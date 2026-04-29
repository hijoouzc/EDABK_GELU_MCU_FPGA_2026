/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	SysTick related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
*	1.0				2023/11/06	SA1			First release
*
*____________________________________________________________________________
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS TIME TO MARKET.
* SONiX SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
* DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
* AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN 
* IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include "SysTick.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
// --- Hệ số tăng tốc độ đồng hồ (DEBUG MODE) ---
uint16_t debug_speed = 1;

volatile uint16_t timer_repeat = 0;
volatile uint8_t timer_1s_flag = 0;
volatile uint8_t timer_1ms_flag = 0;
/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: SysTick_Init
* Description	: Initialization of SysTick timer
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void	SysTick_Init(void)
{
	SystemCoreClockUpdate();

	SysTick_ConfigTime(1);				//Ex: 1 ms

	__SYSTICK_CLEAR_COUNTER_AND_FLAG;

#if SYSTICK_IRQ == INTERRUPT_METHOD
	SysTick->CTRL = 0x7;			//Enable SysTick timer and interrupt
#else
	SysTick->CTRL = 0x5;			//Enable SysTick timer ONLY
#endif	
}

/*****************************************************************************
* Function		: SysTick_ConfigTime
* Description	: Config SysTick reload value
* Input			: ms - SysTick period
* Output		: None
* Return		: None
* Note			: SystemCoreClock * ms /1000 SHALL <= 0x1000000
*****************************************************************************/
void	SysTick_ConfigTime(uint32_t ms)
{
	uint32_t	ticks = SystemCoreClock * ms /1000;
	
	if (ticks > 0x1000000UL)	//Overflow
		SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
	else
		SysTick->LOAD = ticks - 1;

	SysTick->VAL = 0UL;
}

/*****************************************************************************
* Function		: SysTick_Handler
* Description	: ISR of SysTick interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void SysTick_Handler(void)
{
	__SYSTICK_CLEAR_COUNTER_AND_FLAG;

	timer_repeat++;
	if(timer_repeat >= (1000 / debug_speed))	// Ngưỡng lật cờ giây
	{
		timer_repeat = 0;
		timer_1s_flag = 1;
	}
	timer_1ms_flag = 1;
}
