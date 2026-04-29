#ifndef __SN32F400_DMA_H
#define __SN32F400_DMA_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdint.h>
#include <SN32F400.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
Base Address: 0x4007 2000 (DMA0)
*/		

enum DMACHm_e{
	eDMA_CH0,
	eDMA_CH1,
	eDMA_CH2,
	eDMA_CH3,
	eDMA_CH4,
	eDMA_CH5,
	eDMA_CH_MAX
};

/* SYS1_AHBCLKEN */
#define	mskDMA_CLK_EN								(0x01 << 2)

/* DMA n Interrupt Status register <DMAn_INT> (0x00) */
																											// [4:0] The result of INT_ABTn | INT_TCn
#define mskDMA_INT4								(0x01 << 4)					
#define mskDMA_INT3								(0x01 << 3)					
#define mskDMA_INT2								(0x01 << 2)					
#define mskDMA_INT1								(0x01 << 1)					
#define mskDMA_INT0								(0x01 << 0)					

/* DMA n Transfer Complete Interrupt Status register <DMAn_INT_TC> (0x04) */
																											// [4:0] Status of the DMA CHn terminal count interrupts after masking
#define mskDMA_INT_TC4						(0x01 << 4)	 
#define mskDMA_INT_TC3						(0x01 << 3)	 
#define mskDMA_INT_TC2						(0x01 << 2)	 
#define mskDMA_INT_TC1						(0x01 << 1)	 
#define mskDMA_INT_TC0						(0x01 << 0)	 

/* DMA n Transfer Complete Interrupt Status Clear register <DMAn_INT_TC_CLR> (0x08) */
																											// [4:0] Write 1 to clear the INT_TCn and TCn status
#define mskDMA_INT_TC_CLR4				(0x01 << 4)
#define mskDMA_INT_TC_CLR3				(0x01 << 3)
#define mskDMA_INT_TC_CLR2				(0x01 << 2)
#define mskDMA_INT_TC_CLR1				(0x01 << 1)
#define mskDMA_INT_TC_CLR0				(0x01 << 0)

/* DMA n Abort Interrupt Status register <DMAn_INT_ABT> (0x0C) */
																											// [20:16] Status of the DMA CHn abort interrupts after masking
#define mskDMA_INT_ABT4						(0x01 << 20)
#define mskDMA_INT_ABT3						(0x01 << 19)
#define mskDMA_INT_ABT2						(0x01 << 18)
#define mskDMA_INT_ABT1						(0x01 << 17)
#define mskDMA_INT_ABT0						(0x01 << 16)

/* DMA n Abort Interrupt Status Clear register <DMAn_INT_ABT_CLR> (0x10) */
																											// [20:16] Write 1 to clear the INT_ABT4 and ABT4 status
#define mskDMA_INT_ABT_CLR4				(0x01 << 20)
#define mskDMA_INT_ABT_CLR3				(0x01 << 19)
#define mskDMA_INT_ABT_CLR2				(0x01 << 18)
#define mskDMA_INT_ABT_CLR1				(0x01 << 17)
#define mskDMA_INT_ABT_CLR0				(0x01 << 16)

/* DMA n Transfer Complete Status register <DMAn_TC> (0x14) */
																											// [4:0] Status of the DMA terminal count
#define mskDMA_TC4								(0x01 << 4)
#define mskDMA_TC3								(0x01 << 3)
#define mskDMA_TC2								(0x01 << 2)
#define mskDMA_TC1								(0x01 << 1)
#define mskDMA_TC0								(0x01 << 0)

/* DMA n Abort Status register <DMAn_ABT> (0x18) */
																											// [20:16] Status of the DMA abort
#define mskDMA_ABT4								(0x01 << 20)
#define mskDMA_ABT3								(0x01 << 19)
#define mskDMA_ABT2								(0x01 << 18)
#define mskDMA_ABT1								(0x01 << 17)
#define mskDMA_ABT0								(0x01 << 16)

/* DMA n Channel Enable Status register <DMAn_CH_EN> (0x1C) */
																											// [4:0] Status of the channel n CH_EN bit of Cn_CSR register
#define mskDMA_CH_EN4							(0x01 << 4)
#define mskDMA_CH_EN3							(0x01 << 3)
#define mskDMA_CH_EN2							(0x01 << 2)
#define mskDMA_CH_EN1							(0x01 << 1)
#define mskDMA_CH_EN0							(0x01 << 0)

