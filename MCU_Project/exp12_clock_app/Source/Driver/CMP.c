/******************** (C) COPYRIGHT 2021 SONiX *******************************
* COMPANY:	SONiX
* DATE:			2023/11
* AUTHOR:		SA1
* IC:				SN32F400
*____________________________________________________________________________
*	REVISION	Date				User		Description
*	1.0				2023/11/07	SA1			1. First version released
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
#include "CMP.h"
#include "ADC.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	CMP0_ENABLE					1		//0: Disable, 1: Enable
#define	CMP1_ENABLE					1		//0: Disable, 1: Enable
#define	CMP2_ENABLE					1		//0: Disable, 1: Enable
#define	CMP3_ENABLE					1		//0: Disable, 1: Enable
#define	CMP_VIREF_ENABLE		1		//0: Disable, 1: Enable

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: CMP0_IRQHandler
* Description	: ISR of CMP0 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq void CMP0_IRQHandler(void)
{
	SN_CMP->IC |= mskCMP_CM0IC_ENABLE;
}

/*****************************************************************************
* Function		: CMP1_IRQHandler
* Description	: ISR of CMP1 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq void CMP1_IRQHandler(void)
{
	SN_CMP->IC |= mskCMP_CM1IC_ENABLE;
}

/*****************************************************************************
* Function		: CMP2_IRQHandler
* Description	: ISR of CMP2 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq void CMP2_IRQHandler(void)
{
	SN_CMP->IC |= mskCMP_CM2IC_ENABLE;
}

/*****************************************************************************
* Function		: CMP3_IRQHandler
* Description	: ISR of CMP3 interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq void CMP3_IRQHandler(void)
{
	SN_CMP->IC |= mskCMP_CM3IC_ENABLE;
}

/*****************************************************************************
* Function		: CMP_init
* Description	: Initialization of CMP0/CMP1/CMP2/CMP3
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CMP_init(void)
{
	__CMP_ENABLE_CMPHCLK;

#if CMP_VIREF_ENABLE
	__ADC_ENABLE_HCLK
	CMP_VIREF_Enable(0x7F);
#endif

#if CMP0_ENABLE
	SN_CMP->CTRL |= (mskCMP_CM0PS_VIREF0 | mskCMP_CM0O_ENABLE | mskCMP_CM0G_FALLING);
	SN_CMP->IE |= mskCMP_CM0IE_ENABLE;
	NVIC_EnableIRQ(CMP0_IRQn);
	__CMP0_ENABLE;
#endif
	
#if CMP1_ENABLE
	SN_CMP->CTRL |= (mskCMP_CM1PS_VIREF0 | mskCMP_CM1O_ENABLE | mskCMP_CM1G_FALLING);
	SN_CMP->IE |= mskCMP_CM1IE_ENABLE;
	NVIC_EnableIRQ(CMP1_IRQn);
	__CMP1_ENABLE;
#endif

#if CMP2_ENABLE
	SN_CMP->CTRL1 |= (mskCMP_CM2PS_VIREF0 | mskCMP_CM2O_ENABLE | mskCMP_CM2G_FALLING);
	SN_CMP->IE |= mskCMP_CM2IE_ENABLE;
	NVIC_EnableIRQ(CMP2_IRQn); 
	__CMP2_ENABLE;
#endif

#if CMP3_ENABLE
	SN_CMP->CTRL1 |= (mskCMP_CM3PS_VIREF0 | mskCMP_CM3O_ENABLE | mskCMP_CM3G_FALLING);
	SN_CMP->IE |= mskCMP_CM3IE_ENABLE;
	NVIC_EnableIRQ(CMP3_IRQn);
	__CMP3_ENABLE;
#endif
}

/*****************************************************************************
* Function		: CMP_VIREF_init
* Description	: Initialization of CMP0/1/2/3
* Input				: 8-bit DAC0/DAC1 setup data bits
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void CMP_VIREF_Enable(uint8_t VIREF_b)
{
	#if CMP0_ENABLE | CMP1_ENABLE | CMP2_ENABLE
		SN_CMP->VIREF |= (mskCMP_DATA(VIREF_b) | mskCMP_CMPIREFEN_ENABLE); //8-bit DAC0 setup data bits + CMP0/1/2 internal reference voltage (VIREF0/1/2) enable
	#endif
	
	#if CMP3_ENABLE
		SN_CMP->VIREF |= (mskCMP_DATA1(VIREF_b) | mskCMP_CMPIREF1EN_ENABLE); //8-bit DAC1 setup data bits + CMP3 internal reference voltage (VIREF3) enable
	#endif
}
