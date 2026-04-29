#ifndef __SN32F400_SPI_H
#define __SN32F400_SPI_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
Base Address: 0x4001 C000 (SPI0)

*/		

/* SPI n Control register 0 <SPIn_CTRL0> (0x00) */
																			//[0:0] SPI enable bit
#define	SPI_SPIEN_DIS 					0			//Disable
#define	SPI_SPIEN_EN  					1			//Enable
#define mskSPI_SPIEN_DIS				(SPI_SPIEN_DIS << 0)
#define	mskSPI_SPIEN_EN 				(SPI_SPIEN_EN << 0)

																			//[1:1] Loop back mode disable
#define	SPI_LOOPBACK_DIS				0			//Disable
#define	SPI_LOOPBACK_EN					1			//Data input from data output
#define mskSPI_LOOPBACK_DIS			(SPI_LOOPBACK_DIS << 1)
#define	mskSPI_LOOPBACK_EN 			(SPI_LOOPBACK_EN << 1)

																			//[2:2] Slave data output disable bit (ONLY used in slave mode)
#define	SPI_SDODIS_EN						0 		//Enable slave data output
#define	SPI_SDODIS_DIS					1 		//Disable slave data output. (MISO=0)
#define mskSPI_SDODIS_EN				(SPI_SDODIS_EN << 2)
#define	mskSPI_SDODIS_DIS 			(SPI_SDODIS_DIS << 2)

#define	SPI_MS_MASTER_MODE  		0			//[3:3] Master/Slave selection bit
#define	SPI_MS_SLAVE_MODE  			1			
#define mskSPI_MS_MASTER_MODE		(SPI_MS_MASTER_MODE << 3)
#define	mskSPI_MS_SLAVE_MODE 		(SPI_MS_SLAVE_MODE << 3)

																			//[7:6] SPI FSM and FIFO Reset bit
#define	SPI_FRESET_DO_NOTHING		0			//Do nothing																	
#define	SPI_FRESET_RESET_FIFO		3			//Reset finite state machine and FIFO
#define mskSPI_FRESET_DO_NOTHING	(SPI_FRESET_DO_NOTHING << 6)
#define	mskSPI_FRESET_RESET_FIFO 	(SPI_FRESET_RESET_FIFO << 6)

#define	SPI_DL_3 								2			//[11:8] Data Length = DL[3:0]+1
#define	SPI_DL_4 								3		
#define	SPI_DL_5 								4		
#define	SPI_DL_6 								5		
#define	SPI_DL_7 								6		
#define	SPI_DL_8 								7		
#define	SPI_DL_9 								8	
#define	SPI_DL_10 							9		
#define	SPI_DL_11								10	
#define	SPI_DL_12								11	
#define	SPI_DL_13 							12	
#define	SPI_DL_14 							13	
#define	SPI_DL_15 							14	
#define	SPI_DL_16 							15	

#define	SPI_TXFIFOTH_0					0		//[14:12]TX FIFO Threshold level
#define	SPI_TXFIFOTH_1					1		
#define	SPI_TXFIFOTH_2					2		
#define	SPI_TXFIFOTH_3					3		
#define	SPI_TXFIFOTH_4					4		
#define	SPI_TXFIFOTH_5					5		
#define	SPI_TXFIFOTH_6					6		
#define	SPI_TXFIFOTH_7					7		

#define	SPI_RXFIFOTH_0					0		//[17:15]RX FIFO Threshold level
#define	SPI_RXFIFOTH_1					1		
#define	SPI_RXFIFOTH_2					2		
#define	SPI_RXFIFOTH_3					3		
#define	SPI_RXFIFOTH_4					4		
#define	SPI_RXFIFOTH_5					5		
#define	SPI_RXFIFOTH_6					6		
#define	SPI_RXFIFOTH_7					7		

																		//[18:18]Auto-SEL disable bit. For SPI mode only.