/* DMA n Channel Busy Status register <DMAn_CH_BUSY> (0x20) */
																											// [4:0] Status of the channel n BUSY bit of Cn_CFG register
#define mskDMA_CH_BUSY4						(0x01 << 4)
#define mskDMA_CH_BUSY3						(0x01 << 3)
#define mskDMA_CH_BUSY2						(0x01 << 2)
#define mskDMA_CH_BUSY1						(0x01 << 1)
#define mskDMA_CH_BUSY0						(0x01 << 0)

/* DMA n Main Configuration Status register <DMAn_MCSR> (0x24) */
																											// [0:0] DMA controller enable
#define DMA_DMAC_DIS							0										// Disable
#define DMA_DMAC_EN								1										// Enable
#define mskDMA_DMAC_DIS						(DMA_DMAC_DIS << 0)
#define mskDMA_DMAC_EN						(DMA_DMAC_EN << 0) 

																											// [1:1] AHB Master 0 endian configuration
#define DMA_M0ENDIAN_LITTLE				0 								 	// DMA AHB Master 0 is Little-endian
#define DMA_M0ENDIAN_BIG					1 								 	// DMA AHB Master 0 is Big-endian 
#define mskDMA_M0ENDIAN_LITTLE		(DMA_M0ENDIAN_LITTLE << 1)
#define mskDMA_M0ENDIAN_BIG				(DMA_M0ENDIAN_BIG << 1)

/* DMA n Channel m Control register <DMAn_Cm_CSR> (0x100,0x120,0x140,0x160,0x180) */
																											// [0:0] Channel enable
#define DMA_CH_DIS								0										// Enable
#define DMA_CH_EN									1										// Disable
#define	mskDMA_CH_DIS        			(DMA_CH_DIS << 0)
#define	mskDMA_CH_EN        			(DMA_CH_EN << 0)

																											// [4:3] Destination Address Control
#define DMA_DSTAD_CTL_INC					0										// Increment destination address
#define DMA_DSTAD_CTL_DEC					1										// Decrement destination address
#define DMA_DSTAD_CTL_FIX					2										// Fixed destination address
#define DMA_DSTAD_CTL_CYC					3										// Increment destination address
#define	mskDMA_DSTAD_CTL_INC     	(DMA_DSTAD_CTL_INC << 3)
#define	mskDMA_DSTAD_CTL_DEC     	(DMA_DSTAD_CTL_DEC << 3)
#define	mskDMA_DSTAD_CTL_FIX     	(DMA_DSTAD_CTL_FIX << 3)
#define	mskDMA_DSTAD_CTL_CYC     	(DMA_DSTAD_CTL_CYC << 3)

																											// [6:5] Source Address Control
#define	DMA_SRCAD_CTL_INC     		0        					 	// Increment source address
#define	DMA_SRCAD_CTL_DEC     		1        					 	// Decrement source address
#define	DMA_SRCAD_CTL_FIX     		2        					 	// Fixed source address
#define	DMA_SRCAD_CTL_CYC     		3        					 	// Increment cyclic mode
#define	mskDMA_SRCAD_CTL_INC     	(DMA_SRCAD_CTL_INC << 5)
#define	mskDMA_SRCAD_CTL_DEC     	(DMA_SRCAD_CTL_DEC << 5)
#define	mskDMA_SRCAD_CTL_FIX     	(DMA_SRCAD_CTL_FIX << 5)
#define	mskDMA_SRCAD_CTL_CYC     	(DMA_SRCAD_CTL_CYC << 5)

																											// [7:7] Support Hardware Handshake Mode
#define	DMA_MODE_MEMORY     			0        						// Normal mode for memory to memory
#define	DMA_MODE_PERIPHERAL     	1        						// Hardware Handshake mode for M2P, P2M, P2P
#define	mskDMA_MODE_MEMORY       	(DMA_MODE_MEMORY << 7)
#define	mskDMA_MODE_PERIPHERAL   	(DMA_MODE_PERIPHERAL << 7)

																											// [9:8] Destination transfer width
#define	DMA_DST_WIDTH_8BIT    		0										// Transfer width is 8 bits
#define	DMA_DST_WIDTH_16BIT   		1										// Transfer width is 16 bits
#define	DMA_DST_WIDTH_32BIT   		2										// Transfer width is 32 bits
#define	mskDMA_DST_WIDTH_8BIT    	(DMA_DST_WIDTH_8BIT << 8)
#define	mskDMA_DST_WIDTH_16BIT   	(DMA_DST_WIDTH_16BIT << 8)
#define	mskDMA_DST_WIDTH_32BIT   	(DMA_DST_WIDTH_32BIT << 8)

																											// [12:11] Source transfer width
