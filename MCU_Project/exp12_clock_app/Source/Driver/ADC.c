/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	ADC related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2023/11/07	SA1			1. First release
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
#include "ADC.h"
#include "Utility.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/


/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: ADC_IRQHandler
* Description	: ISR of ADC interrupt
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
__irq void ADC_IRQHandler(void)
{
	SN_ADC->IC = 0xFFFFFFF;
}

/*****************************************************************************
* Function		: ADC_FuncInit
* Description	: Initialization of ADC
* Input			: bPCLKDiv - ADC_DIV1, ADC_DIV2, ..., ADC_DIV32
* 						bADCLen - ADC_8BIT, ADC_12BIT
*							bCHMode - Single_Channel, Multiple_Channel
*							bSCMode - Single_Mode, Continuous_Mode
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void ADC_FuncInit(uint8_t bPCLKDiv, uint8_t bADCLen, uint8_t bCHMode, uint8_t bSCMode)
{
	__ADC_ENABLE_HCLK;																	//Enables HCLK for ADC
	
	SN_ADC->ADM_b.AVREFHSEL = ADC_AVREFHSEL_INTERNAL;		//Set ADC high reference voltage source from internal reference
	SN_ADC->ADM_b.VHS = ADC_VHS_INTERNAL_2V_AIN18;			//Set ADC high reference voltage source as Internal VDD
	SN_ADC->ADM_b.OVRMODE = ADC_OVRMODE_OVERWRITE;			//Set ADC FIFO overwrite with the fifo
	SN_ADC->ADM_b.GCHS = ADC_GCHS_EN;										//Enable ADC global channel	

	SN_ADC->ADM_b.ADLEN = bADCLen;											//Set ADC resolution = 12-bit			

	SN_ADC->ADM_b.ADCKS = bPCLKDiv;											//ADC_CLK = ADC_PCLK/32

	SN_ADC->CONVCTRL_b.SCMODE = bSCMode;								//Set mode
	
	SN_ADC->CONVCTRL_b.CH = bCHMode;										//Set converting channel
	
	SN_ADC->ADM_b.ADENB = ADC_ADENB_EN;									//Enable ADC

	UT_DelayNx10us(10);																	//Delay 100us
	
	SN_ADC->ADM1_b.ACS = ENABLE;												//Calibration start
	while (SN_ADC->ADM1_b.ACS == 1);
	
	SN_ADC->ADM1_b.CALIVALENB = ENABLE;									//ADC conversion with calibration value
}

/*****************************************************************************
* Function		: ADC_Read
* Description	: Read ADC converted data
* Input			: None
* Output		: None
* Return		: Data in ADB register
* Note			: None
*****************************************************************************/
uint16_t ADC_Read(void)
{
	return 0;
}

/*****************************************************************************
* Function		: ADC_DMA_Start
* Description	: Start ADC DMA function
* Input			: bADCCh - ADC_CHS_AIN0, ADC_CHS_AIN1, ..., ADC_CHS_AIN21
*							bADCDMAFifoTh - ADC_DMA_FIFO_TH_0, ADC_DMA_FIFO_TH_1 ...
*							wADCDMASize - Total DMA transfer size
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void ADC_DMA_Start(uint16_t hwADCCh, uint8_t bADCDMAFifoTh, uint32_t wADCDMASize)
{
	//Set Convert Channel
	SN_ADC->CONVCTRL = ((SN_ADC->CONVCTRL & 0xFFC00000) | hwADCCh);
	
	SN_ADC->DMA_b.DMA_EN = ADC_DMA_DIS;
	
	//Set ADC FIFO Threshold level & Total DMA transfer size
	SN_ADC->DMA_b.DMA_FIFO_TH = bADCDMAFifoTh;
	SN_ADC->DMA_b.DMA_SIZE = wADCDMASize;
	
	//Enable ADC DMA mode enable	
	SN_ADC->DMA_b.DMA_EN = ADC_DMA_EN;
	
	//Start to execute ADC converting
	SN_ADC->ADM_b.ADS = ADC_ADS_START;
}
