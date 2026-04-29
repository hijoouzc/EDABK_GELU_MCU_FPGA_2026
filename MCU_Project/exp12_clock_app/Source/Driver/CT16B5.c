/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:		SONiX
* DATE:				2023/11
* AUTHOR:			SA1
* IC:					SN32F400
* DESCRIPTION:	CT16B5 related functions.
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
#include "CT16B5.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
volatile uint32_t iwCT16B5_IrqEvent = 0x00; //The bitmask usage of iwCT16Bn_IrqEvent is the same with CT16Bn_RIS

void CT16B5_Init(void);
void CT16B5_NvicEnable(void);
void CT16B5_NvicDisable(void);

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: CT16B5_IRQHandler
* Description	: ISR of CT16B5 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq void CT16B5_IRQHandler(void)
{
	uint32_t iwRisStatus;

	iwRisStatus = SN_CT16B5->RIS;	// Save the interrupt status.

	//Before checking the status, always re-check the interrupt enable register first.
	//In practice, user might use only one or two timer interrupt source. 
	//Ex: Enable only MR0IE and MR3IE ==> No check on MR1IE, MR2IE, and CAP0IE is necessary.
  //User can add the directive pair of "#if 0" and "#endif" pair 
	//to COMMENT the un-used parts to reduce ISR overheads and ROM usage.
	
	//Check the status in oder.
	//MR0
	if (SN_CT16B5->MCTRL_b.MR0IE)				//Check if MR0 IE enables?
	{
		if (iwRisStatus & mskCT16_MR0IF)
		{
			iwCT16B5_IrqEvent |= mskCT16_MR0IF;				
			SN_CT16B5->IC = mskCT16_MR0IC;	//Clear MR0 match interrupt status
		}
	}
	//MR1
	if (SN_CT16B5->MCTRL_b.MR1IE)				//Check if MR1 IE enables?
	{
		if (iwRisStatus & mskCT16_MR1IF)		
		{
			iwCT16B5_IrqEvent |= mskCT16_MR1IF;			
			SN_CT16B5->IC = mskCT16_MR1IC;	//Clear MR1 match interrupt status
		}
	}
	//MR2
	if (SN_CT16B5->MCTRL_b.MR2IE)				//Check if MR2 IE enables?
	{
		if (iwRisStatus & mskCT16_MR2IF)		
		{
			iwCT16B5_IrqEvent |= mskCT16_MR2IF;		
			SN_CT16B5->IC = mskCT16_MR2IC;	//Clear MR2 match interrupt status
		}
	}
	//MR3
	if (SN_CT16B5->MCTRL_b.MR3IE)				//Check if MR3 IE enables?
	{	
		if (iwRisStatus & mskCT16_MR3IF)
		{
			iwCT16B5_IrqEvent |= mskCT16_MR3IF;		
			SN_CT16B5->IC = mskCT16_MR3IC;	//Clear MR3 match interrupt status
		}
	}

	//MR9
	if (SN_CT16B5->MCTRL_b.MR9IE)				//Check if MR9 IE enables?
	{	
		if (iwRisStatus & mskCT16_MR9IF)	
		{
			iwCT16B5_IrqEvent |= mskCT16_MR9IF;		
			SN_CT16B5->IC = mskCT16_MR9IC;	//Clear MR9 match interrupt status
		}
	}

	//CAP0
	if (SN_CT16B5->CAPCTRL_b.CAP0IE)		//Check if CAP0 IE enables?
	{
		if (iwRisStatus & mskCT16_CAP0IF)	//CAP0
		{
			iwCT16B5_IrqEvent |= mskCT16_CAP0IF;	
			SN_CT16B5->IC = mskCT16_CAP0IC;	//Clear CAP0 interrupt status
		}	
	}
}

/*****************************************************************************
* Function		: CT16B5_Init
* Description	: Initialization of CT16B5 timer
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B5_Init(void)
{
	__CT16B5_ENABLE;		
}

/*****************************************************************************
* Function		: CT16B5_NvicEnable
* Description	: Enable CT16B5 timer interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B5_NvicEnable(void)
{
	NVIC_ClearPendingIRQ(CT16B5_IRQn);
	NVIC_EnableIRQ(CT16B5_IRQn);
}

/*****************************************************************************
* Function		: CT16B5_NvicDisable
* Description	: Disable CT16B5 timer interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CT16B5_NvicDisable(void)
{
	NVIC_DisableIRQ(CT16B5_IRQn);
}