#define	DMA_SRC_WIDTH_8BIT    		0										// Transfer width is 8 bits
#define	DMA_SRC_WIDTH_16BIT   		1										// Transfer width is 16 bits
#define	DMA_SRC_WIDTH_32BIT   		2										// Transfer width is 32 bits
#define	mskDMA_SRC_WIDTH_8BIT    	(DMA_SRC_WIDTH_8BIT << 11) 
#define	mskDMA_SRC_WIDTH_16BIT   	(DMA_SRC_WIDTH_16BIT << 11) 
#define	mskDMA_SRC_WIDTH_32BIT   	(DMA_SRC_WIDTH_32BIT << 11) 

																											// [15:15] Transaction abort
#define	DMA_ABT										1
#define	mskDMA_ABT            		(DMA_ABT << 15)

																											// [18:16] Source burst size selection
#define	DMA_BURST_1           		0										// Burst Size = 1
#define	DMA_BURST_4           		1										// Burst Size = 4
#define	DMA_BURST_8           		2										// Burst Size = 8
#define	DMA_BURST_16          		3										// Burst Size = 16
#define	DMA_BURST_32          		4										// Burst Size = 32
#define	DMA_BURST_64          		5										// Burst Size = 64
#define	DMA_BURST_128         		6										// Burst Size = 128
#define	DMA_BURST_256         		7										// Burst Size = 256
#define	mskDMA_BURST_1           	(DMA_BURST_1 << 16)  
#define	mskDMA_BURST_4           	(DMA_BURST_4 << 16)  
#define	mskDMA_BURST_8           	(DMA_BURST_8 << 16)  
#define	mskDMA_BURST_16          	(DMA_BURST_16 << 16) 
#define	mskDMA_BURST_32          	(DMA_BURST_32 << 16) 
#define	mskDMA_BURST_64          	(DMA_BURST_64 << 16) 
#define	mskDMA_BURST_128         	(DMA_BURST_128 << 16)
#define	mskDMA_BURST_256         	(DMA_BURST_256 << 16)

																											// [23:22] Channel priority level
#define	DMA_CHPRI_LV0      				0      							// Channel priority level 0
#define	DMA_CHPRI_LV1      				1      							// Channel priority level 1
#define	DMA_CHPRI_LV2      				2      							// Channel priority level 2
#define	DMA_CHPRI_LV3      				3      							// Channel priority level 3
#define	mskDMA_CHPRI_LV0      		(DMA_CHPRI_LV0 << 22) 
#define	mskDMA_CHPRI_LV1      		(DMA_CHPRI_LV1 << 22) 
#define	mskDMA_CHPRI_LV2      		(DMA_CHPRI_LV2 << 22) 
#define	mskDMA_CHPRI_LV3      		(DMA_CHPRI_LV3 << 22) 

																											// [31:31] Terminal count status mask for current transaction
#define DMA_TC_MSK_DIS						0 									// When terminal count happens, TC status register will be set
#define DMA_TC_MSK_EN							1 									// When terminal count happens, TC status register will not be set
#define	mskDMA_TC_MSK_DIS      		(DMA_TC_MSK_DIS << 31)
#define	mskDMA_TC_MSK_EN         	(DMA_TC_MSK_EN << 31) 

/* DMA n Channel m Configuration register <DMAn_Cm_CFG> (0x104,0x124,0x144,0x164,0x184) */
																											// [0:0] Channel terminal count interrupt mask
#define	DMA_INT_TC_MSK_DIS	      0         					// Channel terminal count interrupt no mask
#define	DMA_INT_TC_MSK_EN         1 	      					// Channel terminal count interrupt mask
#define	mskDMA_INT_TC_MSK_DIS     (DMA_INT_TC_MSK_DIS << 0)       
#define	mskDMA_INT_TC_MSK_EN      (DMA_INT_TC_MSK_EN << 0)  

																											// [1:1] Channel abort interrupt mask
