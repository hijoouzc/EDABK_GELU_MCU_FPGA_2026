/*****************************************************************************
 * DIGITAL CLOCK APPLICATION
 * Board: SN32F407_EVK
 * Team: EDABK_GELU 2026
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "clock_app.h"
#include "..\Module\Buzzer.h"
#include "..\Module\Segment.h"
#include "..\Module\KeyScan.h"
#include "..\Module\EEPROM.h"
#include "..\Driver\GPIO.h"
#include "..\Driver\Systick.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
/*==========================================================================
 * PRIVATE FUNCTION DECLARATIONS
 *=========================================================================*/
static void _tick_clock(void);
static void _tick_blink(void);
static void _tick_buzzer(void);
static void _tick_timeout(void);
static void _tick_eeprom(void);
static void _process_keys(void);
static void _update_display(void);

static void _handle_sw3(void);
static void _handle_sw16(void);
static void _handle_sw6(void);
static void _handle_sw10(void);
static void _handle_sw18(void);

static void _enter_mode(ClockMode_t new_mode);
static void _exit_to_normal(uint8_t save_time);
static void _buzzer_pip(void);
static void _buzzer_alarm_start(void);
static void _reset_timeout(void);

/*_____ D E F I N I T I O N S ______________________________________________*/
/* === Thời gian thực === */
static uint8_t s_hour   = 0;
static uint8_t s_minute = 0;
static uint8_t s_second = 0;

/* === Giờ hẹn === */
static uint8_t s_alarm_hour   = 0;
static uint8_t s_alarm_minute = 0;

/* === Biến tạm khi đang chỉnh giờ === */
static uint8_t s_edit_hour   = 0;
static uint8_t s_edit_minute = 0;

/* === State Machine === */
static ClockMode_t s_mode = MODE_NORMAL;

static uint8_t s_timeout_cnt = 0; // đếm ngược giây

static uint16_t s_blink_ms  = 0;
static uint8_t  s_blink_on  = 1;   /* 1 = đang hiện, 0 = đang tắt */

static uint16_t s_buzzer_timer  = 0;  /* Đếm ngược ms còn lại */
static uint16_t s_buzzer_cycle  = 0;  /* Đếm ms trong chu kỳ ON/OFF */
static uint8_t  s_buzzer_alarm  = 0;  /* 0=pip thường, 1=alarm mode */

/* === EEPROM save state machine === */
typedef enum { EEPROM_IDLE = 0, EEPROM_CHECK, EEPROM_WRITE } EepromState_t;
static EepromState_t s_eeprom_state = EEPROM_IDLE;
static uint8_t s_alarm_buf[2];

/*_____ M A C R O S ________________________________________________________*/
/* === Timeout counter: đếm ngược giây === */
#define TIMEOUT_SECONDS     30
/* === Nhấp nháy: 500ms ON, 500ms OFF === */
#define BLINK_PERIOD_MS     500
/* === Buzzer timing (non-blocking) === */
#define BUZZER_PIP_MS       300
#define BUZZER_ALARM_MS     5000
/* === EEPROM Address === */
#define	EEPROM_WRITE_ADDR	0xA0
#define	EEPROM_READ_ADDR	0xA1
/* === Debug mode speed === */
#define DEBUG_SPEED 1000           
 
/*_____ F U N C T I O N S __________________________________________________*/
/*==========================================================================
 * PUBLIC FUNCTIONS
 *=========================================================================*/

/**
 * @brief Khởi tạo ứng dụng - Gọi 1 lần trong main()
 */
void ClockApp_Init(void)
{
    /*----------------------------------------------------------------------
     * Đọc EEPROM trước khi vào vòng lặp chính
     * Dùng ACK Polling để chắc chắn EEPROM sẵn sàng
     *---------------------------------------------------------------------*/
    while (!eeprom_check(EEPROM_WRITE_ADDR));
    eeprom_read(EEPROM_READ_ADDR, 0x02, &s_alarm_hour,   1);
    while (!eeprom_check(EEPROM_WRITE_ADDR));
    eeprom_read(EEPROM_READ_ADDR, 0x03, &s_alarm_minute, 1);

    /* Validate dữ liệu đọc từ EEPROM */
    if (s_alarm_hour   > 23) s_alarm_hour   = 0;
    if (s_alarm_minute > 59) s_alarm_minute = 0;

    s_mode = MODE_NORMAL;
}

