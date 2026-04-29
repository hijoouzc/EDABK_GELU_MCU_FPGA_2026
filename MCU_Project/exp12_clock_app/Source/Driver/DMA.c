/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	DMA related functions.
*____________________________________________________________________________
*	REVISION	Date				User	Description
*	1.0				2023/11/06	SA1		First release
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
#include "DMA.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
DMA_IntFlagSt stDMA0IntFlag[eDMA_CH_MAX];

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/
// Get channel register shift address, unit:32 bit address
#define CHADDRSHIFT 0x08
//Channel shift address = ((uint32_t)(&un_DMAn[b_DMAn].ptrStDMA0->C1_CSR) - (uint32_t)(&un_DMAn[b_DMAn].ptrStDMA0->C0_CSR))>>2;

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: DMA_Init
* Description	: Initialization of DMAn
* Input				: struct_ptrDMAConfig - Configuration of DMAn
*							: b_CHn - eDMA_CH0(0x00), eDMA_CH0(0x01) ... eDMA_CH4(0x04)
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void DMA_Init (DMA_InitSt* struct_ptrDMAConfig, uint8_t b_CHn)
{
	uint32_t w_CSR_Buf, w_CFG_Buf;
	uint32_t *ptrDMA_Reg;
	uint8_t b_Mode;
	
	SN_SYS1->AHBCLKEN |= mskDMA_CLK_EN;
	
	if((struct_ptrDMAConfig->b_SrcMode == DMA_SRC_PERIPHERAL) || (struct_ptrDMAConfig->b_DstMode == DMA_DST_PERIPHERAL))
		b_Mode = DMA_MODE_PERIPHERAL;
	else
		b_Mode = DMA_MODE_MEMORY;
	
	//Set CSR register buffer
	w_CSR_Buf = ( (struct_ptrDMAConfig->b_DstAddrCtrl << 	3)   // Destination Address Control
							| (struct_ptrDMAConfig->b_SrcAddrCtrl << 	5)   // Source Address Control
							| (b_Mode << 7)                                // Support Hardware Handshake Mode
							| (struct_ptrDMAConfig->b_DstWidth 		<< 	8)   // Destination transfer width
							| (struct_ptrDMAConfig->b_SrcWidth 		<< 11)   // Source transfer width
							| (struct_ptrDMAConfig->b_BurstSize 	<< 16)   // Source burst size selection
							| (struct_ptrDMAConfig->b_Priority 		<< 22)); // Channel priority level
	
	//Set CFG register buffer
	w_CFG_Buf = ((struct_ptrDMAConfig->b_IntTCEn 		<< 0)			 // Terminal count interrupt 
						 | (struct_ptrDMAConfig->b_IntABTEn 	<< 2)      // Mask abort interrupt 
						 | (struct_ptrDMAConfig->b_SrcMode 		<< 7)      // Source Peripheral Mode enable
						 | (struct_ptrDMAConfig->b_DstMode 		<< 13)     // Destination Peripheral Mode enable
						 | (struct_ptrDMAConfig->b_SrcReqSel 	<< 16)     // Source DMA request select
						 | (struct_ptrDMAConfig->b_DstReqSel 	<< 24));   // Destination DMA request select
	
	SN_DMA0->MCSR_b.DMACEN = 1;
	
	//Set DMA CSR & CFG Register
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_CSR + (CHADDRSHIFT * b_CHn));
	*ptrDMA_Reg = w_CSR_Buf;
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_CFG + (CHADDRSHIFT * b_CHn));
	*ptrDMA_Reg = w_CFG_Buf;
	
	// Enable NVIC if INT_TC_MSK or INT_ABT_MSK = No mask
	if((struct_ptrDMAConfig->b_IntTCEn == DMA_INT_TC_MSK_DIS) | (struct_ptrDMAConfig->b_IntABTEn == DMA_INT_ABT_MSK_DIS))
		NVIC_EnableIRQ(DMA0_IRQn);
}

/*****************************************************************************
* Function		: DMA_Start
* Description	: Start DMA channel transfer
* Input				: struct_ptrDMAstart - Configuration of DMAn
*							: b_CHn - eDMA_CH0(0x00), eDMA_CH0(0x01) ... eDMA_CH4(0x04)
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void DMA_Start (DMA_StartSt* struct_ptrDMAstart, uint8_t b_CHn)
{
	uint32_t *ptrDMA_Reg;
	
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_DSTADDR + (CHADDRSHIFT * b_CHn));
	*ptrDMA_Reg = struct_ptrDMAstart->w_DstAddr;
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_SRCADDR + (CHADDRSHIFT * b_CHn));
	*ptrDMA_Reg = struct_ptrDMAstart->w_SrcAddr;
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_SIZE + (CHADDRSHIFT * b_CHn));
	*ptrDMA_Reg = struct_ptrDMAstart->w_TotalSize;
	
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_CSR + (CHADDRSHIFT * b_CHn));
	*ptrDMA_Reg |= mskDMA_CH_EN;
}

/*****************************************************************************
* Function		: DMA_Abort
* Description	: DMA channel abort 
* Input				: b_CHn - eDMA_CH0(0x00), eDMA_CH0(0x01) ... eDMA_CH4(0x04)
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void DMA_Abort(uint8_t b_CHn)
{
	uint32_t *ptrDMA_Reg;
	
	ptrDMA_Reg = (uint32_t *)(&SN_DMA0->C0_CSR + (CHADDRSHIFT * b_CHn));
	
	*ptrDMA_Reg |= mskDMA_ABT;
}

/*****************************************************************************
* Function		: DMA_UnInit
* Description	: Uninitialization of DMAn 
* Input				: None
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
void DMA_UnInit (void)
{
	SN_SYS1->PRST_b.DMA0RST = 1;
	SN_SYS1->AHBCLKEN &= (~mskDMA_CLK_EN);
	NVIC_DisableIRQ(DMA0_IRQn);
}

/*****************************************************************************
* Function		: DMA_IRQHandler
* Description	: DMA ISR 
* Input				: None
* Output			: None
* Return			: None
* Note				: None
*****************************************************************************/
__irq void DMA_IRQHandler(void)
{
	uint8_t b_DMACHn;
	uint32_t w_INT_Buf, w_INT_TC_Buf, w_INT_ERR_ABT_Buf;
	
	w_INT_Buf = SN_DMA0->INT;
	w_INT_TC_Buf = SN_DMA0->INT_TC;
	w_INT_ERR_ABT_Buf = SN_DMA0->INT_ABT;
	
	for(b_DMACHn = 0 ; b_DMACHn < eDMA_CH_MAX ; b_DMACHn++)
	{
		// Check DMA_INT for every channel
		if(w_INT_Buf & (mskDMA_INT0 << b_DMACHn))
		{
			// Check DMA_INT_TC and set TC Flag
			if(w_INT_TC_Buf & (mskDMA_INT_TC0 << b_DMACHn))
			{
				SN_DMA0->INT_TC_CLR = mskDMA_INT_TC_CLR0 << b_DMACHn;
				stDMA0IntFlag[b_DMACHn].Flag.bits.TC = 1;
			}
			// Check DMA_INT_ABT and set ABT Flag
			if(w_INT_ERR_ABT_Buf & (mskDMA_INT_ABT0 << b_DMACHn))
			{
				SN_DMA0->INT_ABT_CLR = mskDMA_INT_ABT_CLR0 << b_DMACHn;
				stDMA0IntFlag[b_DMACHn].Flag.bits.ABT = 1;
			}
		}
	}
}