#define	DMA_INT_ABT_MSK_DIS     	0      					 		// Channel abort interrupt no mask
#define	DMA_INT_ABT_MSK_EN        1      					 		// Channel abort interrupt mask
#define	mskDMA_INT_ABT_MSK_DIS    (DMA_INT_ABT_MSK_DIS << 2)
#define	mskDMA_INT_ABT_MSK_EN     (DMA_INT_ABT_MSK_EN << 2)

																											// [7:7] Source Peripheral Mode enable
#define	DMA_SRC_MEMORY            0										// Source is memory without hardware handshake
#define	DMA_SRC_PERIPHERAL        1										// Source is peripheral with hardware handshake
#define	mskDMA_SRC_MEMORY         (DMA_SRC_MEMORY << 7)
#define	mskDMA_SRC_PERIPHERAL     (DMA_SRC_PERIPHERAL << 7)

																											// [8:8] The DMA channel is busy
#define	DMA_NOT_BUSY	            0   	    					// The DMA channel is not busy
#define	DMA_BUSY	            		1 	      					// The DMA channel is busy
#define	mskDMA_NOT_BUSY						(DMA_NOT_BUSY << 8)
#define	mskDMA_BUSY								(DMA_BUSY << 8)

																											// [13:13] Destination Peripheral Mode enable
#define	DMA_DST_MEMORY            0					        	// Destination is memory without hardware handshake
#define	DMA_DST_PERIPHERAL        1					        	// Destination is peripheral with hardware handshake
#define	mskDMA_DST_MEMORY         (DMA_DST_MEMORY << 13)
#define	mskDMA_DST_PERIPHERAL     (DMA_DST_PERIPHERAL << 13)

																											// [21:16] Source DMA request select
#define	DMA_SRCRS_NONE			     		0x00    					// NONE for Memory mode
#define	DMA_SRCRS_ADC            		0x00    					// ADC
#define	DMA_SRCRS_SPI0_RX        		0x03    					// SPI0 RX
#define	DMA_SRCRS_UART0_RX       		0x07    					// UART0 RX
#define	DMA_SRCRS_UART1_RX       		0x09    					// UART1 RX
#define	DMA_SRCRS_I2C            		0x0E    					// I2C0
#define	DMA_SRCRS_CT16B0_CAP0    		0x10    					// CT16B0 CAP0
#define	DMA_SRCRS_CT16B0_MR9     		0x11    					// CT16B0 MR9
#define	DMA_SRCRS_CT16B0_MR0     		0x12    					// CT16B0 MR0
#define	DMA_SRCRS_CT16B0_MR1     		0x13    					// CT16B0 MR1
#define	DMA_SRCRS_CT16B0_MR2     		0x14    					// CT16B0 MR2
#define	DMA_SRCRS_CT16B0_MR3     		0x15    					// CT16B0 MR3
#define	DMA_SRCRS_CT16B1_CAP0    		0x16    					// CT16B1 CAP0
#define	DMA_SRCRS_CT16B1_MR9     		0x17    					// CT16B1 MR9
#define	DMA_SRCRS_CT16B1_MR0     		0x18    					// CT16B1 MR0
#define	DMA_SRCRS_CT16B1_MR1     		0x19    					// CT16B1 MR1
#define	DMA_SRCRS_CT16B1_MR2     		0x1A    					// CT16B1 MR2
#define	DMA_SRCRS_CT16B1_MR3     		0x1B    					// CT16B1 MR3
#define	DMA_SRCRS_CT16B5_CAP0    		0x2A    					// CT16B5 CAP0
#define	DMA_SRCRS_CT16B5_MR9     		0x2B    					// CT16B5 MR9
#define	DMA_SRCRS_CT16B5_MR0     		0x2C    					// CT16B5 MR0
#define	DMA_SRCRS_CT16B5_MR1     		0x2D    					// CT16B5 MR1
#define	DMA_SRCRS_CT16B5_MR2     		0x2E    					// CT16B5 MR2
#define	DMA_SRCRS_CT16B5_MR3     		0x2F    					// CT16B5 MR3
#define	mskDMA_SRCRS_NONE			      (DMA_SRCRS_NONE << 16)
#define	mskDMA_SRCRS_ADC            (DMA_SRCRS_ADC << 16)
#define	mskDMA_SRCRS_SPI0_RX        (DMA_SRCRS_SPI0_RX << 16)
#define	mskDMA_SRCRS_UART0_RX       (DMA_SRCRS_UART0_RX << 16)
#define	mskDMA_SRCRS_UART1_RX       (DMA_SRCRS_UART1_RX << 16)
#define	mskDMA_SRCRS_I2C            (mskDMA_SRCRS_I2C << 16)           
#define	mskDMA_SRCRS_CT16B0_CAP0    (mskDMA_SRCRS_CT16B0_CAP0 << 16)   
#define	mskDMA_SRCRS_CT16B0_MR9     (mskDMA_SRCRS_CT16B0_MR9 << 16)
#define	mskDMA_SRCRS_CT16B0_MR0     (mskDMA_SRCRS_CT16B0_MR0 << 16)
#define	mskDMA_SRCRS_CT16B0_MR1     (mskDMA_SRCRS_CT16B0_MR1 << 16)
#define	mskDMA_SRCRS_CT16B0_MR2     (mskDMA_SRCRS_CT16B0_MR2 << 16)
#define	mskDMA_SRCRS_CT16B0_MR3     (mskDMA_SRCRS_CT16B0_MR3 << 16)
#define	mskDMA_SRCRS_CT16B1_CAP0    (mskDMA_SRCRS_CT16B1_CAP0 << 16)
#define	mskDMA_SRCRS_CT16B1_MR9     (mskDMA_SRCRS_CT16B1_MR9 << 16)
#define	mskDMA_SRCRS_CT16B1_MR0     (mskDMA_SRCRS_CT16B1_MR0 << 16)
#define	mskDMA_SRCRS_CT16B1_MR1     (mskDMA_SRCRS_CT16B1_MR1 << 16)
#define	mskDMA_SRCRS_CT16B1_MR2     (mskDMA_SRCRS_CT16B1_MR2 << 16)
#define	mskDMA_SRCRS_CT16B1_MR3     (mskDMA_SRCRS_CT16B1_MR3 << 16)
#define	mskDMA_SRCRS_CT16B5_CAP0    (mskDMA_SRCRS_CT16B5_CAP0 << 16)
#define	mskDMA_SRCRS_CT16B5_MR9     (mskDMA_SRCRS_CT16B5_MR9 << 16)
#define	mskDMA_SRCRS_CT16B5_MR0     (mskDMA_SRCRS_CT16B5_MR0 << 16)
#define	mskDMA_SRCRS_CT16B5_MR1     (mskDMA_SRCRS_CT16B5_MR1 << 16)
#define	mskDMA_SRCRS_CT16B5_MR2     (mskDMA_SRCRS_CT16B5_MR2 << 16)
#define	mskDMA_SRCRS_CT16B5_MR3     (mskDMA_SRCRS_CT16B5_MR3 << 16)
	
																											// [29:24] Destination DMA request select
