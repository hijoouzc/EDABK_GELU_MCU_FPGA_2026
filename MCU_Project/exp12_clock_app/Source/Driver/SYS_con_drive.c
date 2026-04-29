/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	System Control related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
*	1.0				2023/11/06	SA1			1. First version release
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
#include "SYS_con_drive.h"
#include "Flash.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: SYS0_GetResetStatus
* Description	: Get specified reset status
* Input				: mskRst - mskSYS0_SW_RESET, mskSYS0_WDT_RESET, mskSYS0_LVD_RESET,
*												 mskSYS0_EXT_RESET, mskSYS0_POR_RESET
* Output			: None
* Return			: TRUE - Reset occurred
*								FALSE - No reset occurred
* Note				: None
*****************************************************************************/
uint32_t SYS0_GetResetStatus(uint32_t mskRst)
{
	if ((SN_SYS0->RSTST & mskRst) != 0)
		return FALSE;
	else
		return TRUE;
}

/*****************************************************************************
* Function		: SYS0_EnableIHRC
* Description	: Enable IHRC and wait for ready
* Input				: ihrcclk - SYS0_IHRC_DISABLE, SYS0_IHRC_12MHZ, SYS0_IHRC_48MHZ 
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void SYS0_EnableIHRC(uint32_t ihrcclk)
{
	switch(ihrcclk){
		case SYS0_IHRC_DISABLE:	
			__SYS0_IHRC_DISABLE;
			//while (__SYS0_CHECK_IHRC_READY_STATUS == mskSYS0_IHRC_READY);
			break;
		case SYS0_IHRC_12MHZ:
			__FLASH_LPM_DISABLE;			
			__SYS0_IHRC12_ENABLE;
			while (__SYS0_CHECK_IHRC_READY_STATUS != mskSYS0_IHRC_READY);
			break;
		case SYS0_IHRC_48MHZ:
			__FLASH_LPM_FASTEST_MODE;
			__SYS0_IHRC48_ENABLE;
			while (__SYS0_CHECK_IHRC_READY_STATUS != mskSYS0_IHRC_READY);
			break;
	}
}

/*****************************************************************************
* Function		: SYS0_EnableEHSXtal
* Description	: Enable EHS X'tal source and wait for ready
* Input				: EHS Freq (Mhz)
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void SYS0_EnableEHSXtal(uint32_t freq)
{
	if (freq > 12)
	{
		SN_SYS0->ANBCTRL_b.EHSFREQ = SYS0_EHS_FREQ_DRIVE_HIGH;
	}
	else
	{
		SN_SYS0->ANBCTRL_b.EHSFREQ = SYS0_EHS_FREQ_DRIVE_LOW;
	}
	
	SN_SYS0->ANBCTRL_b.EHSEN = SYS0_EHS_ENABLE;

	while (__SYS0_CHECK_EHS_READY_STATUS != mskSYS0_EHS_READY);
}

/*****************************************************************************
* Function		: SYS0_EnableELSXtal
* Description	: Enable ELS X'tal and wait for ready
* Input				: None
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void SYS0_EnableELSXtal(void)
{
	__SYS0_ELS_ENABLE;
	while (__SYS0_CHECK_ELS_READY_STATUS != mskSYS0_ELS_READY);
}

/*********************************************************************************
* Function		: SYS0_EnablePLL
* Description	: Enable EHS X'tal source and wait for ready
* Input				: Msel - 2~31
*								Psel - SYS0_PLL_P2, SYS0_PLL_P4
*								Fsel - SYS0_PLL_F1, SYS0_PLL_F2, SYS0_PLL_F3
*								clksrc - SYS0_PLL_CLOCK_IHRC or SYS0_PLL_CLOCK_EHS
* Output			: None
* Return			: None
* Note				: User shall call SYS0_EnableEHSXtal or SYS0_EnableIHRC to make sure
*								the clock source of PLL is enabled and ready.
*********************************************************************************/
void SYS0_EnablePLL(uint32_t Msel, uint32_t Psel, uint32_t Fsel, uint32_t clksrc)
{
	SN_SYS0->PLLCTRL = (Msel|(Psel<<5)|(Fsel<<8));
	
	//User shall call SYS0_EnableEHSXtal(freq) or SYS0_EnableIHRC() to make sure
	//the clock source of PLL is enabled and ready.
	if (clksrc == SYS0_PLL_CLOCK_EHS)
		SN_SYS0->PLLCTRL |=  mskSYS0_PLL_CLOCK_EHS;
	else if (clksrc == SYS0_PLL_CLOCK_IHRC)
		SN_SYS0->PLLCTRL |= mskSYS0_PLL_CLOCK_IHRC;

	__SYS0_PLL_ENABLE;
	while (__SYS0_CHECK_PLL_READY_STATUS != mskSYS0_PLL_READY);
}