/**
 * @brief Task chạy mỗi 1ms - Gọi từ main loop khi timer_1ms_flag = 1
 *
 * Đây là pattern "Cooperative Multitasking"
 * Mỗi sub-task chạy rất nhanh, không blocking
 */
void ClockApp_Task_1ms(void)
{
    _tick_buzzer();    /* Điều khiển buzzer */
    _tick_blink();     /* Tạo hiệu ứng nhấp nháy */
    _tick_eeprom();    /* Ghi EEPROM phi đồng bộ */
    _process_keys();   /* Xử lý phím bấm */
    _update_display(); /* Cập nhật hiển thị */
}

/**
 * @brief Task chạy mỗi 1 giây - Gọi từ main loop khi timer_1s_flag = 1
 */
void ClockApp_Task_1s(void)
{
    _tick_clock();    /* Đếm giờ */
    _tick_timeout();  /* Đếm timeout */
}

/*==========================================================================
 * PRIVATE: SUB-TASKS
 *=========================================================================*/

/**
 * @brief Đếm thời gian thực - chạy mỗi 1 giây
 *
 * Luôn xử lý "rollover" (cuộn số) theo thứ tự nhỏ → lớn
 */
static void _tick_clock(void)
{
    /* Chỉ đếm khi ở chế độ thường - tránh nhảy giờ khi đang chỉnh */
    /* Lưu ý: Vẫn đếm giây ngay cả khi đang set, chỉ không rollover phút/giờ */
    s_second++;
    if (s_second < 60) return;

    s_second = 0;
    s_minute++;
    if (s_minute >= 60) {
        s_minute = 0;
        s_hour++;
        if (s_hour >= 24) s_hour = 0;
    }

    /* Kiểm tra báo thức - chỉ check khi vừa rollover phút */
    if (s_hour   == s_alarm_hour   &&
        s_minute == s_alarm_minute &&
        s_mode   == MODE_NORMAL) {
        _buzzer_alarm_start();
    }
}

/**
 * @brief Tạo nhấp nháy 500ms ON / 500ms OFF
 *
 * Dùng counter ms thay vì polling time - chính xác và non-blocking
 */
static void _tick_blink(void)
{
    s_blink_ms++;
    if (s_blink_ms >= BLINK_PERIOD_MS) {
        s_blink_ms = 0;
        s_blink_on = !s_blink_on;
    }
}

/**
 * @brief Điều khiển buzzer không blocking
 *
 *  State machine nhỏ trong task
 * - Pip thường: 300ms ON rồi tắt
 * - Alarm: Lặp lại 500ms ON / 500ms OFF trong 5 giây
 */
static void _tick_buzzer(void)
{
    if (s_buzzer_timer == 0) {
        buzzer_off();
        return;
    }

    s_buzzer_timer--;

    if (s_buzzer_alarm == 0) {
        /* Pip thường: ON suốt 300ms */
        buzzer_on();
    } else {
        /* Alarm: 500ms ON / 500ms OFF */
        s_buzzer_cycle++;
        if (s_buzzer_cycle < 500) {
            buzzer_on();
        } else if (s_buzzer_cycle < 1000) {
            buzzer_off();
        } else {
            s_buzzer_cycle = 0;
        }
    }

    /* Khi hết thời gian */
    if (s_buzzer_timer == 0) {
        buzzer_off();
        s_buzzer_alarm = 0;
        s_buzzer_cycle = 0;
    }
}

/**
 * @brief Xử lý timeout 30 giây không bấm phím
 *
 * Timeout chỉ chạy khi đang ở mode edit
 */
static void _tick_timeout(void)
{
    if (s_mode == MODE_NORMAL) return;

    if (s_timeout_cnt > 0) {
        s_timeout_cnt--;
    }

    if (s_timeout_cnt == 0) {
        /* Timeout: thoát về Normal, lưu lại thay đổi nếu có */
        if (s_mode == MODE_SET_HOUR || s_mode == MODE_SET_MINUTE) {
            _exit_to_normal(1);  /* Lưu giờ đã chỉnh */
        } else {
            _exit_to_normal(0);  /* Không lưu giờ (là alarm mode) */
            /* Alarm mode timeout: vẫn kích hoạt EEPROM save */
            if (s_mode == MODE_ALARM_HOUR || s_mode == MODE_ALARM_MINUTE) {
                s_eeprom_state = EEPROM_CHECK;
            }
        }
        _buzzer_pip();  /* Beep báo timeout */
    }
}

