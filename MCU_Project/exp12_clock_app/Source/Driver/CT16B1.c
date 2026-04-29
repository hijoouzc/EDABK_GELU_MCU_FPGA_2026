/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:		SONiX
* DATE:				2023/11
* AUTHOR:			SA1
* IC:					SN32F400
* DESCRIPTION:	CT16B1 related functions.
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
#include "CT16B1.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

void CT16B1_Init(void);
void CT16B1_NvicEnable(void);
void CT16B1_NvicDisable(void);

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/
/*****************************************************************************
* Function		: CT16B1_IRQHandler
* Description	: ISR of CT16B1 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B1_IRQHandler(void)
{
	uint16_t ris = SN_CT16B1->RIS;
	
	if(ris & (1 << 5))		//interrupt flag for match MR9
	{
		timer_1ms_flag = 1;
	}
	SN_CT16B1->IC = ris;
}

/*****************************************************************************
* Function		: CT16B1_Init
* Description	: Initialization of CT16B1 timer
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B1_Init(void)
{
	//Enable P_CLOCK for CT16B1.
	__CT16B1_ENABLE;
	
	SN_CT16B1->MR9 = 12 * 1000 -1;	//HCLK=12MHz.timer 1ms
	
	SN_CT16B1->MCTRL = 1<<30|			//when TC == MR9,reset TC = 0;
										 1<<29;				//when TC == MR9
	
	SN_CT16B1->TMRCTRL = 1 << 1;		//reset timer count
	while(SN_CT16B1->TMRCTRL & (1<<1));
	
	SN_CT16B1->TMRCTRL = 1;					//START TIMER
	
	NVIC_EnableIRQ(CT16B1_IRQn);		//ENABLE systerm CT16B0 interrput
}

/*****************************************************************************
* Function		: CT16B1_NvicEnable
* Description	: Enable CT16B1 timer interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B1_NvicEnable(void)
{
	NVIC_ClearPendingIRQ(CT16B1_IRQn);
	NVIC_EnableIRQ(CT16B1_IRQn);
}

/*****************************************************************************
* Function		: CT16B1_NvicDisable
* Description	: Enable CT16B1 timer interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B1_NvicDisable(void)
{
	NVIC_DisableIRQ(CT16B1_IRQn);
}
