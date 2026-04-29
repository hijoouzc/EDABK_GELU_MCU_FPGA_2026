/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:		SONiX
* DATE:				2023/11
* AUTHOR:			SA1
* IC:					SN32F400
* DESCRIPTION:	CT16B0 related functions.
*____________________________________________________________________________
*	REVISION	Date				User		Description
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
#include <SN32F400.h>
#include "CT16.h"
#include "CT16B0.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
void CT16B0_Init(void);
void CT16B0_NvicEnable(void);
void CT16B0_NvicDisable(void);

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: CT16B0_IRQHandler
* Description	: ISR of CT16B0 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B0_IRQHandler(void)
{
	uint32_t ris = SN_CT16B0->RIS;	//read interrupt request
	
	//clear ct16b0 group interrupt flag
	SN_CT16B0->IC = ris;
}

/*****************************************************************************
* Function		: CT16B0_Init
* Description	: Initialization of CT16B0 timer
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B0_Init(void)
{
	//Enable P_CLOCK for CT16B0.
	__CT16B0_ENABLE;
	
	SN_CT16B0->MR9 = 12 * 1000 -1;	//HCLK=12MHz.timer 1ms
	
	SN_CT16B0->MR0 = 0;
	
	SN_CT16B0->MCTRL = 1<<30;			//when TC == MR9,reset TC = 0;
	
	SN_CT16B0->PWMCTRL = 1 << 0 |		//enable PWM0 PWM MODE
											 1 << 4 |		//PWM0 mode 2
											 1 << 20;   //enable PWM0 IO output enable
	
	
	SN_CT16B0->TMRCTRL = 1 << 1;		//reset timer count
	while(SN_CT16B0->TMRCTRL & (1<<1));
	
	SN_CT16B0->TMRCTRL = 1;					//START TIMER

}

/*****************************************************************************
* Function		: CT16B0_NvicEnable
* Description	: Enable CT16B0 timer interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B0_NvicEnable(void)
{
	NVIC_ClearPendingIRQ(CT16B0_IRQn);
	NVIC_EnableIRQ(CT16B0_IRQn);
}

/*****************************************************************************
* Function		: CT16B0_NvicEnable
* Description	: Disable CT16B0 timer interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B0_NvicDisable(void)
{
	NVIC_DisableIRQ(CT16B0_IRQn);
}