/**
 * @brief Ghi EEPROM phi đồng bộ (non-blocking state machine)
 *
 * I2C EEPROM cần thời gian ghi (tmax ~5ms)
 * Dùng ACK Polling: Thử ghi → nếu EEPROM NACK thì đợi → thử lại
 * KHÔNG blocking bằng delay() → dùng state machine
 */
static void _tick_eeprom(void)
{
    switch (s_eeprom_state) {
        case EEPROM_IDLE:
            break;

        case EEPROM_CHECK:
            if (eeprom_check(EEPROM_WRITE_ADDR)) {
                s_alarm_buf[0] = s_alarm_hour;
                s_alarm_buf[1] = s_alarm_minute;
                eeprom_write(EEPROM_WRITE_ADDR, 0x02, s_alarm_buf, 2);
                s_eeprom_state = EEPROM_WRITE;
            }
            break;

        case EEPROM_WRITE:
            if (eeprom_check(EEPROM_WRITE_ADDR)) {
                s_eeprom_state = EEPROM_IDLE;  /* Ghi xong */
            }
            break;
    }
}

/**
 * @brief Xử lý phím bấm
 *
 * KeyScan trả về KEY_PUSH_FLAG | key_code
 * Dùng switch(s_mode) để biết đang ở state nào rồi xử lý
 */
static void _process_keys(void)
{
    uint16_t key_event = KeyScan();
    /* Không có sự kiện phím */
    if (key_event == 0U) {
        return;
    }

    /* Chỉ xử lý sự kiện nhấn phím */
    if ((key_event & KEY_PUSH_FLAG) == 0U) {
        return;
    }

    /* Tách mã phím khỏi event flag */
    uint8_t key_code = (uint8_t)(key_event & 0x00FFU);

    /*------------------------------------------------------------------
     * Tách xử lý phím thành từng handler function
     * Giúp code dễ đọc và dễ test từng phần
     *-----------------------------------------------------------------*/
    switch (key_code) {
        case KEY_1:   _handle_sw3();  break;  /* SW3: SETUP    */
        case KEY_13:  _handle_sw16(); break;  /* SW16: ALARM   */
        case KEY_4:   _handle_sw6();  break;  /* SW6: +        */
        case KEY_8:   _handle_sw10(); break;  /* SW10: -       */
        case KEY_16:  _handle_sw18(); break;  /* SW18: DEBUG   */
        default: break;
    }
}

/*==========================================================================
 * PRIVATE: KEY HANDLERS - Mỗi phím là 1 hàm riêng
 *=========================================================================*/

static void _handle_sw3(void)
{
    _buzzer_pip();
    _reset_timeout();

    switch (s_mode) {
        case MODE_NORMAL:
            /* Vào chỉnh giờ: copy giờ thực vào biến tạm */
            s_edit_hour   = s_hour;
            s_edit_minute = s_minute;
            _enter_mode(MODE_SET_HOUR);
            break;

        case MODE_SET_HOUR:
            _enter_mode(MODE_SET_MINUTE);
            break;

        case MODE_SET_MINUTE:
            /* Thoát: lưu giờ đã chỉnh vào đồng hồ thực */
            s_hour   = s_edit_hour;
            s_minute = s_edit_minute;
            s_second = 0;
            _enter_mode(MODE_NORMAL);
            break;

        default:
            break;
    }
}

static void _handle_sw16(void)
{
    _buzzer_pip();
    _reset_timeout();

    switch (s_mode) {
        case MODE_NORMAL:
            _enter_mode(MODE_ALARM_HOUR);
            break;

        case MODE_ALARM_HOUR:
            _enter_mode(MODE_ALARM_MINUTE);
            break;

        case MODE_ALARM_MINUTE:
            /* Thoát: kích hoạt lưu EEPROM */
            s_eeprom_state = EEPROM_CHECK;
            _enter_mode(MODE_NORMAL);
            break;

        default:
            break;
    }
}

static void _handle_sw6(void)  /* Nút + */
{
    _buzzer_pip();
    _reset_timeout();

    switch (s_mode) {
        case MODE_SET_HOUR:
            s_edit_hour = (s_edit_hour + 1) % 24;
            break;
        case MODE_SET_MINUTE:
            s_edit_minute = (s_edit_minute + 1) % 60;
            break;
        case MODE_ALARM_HOUR:
            s_alarm_hour = (s_alarm_hour + 1) % 24;
            break;
        case MODE_ALARM_MINUTE:
            s_alarm_minute = (s_alarm_minute + 1) % 60;
            break;
        default:
            break;
    }
    /* Reset blink khi thay đổi giá trị → người dùng thấy ngay */
    s_blink_ms = 0;
    s_blink_on = 1;
}

