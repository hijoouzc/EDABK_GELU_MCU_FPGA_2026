# 🕐 Đồng Hồ Số Trên Kit SN32F407 EVK

**Platform:** SN32F407 EVK (ARM Cortex-M0, 12 MHz)  
**IDE:** Keil MDK-ARM v5 (ARMCLANG v6.24)  
**ROM:** 4.14 KB / 32 KB | **RAM:** 0.64 KB / 8 KB

---
![Board SN32F407](images/board.jpg)
## Mục Lục

- [Tính Năng](#tính-năng)
- [Kiến Trúc Phần Mềm](#kiến-trúc-phần-mềm)
- [Cấu Trúc Thư Mục](#cấu-trúc-thư-mục)
- [Phần Cứng & Kết Nối](#phần-cứng--kết-nối)
- [State Machine](#state-machine)
- [Luồng Hoạt Động](#luồng-hoạt-động)
- [Các Kỹ Thuật Quan Trọng](#các-kỹ-thuật-quan-trọng)
- [Hướng Dẫn Build & Flash](#hướng-dẫn-build--flash)
- [Bảng Phím](#bảng-phím)

---

## Tính Năng

| Tính năng | Mô tả |
|---|---|
| Hiển thị giờ | 4 LED 7-SEG, định dạng `HH.MM` (00.00 – 23.59) |
| Chỉnh giờ | SW3 (SETUP) → nhấp nháy HH hoặc MM, SW6/SW10 để tăng/giảm |
| Hẹn giờ | SW16 (ALARM) → chỉnh và lưu vào EEPROM, chuông kêu 5 giây khi đến giờ |
| Buzzer | Pip 300ms mỗi lần bấm phím; pip-pip 500ms ON/OFF khi báo thức |
| LED D6 | Nhấp nháy khi đang ở chế độ chỉnh alarm |
| Timeout | 30 giây không bấm → tự thoát, buzzer báo |
| Persistence | Giờ hẹn lưu EEPROM I2C (địa chỉ 0xA0), ACK Polling phi đồng bộ |
| WDT | Watchdog Timer reset hệ thống nếu main loop bị treo |

---

## Kiến Trúc Phần Mềm

### Layered Architecture (Phân Lớp Nghiêm Ngặt)

```
┌─────────────────────────────────┐
│         UserAPP Layer           │  clock_app.c / main.c
│   (Business Logic, State FSM)   │  ← Chỉ gọi xuống, không bao giờ gọi lên
├─────────────────────────────────┤
│         Module Layer            │  KeyScan, Segment, Buzzer, EEPROM
│   (Reusable Components)         │  ← Đóng gói phần cứng thành API cấp cao
├─────────────────────────────────┤
│         Driver Layer            │  GPIO, CT16B0, SysTick, I2C0, WDT
│   (Hardware Abstraction)        │  ← Trực tiếp điều khiển thanh ghi
├─────────────────────────────────┤
│         HAL / CMSIS             │  SN32F400.h, core_cm0.h
│   (Vendor Register Definitions) │
└─────────────────────────────────┘

Quy tắc: App → Module → Driver → HAL  (KHÔNG BAO GIỜ ngược chiều)
```

### Cooperative Multitasking – Super Loop

```c
// main.c
while (1) {
    __WDT_FEED_VALUE;            // Feed watchdog mỗi vòng lặp

    if (timer_1ms_flag) {        // SysTick ISR set flag
        timer_1ms_flag = 0;      // Clear TRƯỚC khi xử lý
        ClockApp_Task_1ms();     // Buzzer + Blink + EEPROM + KeyScan + Display
    }

    if (timer_1s_flag) {
        timer_1s_flag = 0;
        ClockApp_Task_1s();      // Đếm giờ + Timeout
    }
}
```

**Nguyên tắc vàng:** ISR **chỉ set flag**, không bao giờ thực thi logic phức tạp.

### Flag-based Scheduling

```
SysTick ISR (mỗi 1ms)
│
├─→ timer_1ms_flag = 1
│     │
│     └─→ Main Loop xử lý:
│           ├─ _tick_buzzer()    ← Non-blocking buzzer state machine
│           ├─ _tick_blink()     ← 500ms counter cho nhấp nháy
│           ├─ _tick_eeprom()    ← ACK Polling state machine
│           ├─ _process_keys()   ← KeyScan + dispatch handler
│           └─ _update_display() ← Chọn data → ghi segment_buff → Digital_Scan()
│
└─→ timer_1s_flag = 1 (mỗi 1000 lần)
      └─→ Main Loop xử lý:
            ├─ _tick_clock()    ← Tăng giây/phút/giờ, check báo thức
            └─ _tick_timeout()  ← Đếm ngược 30s, thoát mode
```

---

## Cấu Trúc Thư Mục

```
clock_app/
├── Source/
│   ├── UserAPP/
│   │   ├── main.c              ← Entry point, super loop, init sequence
│   │   ├── clock_app.c         ← Toàn bộ business logic, state machine
│   │   └── clock_app.h         ← Public API: ClockApp_Init/Task_1ms/Task_1s
│   │
│   ├── Driver/                 ← Hardware drivers (HAL)
│   │   ├── GPIO.c / .h         ← GPIO init, IRQ handlers
│   │   ├── CT16B0.c / .h       ← PWM timer cho buzzer (P3.0)
│   │   ├── SysTick.c / .h      ← System tick 1ms, timer_1ms/1s flags
│   │   ├── I2C0.c / .h         ← I2C master driver
│   │   ├── WDT.c / .h          ← Watchdog Timer (250ms reset)
│   │   ├── PFPA.c              ← Pin Function / Peripheral Assignment
│   │   └── Utility.c / .h      ← UT_DelayNx10us (blocking delay, dùng hạn chế)
│   │
│   └── Module/                 ← Reusable components
│       ├── KeyScan.c / .h      ← Ma trận phím 4×4, debounce phần mềm
│       ├── Segment.c / .h      ← LED 7-SEG multiplexing, segment_buff[]
│       ├── Buzzer.c / .h       ← buzzer_on/off, bảng nốt nhạc
│       └── EEPROM.c / .h       ← eeprom_read/write/check (ACK Polling)
│
├── RTE/Device/SN32F407F/
│   ├── startup_SN32F400.s      ← Vector table, Reset_Handler
│   └── system_SN32F400.c       ← SystemInit, SystemCoreClockUpdate
│
├── Objects/                    ← Build artifacts (.o, .axf, .map)
├── Listings/                   ← Linker map, assembly listing
└── clock_app.uvprojx           ← Keil project file
```

---

## Phần Cứng & Kết Nối

### LED 7-Segment (4 digit, Common Cathode)

| GPIO | Chức năng |
|---|---|
| P0.0 – P0.7 | Segment A–H (dữ liệu đoạn) |
| P1.9 | COM0 – Digit 0 (hàng chục giờ) |
| P1.10 | COM1 – Digit 1 (hàng đơn vị giờ, có dấu chấm `.`) |
| P1.11 | COM2 – Digit 2 (hàng chục phút) |
| P1.12 | COM3 – Digit 3 (hàng đơn vị phút) |

> **Ghost Prevention:** `Digital_Scan()` tắt TẤT CẢ segment trước khi chuyển COM.  
> Không làm vậy → các digit "ma" xuất hiện do điện dung ký sinh.

### Phím Bấm (Ma Trận 4×4)

| Phím | GPIO | Chức năng |
|---|---|---|
| SW3 | ROW4 + COL1 = KEY_13 | SETUP – chỉnh giờ thực |
| SW16 | ROW4 + COL4 = KEY_16 | ALARM – chỉnh giờ hẹn |
| SW6 | ROW1 + COL4 = KEY_4 | + (tăng) |
| SW10 | ROW2 + COL4 = KEY_8 | − (giảm) |

> **Debounce:** KeyScan dùng software counter (`key_debounce`).  
> Chỉ nhận sự kiện sau `KEY_SHORT_PUSH_TIME = 50` lần poll liên tiếp cùng trạng thái.

### Ngoại Vi Khác

| Ngoại vi | GPIO / Địa chỉ | Ghi chú |
|---|---|---|
| Buzzer PWM | P3.0 → CT16B0 PWM0 | CT16B0 MR9 = period, MR0 = duty cycle |
| LED D6 | P3.8 | Active LOW (BCLR = ON, BSET = OFF) |
| EEPROM I2C | SDA=P1.5, SCL=P1.4 | Địa chỉ 0xA0 (Write), 0xA1 (Read) |

---

## State Machine

![State Machine ](images/FSM.png)

---

## Luồng Hoạt Động

### Khởi Động

```
SystemInit() → SystemCoreClockUpdate() → PFPA_Init() → GPIO_Init()
→ WDT_Init() → I2C0_Init() → CT16B0_Init() → SysTick_Init()
→ ClockApp_Init() [đọc alarm từ EEPROM với ACK Polling]
→ Super Loop
```

### Non-Blocking Buzzer

Thay vì `delay(300ms)` blocking, dùng countdown counter:

```c
// Khi bấm phím:
s_buzzer_timer = 300;   // đặt countdown 300ms
s_buzzer_alarm = 0;     // chế độ pip đơn

// Trong _tick_buzzer() (gọi mỗi 1ms):
if (s_buzzer_timer == 0) { buzzer_off(); return; }
s_buzzer_timer--;
buzzer_on();   // pip: ON suốt countdown
```

### Non-Blocking EEPROM Write (ACK Polling)

EEPROM cần ~5ms ghi nội bộ. Dùng state machine thay vì `while(!ready)`:

```
EEPROM_IDLE → [trigger] → EEPROM_CHECK → [ACK nhận] → EEPROM_WRITE → [ACK nhận] → EEPROM_IDLE
                              ↑_________________|NACK (busy, thử lại tick sau)
```

---

## Các Kỹ Thuật Quan Trọng

### 1. `volatile` – Bắt Buộc Cho Biến Chia Sẻ Giữa ISR và Main

```c
// SysTick.h
extern volatile uint8_t timer_1ms_flag;
extern volatile uint8_t timer_1s_flag;
```

Nếu thiếu `volatile`, compiler tối ưu hóa bỏ qua việc đọc biến trong main loop → chương trình treo vĩnh viễn. Compiler không biết biến được thay đổi bởi ISR.

### 2. Clear Flag TRƯỚC Khi Xử Lý

```c
// Đúng:
if (timer_1ms_flag) {
    timer_1ms_flag = 0;     ← Clear trước
    ClockApp_Task_1ms();    ← Rồi mới xử lý
}

// Sai (có thể miss flag nếu ISR fire trong lúc xử lý):
if (timer_1ms_flag) {
    ClockApp_Task_1ms();
    timer_1ms_flag = 0;     ← Clear sau = nguy hiểm
}
```

### 3. LED Multiplexing – Thứ Tự Tắt/Bật

```c
void Digital_Scan(void) {
    SN_GPIO0->BCLR = 0xff;      // 1. Tắt TẤT CẢ segment
    SN_GPIO1->BCLR = 0xf << 9; // 2. Tắt TẤT CẢ COM
    com_scan++;                  // 3. Chuyển COM tiếp theo
    // ... bật COM mới ...      // 4. Bật COM
    SN_GPIO0->BSET = segment_buff[com_scan]; // 5. Bật segment
}
```

Nếu bật COM mới trước khi tắt segment cũ → digit "ma" xuất hiện trong ~vài microsecond.

### 4. SysTick – Heartbeat Của Hệ Thống

```c
// SysTick_Init: load = SystemCoreClock / 1000 - 1 = 11999 (cho 1ms @ 12MHz)
SysTick->LOAD = 11999;
SysTick->CTRL = 0x7;  // Enable + Interrupt + Use processor clock

// ISR chỉ set flag, KHÔNG làm gì khác:
void SysTick_Handler(void) {
    __SYSTICK_CLEAR_COUNTER_AND_FLAG;
    timer_1ms_flag = 1;
    // Mỗi 1000ms: timer_1s_flag = 1
}
```

### 5. PWM Buzzer – CT16B0

```
CT16B0 hoạt động ở Edge-Aligned Up-Counting mode:
- MR9: Period register – TC reset về 0 khi TC == MR9
- MR0: Duty cycle – PWM output toggle khi TC == MR0
- Tần số = HCLK / (MR9 + 1)
- Duty cycle = MR0 / MR9 (50% khi MR0 = MR9/2)

buzzer_on()  → MR9 = 43 (277Hz ≈ 1kHz), MR0 = MR9/2
buzzer_off() → MR0 = 0 (duty = 0%, không có xung ra)
```

### 6. I2C EEPROM – Giao Thức Ghi Đọc

```
WRITE: START → addr|W → ACK → reg_addr → ACK → data → ACK → STOP
READ:  START → addr|W → ACK → reg_addr → ACK →
       RESTART → addr|R → ACK → [data → ACK]* → data → NACK → STOP

ACK Polling (kiểm tra ghi xong chưa):
       START → addr|W → nếu ACK: EEPROM ready; nếu NACK: đang ghi nội bộ
```

### 7. Watchdog Timer

```c
WDT_ReloadValue(61);  // ~250ms timeout @ ILRC 32kHz
__WDT_ENABLE;

// Trong main loop:
__WDT_FEED_VALUE;     // = SN_WDT->FEED = 0x5AFA55AA
```

Nếu main loop bị treo hơn 250ms (do bug), WDT reset MCU. Safety net cho production firmware.

---

## Hướng Dẫn Build & Flash

### Yêu Cầu

- Keil MDK-ARM v5 (ARMCLANG v6.x)  
- Pack: `SONiX.SN32F4_DFP` v1.1.1 trở lên  
- Debugger: SNLINK hoặc J-Link

### Build

```
1. Mở clock_app.uvprojx
2. Chọn Target: "Target 1"
3. Project → Build (F7)
4. Kết quả: Objects/exp1_LED_blink.axf
   Code: ~4.14 KB ROM, ~0.64 KB RAM
```

### Flash

```
1. Kết nối SNLINK vào connector SWD của board
2. Flash → Download (F8)
   hoặc Debug → Start Debug Session (Ctrl+F5) → Run (F5)
```

### Verify Build Thành Công

Trong `Listings/exp1_LED_blink.map`, kiểm tra:

```
Total RO  Size (Code + RO Data)    4236 (4.14kB)   ← Phải < 32KB (0x8000)
Total RW  Size (RW Data + ZI Data)  656 (0.64kB)   ← Phải < 8KB  (0x2000)
```

---

## Bảng Phím

| Trạng thái hiện tại | SW3 (SETUP) | SW16 (ALARM) | SW6 (+) | SW10 (−) |
|---|---|---|---|---|
| NORMAL | → SET_HOUR | → ALARM_HOUR | — | — |
| SET_HOUR | → SET_MIN | — | Tăng giờ | Giảm giờ |
| SET_MIN | → NORMAL (lưu giờ) | — | Tăng phút | Giảm phút |
| ALARM_HOUR | — | → ALARM_MIN | Tăng giờ | Giảm giờ |
| ALARM_MIN | — | → NORMAL (lưu EEPROM) | Tăng phút | Giảm phút |

> Bấm phím bất kỳ trong edit mode → reset timeout 30 giây.  
> Bấm phím bất kỳ → buzzer pip 300ms.


*SN32F407 EVK | Keil MDK-ARM v5 | ARM Cortex-M0 @ 12MHz*