#define	SPI_SELDIS_EN						0		//Enable Auto-SEL flow control
#define	SPI_SELDIS_DIS					1		//Disable Auto-SEL flow control
#define	mskSPI_SELDIS_EN 				(SPI_SELDIS_EN << 18)
#define	mskSPI_SELDIS_DIS 			(SPI_SELDIS_DIS << 18)

/* SPI n Control register 1 <SPIn_CTRL1> (0x04) */
																		//[0:0]MSB/LSB selection bit
#define	SPI_MLSB_MSB						0		//MSB transmit first
#define	SPI_MLSB_LSB						1		//LSB transmit first
#define	mskSPI_MLSB_MSB 				(SPI_MLSB_MSB << 0)
#define	mskSPI_MLSB_LSB 				(SPI_MLSB_LSB << 0)

																		//[1:1]Clock polarity selection bit
#define	SPI_CPOL_SCK_IDLE_LOW		0		//SCK idles at Low level
#define	SPI_CPOL_SCK_IDLE_HIGH	1		//SCK idles at High level
#define	mskSPI_CPOL_SCK_IDLE_LOW 	(SPI_CPOL_SCK_IDLE_LOW << 1)
#define	mskSPI_CPOL_SCK_IDLE_HIGH (SPI_CPOL_SCK_IDLE_HIGH << 1)

																		//[2:2]Clock phase for edge sampling
#define	SPI_CPHA_FALLING_EDGE		0		//Data changes at clock falling edge
#define	SPI_CPHA_RISING_EDGE		1		//Data changes at clock rising edge
#define	mskSPI_CPHA_FALLING_EDGE 	(SPI_CPHA_FALLING_EDGE << 2)
#define	mskSPI_CPHA_RISING_EDGE		(SPI_CPHA_RISING_EDGE << 2)


/* SPI n Clock Divider register <SPIn_CLKDIV> (0x08) */
																		//[7:0]SPIn clock divider
#define	SPI_DIV  								2		//MCLK/n, n = 2, 4, 6, 8, ...,512


/* SPI n Status register <SPIn_STAT> (0x0C) */
#define mskSPI_TX_EMPTY					(0x1 << 0)		//TX FIFO empty flag
#define mskSPI_TX_FULL					(0x1 << 1)		//TX FIFO full flag
#define mskSPI_RX_EMPTY					(0x1 << 2)		//RX FIFO empty flag
#define mskSPI_RX_FULL					(0x1 << 3)		//RX FIFO full flag
#define mskSPI_BUSY							(0x1 << 4)		//Busy flag
#define mskSPI_TXFIFOTHF				(0x1 << 5)		//TX FIFO threshold flag
#define mskSPI_RXFIFOTHF				(0x1 << 6)		//RX FIFO threshold flag


/* SPI n Interrupt Enable register <SPIn_IE> (0x10) */
#define	SPI_RXOVFIE_DIS					0		//[0:0]RX Overflow interrupt enable
#define	SPI_RXOVFIE_EN					1
#define	mskSPI_RXOVFIE_DIS 			(SPI_RXOVFIE_DIS << 0)
#define	mskSPI_RXOVFIE_EN				(SPI_RXOVFIE_EN << 0)

#define	SPI_RXTOIE_DIS					0		//[1:1]RX time-out interrupt enable
#define	SPI_RXTOIE_EN						1
#define	mskSPI_RXTOIE_DIS 			(SPI_RXTOIE_DIS << 1)
#define	mskSPI_RXTOIE_EN				(SPI_RXTOIE_EN << 1)

#define	SPI_RXFIFOTHIE_DIS			0		//[2:2]RX FIFO threshold interrupt enable
#define	SPI_RXFIFOTHIE_EN				1
#define	mskSPI_RXFIFOTHIE_DIS 	(SPI_RXFIFOTHIE_DIS << 2)
#define	mskSPI_RXFIFOTHIE_EN		(SPI_RXFIFOTHIE_EN << 2)