static void _handle_sw10(void)  /* Nút - */
{
    _buzzer_pip();
    _reset_timeout();

    switch (s_mode) {
        case MODE_SET_HOUR:
            s_edit_hour = (s_edit_hour == 0) ? 23 : s_edit_hour - 1;
            break;
        case MODE_SET_MINUTE:
            s_edit_minute = (s_edit_minute == 0) ? 59 : s_edit_minute - 1;
            break;
        case MODE_ALARM_HOUR:
            s_alarm_hour = (s_alarm_hour == 0) ? 23 : s_alarm_hour - 1;
            break;
        case MODE_ALARM_MINUTE:
            s_alarm_minute = (s_alarm_minute == 0) ? 59 : s_alarm_minute - 1;
            break;
        default:
            break;
    }
    s_blink_ms = 0;
    s_blink_on = 1;
}

static void _handle_sw18(void)  /* Nút DEBUG_Mode */
{
    _buzzer_pip();

    if (debug_speed == 1) debug_speed = DEBUG_SPEED ; // Bật Debug
    else debug_speed = 1;                    // Tắt Debug
}

/*==========================================================================
 * PRIVATE: DISPLAY - Cập nhật hiển thị theo state
 *
 * Tách hoàn toàn display logic khỏi business logic
 * Hàm này chỉ QUYẾT ĐỊNH hiện cái gì, không quan tâm hardware
 *=========================================================================*/
static void _update_display(void)
{
    uint8_t disp_hour, disp_minute;
    uint8_t blink_hh = 0, blink_mm = 0;

    /* Chọn dữ liệu hiển thị theo mode */
    switch (s_mode) {
        case MODE_NORMAL:
            disp_hour   = s_hour;
            disp_minute = s_minute;
            break;

        case MODE_SET_HOUR:
        case MODE_SET_MINUTE:
            disp_hour   = s_edit_hour;
            disp_minute = s_edit_minute;
            blink_hh    = (s_mode == MODE_SET_HOUR);
            blink_mm    = (s_mode == MODE_SET_MINUTE);
            break;

        case MODE_ALARM_HOUR:
        case MODE_ALARM_MINUTE:
            disp_hour   = s_alarm_hour;
            disp_minute = s_alarm_minute;
            blink_hh    = (s_mode == MODE_ALARM_HOUR);
            blink_mm    = (s_mode == MODE_ALARM_MINUTE);
            break;

        default:
            return;
    }

    /* Cập nhật LED 7-seg */
    Digital_Display_Clock(disp_hour, disp_minute);

    /* Áp dụng hiệu ứng nhấp nháy */
    if (!s_blink_on) {
        if (blink_hh) {
            segment_buff[0] = 0x00;
            segment_buff[1] = 0x00;
        }
        if (blink_mm) {
            segment_buff[2] = 0x00;
            segment_buff[3] = 0x00;
        }
    }

    /* LED D6: bật khi ở mode alarm, tắt khi không */
    if (s_mode == MODE_ALARM_HOUR || s_mode == MODE_ALARM_MINUTE) {
        if (s_blink_on) SET_LED0_ON;
        else            SET_LED0_OFF;
    } else {
        SET_LED0_OFF;
    }

    /* Quét LED 7-seg ra GPIO */
    Digital_Scan();
}

/*==========================================================================
 * PRIVATE: HELPER FUNCTIONS
 *=========================================================================*/

static void _enter_mode(ClockMode_t new_mode)
{
    s_mode     = new_mode;
    s_blink_ms = 0;
    s_blink_on = 1;

    if (new_mode != MODE_NORMAL) {
        _reset_timeout();
    }
}

static void _exit_to_normal(uint8_t save_time)
{
    if (save_time) {
        s_hour   = s_edit_hour;
        s_minute = s_edit_minute;
        s_second = 0;
    }
    _enter_mode(MODE_NORMAL);
}

static void _buzzer_pip(void)
{
    s_buzzer_alarm  = 0;
    s_buzzer_timer  = BUZZER_PIP_MS;
    s_buzzer_cycle  = 0;
}

static void _buzzer_alarm_start(void)
{
    s_buzzer_alarm  = 1;
    s_buzzer_timer  = BUZZER_ALARM_MS;
    s_buzzer_cycle  = 0;
}

static void _reset_timeout(void)
{
    s_timeout_cnt = TIMEOUT_SECONDS * debug_speed;
}