#define	DMA_DSTRS_NONE			      	0x00							// NONE for Memory mode
#define	DMA_DSTRS_SPI0_TX        		0x02							// SPI0 TX
#define	DMA_DSTRS_UART0_TX       		0x06							// UART0 TX
#define	DMA_DSTRS_UART1_TX       		0x08							// UART1 TX
#define	DMA_DSTRS_I2C            		0x0E							// I2C
#define	DMA_DSTRS_CT16B0_MR9     		0x11							// CT16B0 MR9
#define	DMA_DSTRS_CT16B0_MR0     		0x12							// CT16B0 MR0
#define	DMA_DSTRS_CT16B0_MR1     		0x13							// CT16B0 MR1
#define	DMA_DSTRS_CT16B0_MR2     		0x14							// CT16B0 MR2
#define	DMA_DSTRS_CT16B0_MR3     		0x15							// CT16B0 MR3
#define	DMA_DSTRS_CT16B1_MR9     		0x17							// CT16B1 MR9
#define	DMA_DSTRS_CT16B1_MR0     		0x18							// CT16B1 MR0
#define	DMA_DSTRS_CT16B1_MR1     		0x19							// CT16B1 MR1
#define	DMA_DSTRS_CT16B1_MR2     		0x1A							// CT16B1 MR2
#define	DMA_DSTRS_CT16B1_MR3     		0x1B							// CT16B1 MR3
#define	DMA_DSTRS_CT16B5_MR9     		0x2B							// CT16B5 MR9
#define	DMA_DSTRS_CT16B5_MR0     		0x2C							// CT16B5 MR0
#define	DMA_DSTRS_CT16B5_MR1     		0x2D							// CT16B5 MR1
#define	DMA_DSTRS_CT16B5_MR2     		0x2E							// CT16B5 MR2
#define	DMA_DSTRS_CT16B5_MR3     		0x2F							// CT16B5 MR3
#define	mskDMA_DSTRS_NONE			      (DMA_DSTRS_NONE	<< 24)
#define	mskDMA_DSTRS_SPI0_TX        (DMA_DSTRS_SPI0_TX << 24)
#define	mskDMA_DSTRS_UART0_TX       (DMA_DSTRS_UART0_TX << 24)
#define	mskDMA_DSTRS_UART1_TX       (DMA_DSTRS_UART1_TX << 24)
#define	mskDMA_DSTRS_I2C            (DMA_DSTRS_I2C << 24)
#define	mskDMA_DSTRS_CT16B0_MR9     (DMA_DSTRS_CT16B0_MR9 << 24)
#define	mskDMA_DSTRS_CT16B0_MR0     (DMA_DSTRS_CT16B0_MR0 << 24)
#define	mskDMA_DSTRS_CT16B0_MR1     (DMA_DSTRS_CT16B0_MR1 << 24)
#define	mskDMA_DSTRS_CT16B0_MR2     (DMA_DSTRS_CT16B0_MR2 << 24)
#define	mskDMA_DSTRS_CT16B0_MR3     (DMA_DSTRS_CT16B0_MR3 << 24)
#define	mskDMA_DSTRS_CT16B1_MR9     (DMA_DSTRS_CT16B1_MR9 << 24)
#define	mskDMA_DSTRS_CT16B1_MR0     (DMA_DSTRS_CT16B1_MR0 << 24)
#define	mskDMA_DSTRS_CT16B1_MR1     (DMA_DSTRS_CT16B1_MR1 << 24)
#define	mskDMA_DSTRS_CT16B1_MR2     (DMA_DSTRS_CT16B1_MR2 << 24)
#define	mskDMA_DSTRS_CT16B1_MR3     (DMA_DSTRS_CT16B1_MR3 << 24)
#define	mskDMA_DSTRS_CT16B5_MR9     (DMA_DSTRS_CT16B5_MR9 << 24)
#define	mskDMA_DSTRS_CT16B5_MR0     (DMA_DSTRS_CT16B5_MR0 << 24)
#define	mskDMA_DSTRS_CT16B5_MR1     (DMA_DSTRS_CT16B5_MR1 << 24)
#define	mskDMA_DSTRS_CT16B5_MR2     (DMA_DSTRS_CT16B5_MR2 << 24)
#define	mskDMA_DSTRS_CT16B5_MR3     (DMA_DSTRS_CT16B5_MR3 << 24)