#define	SPI_TXFIFOTHIE_DIS			0		//[3:3]TX FIFO threshold interrupt enable
#define	SPI_TXFIFOTHIE_EN				1
#define	mskSPI_TXFIFOTHIE_DIS 	(SPI_TXFIFOTHIE_DIS << 3)
#define	mskSPI_TXFIFOTHIE_EN		(SPI_TXFIFOTHIE_EN << 3)

#define SPI_TXUDFIE_DIS					0		//[4:4]TX underflow interrupt enable
#define SPI_TXUDFIE_EN					1
#define mskSPI_TXUDFIE_DIS			(SPI_TXUDFIE_DIS << 4)
#define mskSPI_TXUDFIE_EN				(SPI_TXUDFIE_EN << 4)

#define SPI_TXEMPIE_DIS					0		//[5:5]TX all empty interrupt enable
#define SPI_TXEMPIE_EN					1
#define	mskSPI_TXEMPIE_DIS			(SPI_TXEMPIE_DIS << 5)
#define mskSPI_TXEMPIE_EN				(SPI_TXEMPIE_EN << 5)

/* SPI n Raw Interrupt Status register <SPIn_RIS> (0x14) */
/* SPI n Interrupt Clear register <SPIn_IC> (0x18) */
#define mskSPI_RXOVFIF					(0x1 << 0)	//[0:0]RX overflow interrupt flag
#define mskSPI_RXOVFIC					mskSPI_RXOVFIF

#define mskSPI_RXTOIF						(0x1 << 1)	//[1:1]RX time-out interrupt flag
#define mskSPI_RXTOIC						mskSPI_RXTOIF

#define mskSPI_RXFIFOTHIF				(0x1 << 2)	//[2:2]RX FIFO threshold interrupt flag
#define mskSPI_RXFIFOTHIC				mskSPI_RXFIFOTHIF

#define mskSPI_TXFIFOTHIF				(0x1 << 3)	//[3:3]TX FIFO threshold interrupt flag
#define mskSPI_TXFIFOTHIC				mskSPI_TXFIFOTHIF

#define mskSPI_TXUDFIF					(0x1 << 4)	//[4:4]TX underflow interrupt enable
#define mskSPI_TXUDFIC					mskSPI_TXUDFIF

#define mskSPI_TXEMPIF					(0x1 << 5)	//[5:5]TX all empty interrupt enable
#define mskSPI_TXEMPIC					mskSPI_TXEMPIF

/*  SPI n Data Fetch register <SPIn_DF> (0x20) */
																						//[0:0]SPI data fetch control bit
#define	SPI_DF_DIS							0						//Disable
#define	SPI_DF_EN								1						//Enable when SCKn frequency > 6MHz
#define	mskSPI_DF_DIS						(SPI_DF_DIS << 0)
#define	mskSPI_SPI_DF_EN				(SPI_DF_EN << 0)

/* SPI n FIFO threshold register <SPIn_FIFO_TH> (0x24) */
																						//[3:0]TX FIFO Threshold level
#define	SPI_NEW_TXFIFOTH_0			0	
#define	SPI_NEW_TXFIFOTH_1			1		
#define	SPI_NEW_TXFIFOTH_2			2		
#define	SPI_NEW_TXFIFOTH_3			3		
#define	SPI_NEW_TXFIFOTH_4			4		
#define	SPI_NEW_TXFIFOTH_5			5		
#define	SPI_NEW_TXFIFOTH_6			6		
#define	SPI_NEW_TXFIFOTH_7			7	
#define	SPI_NEW_TXFIFOTH_8			8	
#define	SPI_NEW_TXFIFOTH_9			9		
#define	SPI_NEW_TXFIFOTH_10		 10		
#define	SPI_NEW_TXFIFOTH_11		 11		
#define	SPI_NEW_TXFIFOTH_12		 12		
#define	SPI_NEW_TXFIFOTH_13		 13		
#define	SPI_NEW_TXFIFOTH_14		 14		
#define	SPI_NEW_TXFIFOTH_15		 15	
																						//[19:16]RX FIFO Threshold level
