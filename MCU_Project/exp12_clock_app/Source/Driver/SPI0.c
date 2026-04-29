/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	SPI0 related functions.
*____________________________________________________________________________
*	REVISION	Date				User		Description
*	1.0				2023/11/06	SA1			1. First release
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
#include "SPI.h"
#include "Utility.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: SPI0_Init
* Description	: Initialization of SPI0
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void SPI0_Init(void)
{
	//Enable HCLK for SPI0
	SN_SYS1->AHBCLKEN_b.SPI0CLKEN = 1;							//Enable clock for SPI0.

	//SPI0 setting
	SN_SPI0->CTRL0_b.DL = SPI_DL_8;									//3 ~ 16 Data length
	SN_SPI0->CTRL0_b.MS = SPI_MS_MASTER_MODE;				//Master/Slave selection bit
	SN_SPI0->CTRL0_b.LOOPBACK = SPI_LOOPBACK_DIS; 	//Loop back mode
	SN_SPI0->CTRL0_b.SDODIS = SPI_SDODIS_EN; 				//Slave data output 
																									//(ONLY used in slave mode)

	SN_SPI0->CLKDIV_b.DIV = (SPI_DIV / 2) - 1;			//SPIn clock divider

	//SPI0 SPI mode
	SN_SPI0->CTRL1 = mskSPI_CPHA_FALLING_EDGE|			//Clock phase for edge sampling
									 mskSPI_CPOL_SCK_IDLE_LOW|			//Clock polarity selection bit
									 mskSPI_MLSB_MSB;								//MSB/LSB selection bit

	//SPI0 SEL0 setting
	SN_SPI0->CTRL0_b.SELDIS = SPI_SELDIS_DIS; 			//Auto-SEL disable bit

	//SPI0 Fifo reset
	__SPI0_FIFO_RESET;

//NVIC_ClearPendingIRQ(SPI0_IRQn);
//NVIC_EnableIRQ(SPI0_IRQn);
	
	__SPI0_DATA_FETCH_HIGH_SPEED;									//Enable if Freq. of SCK > 6MHz

	//SPI0 enable	
	SN_SPI0->CTRL0_b.SPIEN  = SPI_SPIEN_EN;    			//SPI enable bit	
}



/*****************************************************************************
* Function		: SPI0_Enable
* Description	: SPI0 enable setting
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void SPI0_Enable(void)
{
	SN_SYS1->AHBCLKEN_b.SPI0CLKEN = 1;							//Enable clock for SPI0.
  SN_SPI0->CTRL0_b.SPIEN = SPI_SPIEN_EN;    			//SPI enable bit
	__SPI0_FIFO_RESET;
}

/*****************************************************************************
* Function		: SPI0_Disable
* Description	: SPI0 disable setting
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void SPI0_Disable(void)
{
  SN_SPI0->CTRL0_b.SPIEN  = SPI_SPIEN_DIS;    		//SPI disable bit
	SN_SYS1->AHBCLKEN_b.SPI0CLKEN = 0;							//Disable clock for SPI0.
}

/*****************************************************************************
* Function		: SPI0_Disable
* Description	: SPI0 disable setting
* Input			: w_TxRxDMAEnable - mskSPI_RX_DMA_EN / mskSPI_TX_DMA_EN
*						: w_DMASize - Total DMA transfer Size (unit: Data length of SPI)
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void SPI0_DMAEnable(uint32_t w_TxRxDMAEnable, uint32_t w_DMASize)
{
	if((w_TxRxDMAEnable & (mskSPI_RX_DMA_EN | mskSPI_TX_DMA_EN)) != 0)
		SN_SPI0->DMA = w_TxRxDMAEnable | w_DMASize;
	else
		SN_SPI0->DMA = 0;
}
/*****************************************************************************
* Function		: SPI0_RW
* Description	: SPI0 read and write
* Input			: dat: data to be write
* Output		: None
* Return		: read data
* Note			: None
*****************************************************************************/
uint8_t SPI0_RW(uint8_t dat)
{
	SN_SPI0->DATA = dat;
	while(SN_SPI0->STAT_b.BUSY);
	
	return SN_SPI0->DATA;
}