/*** DMA Initialization Structure definition ***/
typedef struct{
	uint8_t  b_SrcAddrCtrl;
	uint8_t  b_SrcMode;
	uint8_t  b_SrcWidth;
	uint8_t  b_SrcReqSel;
	uint8_t  b_DstAddrCtrl;
	uint8_t  b_DstMode;
	uint8_t  b_DstWidth;
	uint8_t  b_DstReqSel;
	uint8_t  b_Priority;
	uint8_t  b_BurstSize;
	uint8_t  b_IntTCEn;
	uint8_t  b_IntABTEn;
}DMA_InitSt;

/*** DMA Start Structure definition ***/
typedef struct{
	uint32_t  w_SrcAddr;
	uint32_t  w_DstAddr;
	uint32_t  w_TotalSize;
}DMA_StartSt;

/*_____ M A C R O S ________________________________________________________*/
			  
/*_____ D E C L A R A T I O N S ____________________________________________*/
/*** DMA ISR Flag Structure definition ***/
typedef struct{
	union{
		uint8_t All;
		struct{
			uint8_t TC	:1;
			uint8_t ABT	:1;
		}bits;
	}Flag;
}DMA_IntFlagSt;

extern DMA_IntFlagSt stDMA0IntFlag[eDMA_CH_MAX];

/*_____ D E C L A R A T I O N S ____________________________________________*/
void DMA_Init (DMA_InitSt* struct_ptrDMAConfig, uint8_t b_CHn);
void DMA_InterruptEnable(uint8_t b_Enable, uint8_t b_CHn);
void DMA_Start (DMA_StartSt* struct_ptrDMAstart, uint8_t b_CHn);
void DMA_Abort(uint8_t b_CHn);
void DMA_UnInit (void);


#endif	/*__SN32F400_DMA_H*/