#define	SPI_NEW_RXFIFOTH_0			0	
#define	SPI_NEW_RXFIFOTH_1			1		
#define	SPI_NEW_RXFIFOTH_2			2		
#define	SPI_NEW_RXFIFOTH_3			3		
#define	SPI_NEW_RXFIFOTH_4			4		
#define	SPI_NEW_RXFIFOTH_5			5		
#define	SPI_NEW_RXFIFOTH_6			6		
#define	SPI_NEW_RXFIFOTH_7			7	
#define	SPI_NEW_RXFIFOTH_8			8	
#define	SPI_NEW_RXFIFOTH_9			9		
#define	SPI_NEW_RXFIFOTH_10		 10		
#define	SPI_NEW_RXFIFOTH_11		 11		
#define	SPI_NEW_RXFIFOTH_12		 12		
#define	SPI_NEW_RXFIFOTH_13		 13		
#define	SPI_NEW_RXFIFOTH_14		 14		
#define	SPI_NEW_RXFIFOTH_15		 15	
																						//[31:31]Use new TX/RX threshold setting
#define	SPI_NEW_TH_DIS					0U					//Disable
#define	SPI_NEW_TH_EN						1U					//Enable
#define	mskSPI_NEW_TH_DIS				(SPI_NEW_TH_DIS << 31)
#define	mskSPI_NEW_TH_EN				(SPI_NEW_TH_EN << 31)


/* SPI n DMA mode register <SPIn_DMA> (0x50) */
																						//[30:30]RX DMA enable
#define	SPI_RX_DMA_DIS					0 					//Disable
#define	SPI_RX_DMA_EN						1 					//Enable
#define	mskSPI_RX_DMA_DIS				(SPI_RX_DMA_DIS << 30)
#define	mskSPI_RX_DMA_EN				(SPI_RX_DMA_EN << 30)
																						//[31:31]TX DMA enable
#define	SPI_TX_DMA_DIS					0U					//Disable
#define	SPI_TX_DMA_EN						1U					//Enable
#define	mskSPI_TX_DMA_DIS				(SPI_TX_DMA_DIS << 31)
#define	mskSPI_TX_DMA_EN				(SPI_TX_DMA_EN << 31)

/* SPI n ARGB CTRL register <SPIn_ARGBCTRL> (0x58) */
																						//[0:0]ARGB mode enable
#define	SPI_ARGBM_DIS						0 					//Disable
#define	SPI_ARGBM_EN						1 					//Enable
#define	mskSPI_ARGBM_DIS				(SPI_ARGBM_DIS << 0)
#define	mskSPI_ARGBM_EN					(SPI_ARGBM_EN << 0)


/*_____ M A C R O S ________________________________________________________*/
#define	__SPI0_FIFO_RESET				{SN_SPI0->CTRL0_b.FRESET = SPI_FRESET_RESET_FIFO;while(SN_SPI0->CTRL0_b.FRESET == SPI_FRESET_RESET_FIFO);}
#define	__SPI0_CLR_SEL0					(SN_GPIO0->DATA_b.DATA1 = 0)
#define	__SPI0_SET_SEL0					(SN_GPIO0->DATA_b.DATA1 = 1)

//SPI Data Fetch speed (High: SCK > 6MHz)
#define	__SPI0_DATA_FETCH_HIGH_SPEED	(SN_SPI0->DFDLY = SPI_DF_EN)

/*_____ D E C L A R A T I O N S ____________________________________________*/
void SPI0_Init(void);
void SPI0_Enable(void);
void SPI0_Disable(void);
void SPI0_DMAEnable(uint32_t, uint32_t);
uint8_t SPI0_RW(uint8_t dat);
#endif	/*__SN32F400_SPI_H*/

