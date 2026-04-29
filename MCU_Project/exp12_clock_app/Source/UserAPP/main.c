/*****************************************************************************
 * MAIN.C - Entry Point
 *
 * 1. Khởi tạo (Init)
 * 2. Vòng lặp chính (Super Loop / Main Loop)
 * 3. KHÔNG có business logic ở đây
 *****************************************************************************/

 /*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>
#include <SN32F400_Def.h>
#include "..\Driver\GPIO.h"
#include "..\Driver\CT16B0.h"
#include "..\Driver\WDT.h"
#include "..\Driver\I2C.h"
#include "..\Driver\SysTick.h"
#include "..\Module\Segment.h"
#include "clock_app.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
void PFPA_Init(void);
void NotPinOut_GPIO_init(void);

/*_____ D E F I N I T I O N S ______________________________________________*/
#ifndef	SN32F407					
	#error Please install SONiX.SN32F4_DFP.0.0.18.pack or version >= 0.0.18
#endif
#define	PKG						SN32F407

int main(void)
{
    /*======================================================================
     * Thứ tự khởi tạo QUAN TRỌNG
     * 1. Clock hệ thống trước tiên
     * 2. Hardware drivers
     * 3. Application modules
     *=====================================================================*/
    SystemInit();
    SystemCoreClockUpdate();
    PFPA_Init();
    NotPinOut_GPIO_init();

    SN_SYS0->EXRSTCTRL_b.RESETDIS = 0;  /* Enable External Reset */

    /* Khởi tạo Drivers */
    GPIO_Init();
    WDT_Init();
    I2C0_Init();
    CT16B0_Init();
    SysTick_Init();  /* Phải init cuối - bắt đầu sinh tick */

    /* Map PWM0 → P3.0 (Buzzer) */
    SN_PFPA->CT16B0_b.PWM0 = 1;

    /* Khởi tạo Application */
    ClockApp_Init();

    /*======================================================================
     * SUPER LOOP - Vòng lặp chính
     *
     * Pattern "Flag-based scheduling"
     * ISR set flag → Main loop check và clear flag → Gọi task
     * Ưu điểm: Đơn giản, dễ debug, không cần RTOS
     *=====================================================================*/
    while (1) {
        __WDT_FEED_VALUE;  /* Feed Watchdog - hệ thống vẫn sống */

        if (timer_1ms_flag) {
            timer_1ms_flag = 0;          /* LUÔN clear flag trước khi xử lý */
            ClockApp_Task_1ms();
        }

        if (timer_1s_flag) {
            timer_1s_flag = 0;
            ClockApp_Task_1s();
        }
    }
}

/*****************************************************************************
* Function		: NotPinOut_GPIO_init
* Description	: Set the status of the GPIO which are NOT pin-out to input pull-up. 
* Input				: None
* Output			: None
* Return			: None
* Note				: 1. User SHALL define PKG on demand.
*****************************************************************************/
void NotPinOut_GPIO_init(void)
{
#if (PKG == SN32F405)
	//set P0.4, P0.6, P0.7 to input pull-up
	SN_GPIO0->CFG = 0x00A008AA;
	//set P1.4 ~ P1.12 to input pull-up
	SN_GPIO1->CFG = 0x000000AA;
	//set P3.8 ~ P3.11 to input pull-up
	SN_GPIO3->CFG = 0x0002AAAA;
#elif (PKG == SN32F403)
	//set P0.4 ~ P0.7 to input pull-up
	SN_GPIO0->CFG = 0x00A000AA;
	//set P1.4 ~ P1.12 to input pull-up
	SN_GPIO1->CFG = 0x000000AA;
	//set P2.5 ~ P2.6, P2.10 to input pull-up
	SN_GPIO2->CFG = 0x000A82AA;
	//set P3.0, P3.8 ~ P3.13 to input pull-up
	SN_GPIO3->CFG = 0x0000AAA8;
#endif
}

/*****************************************************************************
* Function		: HardFault_Handler
* Description	: ISR of Hard fault interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void HardFault_Handler(void)
{
    NVIC_SystemReset();  /* Reset khi có lỗi nghiêm trọng */
}