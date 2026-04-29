/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:			  SA1
* IC:					  SN32F400
* DESCRIPTION:	GPIO related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
*	1.0				2023/11/07	SA1			1. First release
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
#include "GPIO.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: GPIO_Init
* Description	: GPIO Init
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void GPIO_Init(void)
{
	//key row input
	SN_GPIO1->MODE = 0xf << 4;	//p14~p17 4 pin input mode
	//key col input 
	SN_GPIO2->MODE = 0xf << 4;	//p24~p27 4 pin input mode

	//set digital tube segment port output mode
	SN_GPIO0->MODE = 0xff;	//p00~p07 8 pin output mode
	SN_GPIO0->BCLR = 0xff;	//P00~P07 8 pin out put low
	
	//set digital tube COM port output
	SN_GPIO1->MODE = 0x0f << 9;	//P19~P112	4 pin output mode
	SN_GPIO1->BCLR = 0x0f << 9;	//P19~P112	4 pin output low
	
	//set P3.8 output mode to driver LED0 
	SN_GPIO3->MODE_b.MODE8 = 1;
	SET_LED0_OFF;
	//set P3.9 output mode to driver LED0 
	SN_GPIO3->MODE_b.MODE9 = 1;	
	SET_LED1_OFF;
	
}
/*****************************************************************************
* Function		: P0_IRQHandler
* Description	: Set GPIO P0 IRQ
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void P0_IRQHandler(void)
{
	//clear P0 group interrupt flag
	SN_GPIO0->IC = 0x3FFF;
}

/*****************************************************************************
* Function		: P1_IRQHandler
* Description	: Set GPIO P1 IRQ
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void P1_IRQHandler(void)
{
	//clear P1 group interrupt flag
	SN_GPIO1->IC = 0x3FFF;
}

/*****************************************************************************
* Function		: P2_IRQHandler
* Description	: Set GPIO P2 IRQ
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void P2_IRQHandler(void)
{
	//clear P2 group interrupt flag
	SN_GPIO2->IC = 0x3FFF;
}

/*****************************************************************************
* Function		: P3_IRQHandler
* Description	: Set GPIO P3 IRQ
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void P3_IRQHandler(void)
{
	//clear P3 group interrupt flag
	SN_GPIO3->IC = 0x3FFF;
}