/***************************************************************************************
* Function		: SYS0_SystemClockSwitch
* Description	: Switch system clock to desired clock source, and set proper AHB clock 
*								prescale value.
* Input				: sysclk - SYS0_SYSCLK_IHRC, SYS0_SYSCLK_ILRC, SYS0_SYSCLK_EHS,
*												 SYS0_SYSCLK_ELS, SYS0_SYSCLK_PLL
*								prescale - SYS0_AHBPRE_DIV1, SYS0_AHBPRE_DIV2, ..., SYS0_AHBPRE_DIV128
*								prescale15 - SYS0_SYSCLK_DIV1, SYS0_SYSCLK_DIV1P5
* Output			: None
* Return			: None
* Note				: User shall Enable the desired system clock source and disable
*								the unused clock by application after switching for power 
*								saving issue.
***************************************************************************************/
void SYS0_SystemClockSwitch(uint32_t sysclk, uint32_t prescale, uint32_t prescale15)
{
	//<-------------------- Set for ROM Power Control BEGIN -------------------->
	__FLASH_LPM_FASTEST_MODE;
	//<-------------------- Set for ROM Power Control END   -------------------->
	
	SN_SYS0->AHBCP = prescale + (prescale15 << 3);
	
	SN_SYS0->CLKCFG = sysclk;

	switch (sysclk)
	{
		case SYS0_SYSCLK_IHRC:
			while (__SYS0_CHECK_SYSCLK_SW_STATUS != mskSYS0_SYSCLK_SW_IHRC);
			break;
		case SYS0_CLK_ILRC:
			while (__SYS0_CHECK_SYSCLK_SW_STATUS != mskSYS0_SYSCLK_SW_ILRC);
			break;
		case SYS0_CLK_EHS:
			while (__SYS0_CHECK_SYSCLK_SW_STATUS != mskSYS0_SYSCLK_SW_EHS);
			break;
		case SYS0_CLK_ELS:
			while (__SYS0_CHECK_SYSCLK_SW_STATUS != mskSYS0_SYSCLK_SW_ELS);
			break;
		case SYS0_CLK_PLL:
			while (__SYS0_CHECK_SYSCLK_SW_STATUS != mskSYS0_SYSCLK_SW_PLL);
			break;
		default:
			break;
	}
}

/***************************************************************************************
* Function		: SYS0_SystemCoreClockUpdate
* Description	: Switch system clock to desired clock source, and set proper AHB clock 
*								prescale value.
* Input				: hclk - HCLK (Hz)
* Output			: None
* Return			: None
* Note				: None
***************************************************************************************/
void SYS0_SystemCoreClockUpdate(uint32_t hclk)
{
	if (hclk > 48000000)
	{
		__FLASH_LPM_FASTEST_MODE;
	}
	else if (hclk >= 24000000)
	{
		__FLASH_LPM_MEDIUM_MODE;
	}
	else
	{
		__FLASH_LPM_DISABLE;
	}
}

/***********************************************************************************************
* Function		: SYS1_EnableClockout
* Description	: Enable clockout and set proper Clockout	prescale value.
* Input				: src - SYS1_CLOCKOUT_DISABLE, SYS1_CLOCKOUT_ILRC, SYS1_CLOCKOUT_ELS,
*											SYS1_CLOCKOUT_HCLK, SYS1_CLOCKOUT_IHRC, SYS1_CLOCKOUT_EHS
*											SYS1_CLOCKOUT_PLL
*								prescale - SYS1_CLOCKOUT_DIV1, SYS1_CLOCKOUT_DIV2, ... , SYS1_CLOCKOUT_DIV128
* Output			: None
* Return			: None
* Note				: None
***********************************************************************************************/
void SYS1_EnableClockout(uint32_t src, uint32_t prescale)
{
	SN_SYS1->AHBCLKEN_b.CLKOUTSEL = src;	
	SN_SYS1->APBCP1_b.CLKOUTPRE = prescale;
}

/*******************************************************************************************************
* Function		: SYS0_LvdControl
* Description	: Set LVD interrupt, reset and voltage level
* Input				:	LvdEn - SYS0_LVD_ENABLE, SYS0_LVD_DISABLE
*								IntLvl - mskSYS0_LVD_INT_2P1V, ... , mskSYS0_LVD_INT_4P5V
*								RstEn - SYS0_LVD_RESET_ENABLE, SYS0_LVD_RESET_DISABLE
*								RstLvl - mskSYS0_LVD_RESET_2P1V, mskSYS0_LVD_RESET_2P5V, ... , mskSYS0_LVD_RESET_4P5V
* Output			: None
* Return			: None
* Note				: User can modify whether LVD interrupt is enabled or not (ie., just polling) on demand.
*******************************************************************************************************/
void SYS0_LvdControl(uint32_t LvdEn, uint32_t IntLvl, uint32_t RstEn, uint32_t RstLvl)
{
	__SYS0_SET_LVD_DISABLE;									//Disable LVD
	
	if (LvdEn == SYS0_LVD_ENABLE)
	{
		if (RstEn == SYS0_LVD_RESET_ENABLE)
		{
			SN_SYS0->LVDCTRL |= (IntLvl | RstLvl);		//Set LVD Interrupt & Reset voltage level
			__SYS0_SET_LVD_RESET_ENABLE;
		}
		else
		{
			__SYS0_SET_LVD_RESET_DISABLE;
			SN_SYS0->LVDCTRL |= IntLvl;								//Set LVD Interrupt voltage level
		}

		//<-------------------- TODO: User can Enable/Disable on demand BEGIN -------------------->
		//NVIC_ClearPendingIRQ(LVD_IRQn);
		//NVIC_EnableIRQ(LVD_IRQn);
		//<-------------------- TODO: User can Enable/Disable on demand END 	-------------------->

		__SYS0_SET_LVD_ENABLE;			//Enable LVD
	}
	else
		NVIC_DisableIRQ(LVD_IRQn);
}

/*****************************************************************************
* Function		: LVD_IRQHandler
* Description	: ISR of LVD interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq	void LVD_IRQHandler(void)
{
	__SYS0_CLEAR_LVD_RESET;
}

