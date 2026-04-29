/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	OPA related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2023/11/07	SA1			First release
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
#include <SN32F400_Def.h>
#include "OPA.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
#define OPA_VDDDIV2_ENABLE	1		//0: Disable, 1: Enable

uint8_t OPA0_ENABLE = 0x0;		
uint8_t OPA1_ENABLE = 0x1;		
uint8_t OPA2_ENABLE = 0x2;
uint8_t ALL_OPA_ENABLE = 0x3;

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/
/*****************************************************************************
* Function		: OPA_Enable
* Description	: Enable PCLK for OPA
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void OPA_Enable(void)
{
	__OPA_ENABLE_PCLK;
}

/*****************************************************************************
* Function		: OPA_Disable
* Description	: Disable PCLK for OPA
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void OPA_Disable(void)
{
	__OPA_DISABLE_PCLK;
}

/*****************************************************************************
* Function		: OPA_PGA_Test
* Description	: OPA_PGA_Test
* Input			: number (OPA0~2)
						: gain (setting value + 1), setting value = 0x0~0x1F(1X~32X)
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void OPA_PGA_Test(uint8_t number, uint8_t gain)
{
	SN_OPA->PGACTRL_b.VHALF_EN = 1; //0: Disable, 1: Enable
	
	if(number == OPA0_ENABLE)
	{
		SN_OPA->PGACTRL |= (mskOP0PS_DIS | mskOP0NS_EN | mskOP0PRS_10K | mskOP0NRS_10K);
		SN_OPA->PGACTRL_b.OP0GS = gain;
		SN_OPA->CTRL |= (mskOP0EN_EN | mskOP0_SEL_OP0O);
	}
	if(number == OPA1_ENABLE)
	{
		SN_OPA->PGACTRL |= (mskOP1PS_DIS | mskOP1NS_EN | mskOP1PRS_10K | mskOP1NRS_10K);
		SN_OPA->PGACTRL_b.OP1GS = gain;
		SN_OPA->CTRL |= (mskOP1EN_EN | mskOP1_SEL_OP1O);
	}
	if(number == OPA2_ENABLE)
	{
		SN_OPA->PGACTRL2 |= (mskOP2PS_DIS | mskOP2NS_EN | mskOP2PRS_10K | mskOP2NRS_10K);
		SN_OPA->PGACTRL2_b.OP2GS = gain;
		SN_OPA->CTRL |= (mskOP2EN_EN | mskOP2_SEL_OP2O);
	}
}
