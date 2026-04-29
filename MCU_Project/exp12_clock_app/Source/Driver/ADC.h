#ifndef __SN32F400_ADC_H
#define __SN32F400_ADC_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
//Temp sensor VIREF gain select bit
#define TS_GAINSEL_LOW_GAIN			0x0
#define TS_GAINSEL_HIGH_GAIN		0x0

//ADC FIFO reset bit
#define ADC_FIFORST_NO_EFFECT		0x0
#define ADC_FIFORST_RESET				0x1

//ADC Overrun mode select bit
#define ADC_OVRMODE_PRESERVE		0x0
#define ADC_OVRMODE_OVERWRITE		0x1

//ADC Stop control bit
#define ADC_ADSTOP_NO_EFFECT		0x0
#define ADC_ADSTOP_STOP					0x1

//ADC Internal Reference Voltage level
#define	ADC_VHS_INTERNAL_2V						0
#define	ADC_VHS_INTERNAL_3V						1
#define	ADC_VHS_INTERNAL_4P5V					2
#define	ADC_VHS_INTERNAL_1P5V					3
#define	ADC_VHS_INTERNAL_2V_AIN18			4
#define	ADC_VHS_INTERNAL_3V_AIN18			5
#define	ADC_VHS_INTERNAL_4P5V_AIN18		6
#define	ADC_VHS_INTERNAL_1P5V_AIN18		7

//ADC high reference voltage source select bit
#define ADC_AVREFHSEL_INTERNAL	0x0
#define ADC_AVREFHSEL_EXTERNAL	0x1

//ADC Enable bit
#define ADC_ADENB_DIS						0x0
#define ADC_ADENB_EN						0x1

//ADC Clock source divider
#define ADC_ADCKS_DIV1					0x0
#define ADC_ADCKS_DIV2					0x1
#define ADC_ADCKS_DIV4					0x2
#define ADC_ADCKS_DIV8					0x3
#define ADC_ADCKS_DIV16					0x4
#define ADC_ADCKS_DIV32					0x5

//ADC resolution control bit
#define ADC_ADLEN_8BIT					0x0
#define ADC_ADLEN_12BIT					0x1

//ADC start control bit
#define	ADC_ADS_STOP						0x0
#define	ADC_ADS_START						0x1

//ADC global channel select bit
#define ADC_GCHS_DIS						0x0
#define ADC_GCHS_EN							0x1

//ADC Single/Continuous mode select bit
#define ADC_SCMODE_SINGLE_MODE				0x0
#define ADC_SCMODE_CONTINUOUS_MODE		0x1

//ADC Converting channel number
#define ADC_CH_SINGLE_CHANNEL		0x0
#define ADC_CH_MULTIPLE_CHANNEL	0x1

//ADC input channels select bit
#define ADC_CHS_DIS							0x0
#define ADC_CHS_AIN0						(0x1 << 0)			//P2.0
#define ADC_CHS_AIN1						(0x1 << 1)			//P2.1
#define ADC_CHS_AIN2						(0x1 << 2)			//P2.2
#define ADC_CHS_AIN3						(0x1 << 3)			//P2.3
#define ADC_CHS_AIN4						(0x1 << 4)			//P2.4
#define ADC_CHS_AIN5						(0x1 << 5)			//P2.5
#define ADC_CHS_AIN6						(0x1 << 6)			//P2.6
#define ADC_CHS_AIN7						(0x1 << 7)			//P2.7
#define ADC_CHS_AIN8						(0x1 << 8)			//P2.8
#define ADC_CHS_AIN9						(0x1 << 9)			//P2.9
#define ADC_CHS_AIN10						(0x1 << 10)			//P2.10
#define ADC_CHS_AIN11						(0x1 << 11)			//P1.0
#define ADC_CHS_AIN12						(0x1 << 12)			//P1.1
#define ADC_CHS_AIN13						(0x1 << 13)			//P1.2
#define ADC_CHS_AIN14						(0x1 << 14)			//P0.5
#define ADC_CHS_AIN15						(0x1 << 15)			//P3.0
#define ADC_CHS_AIN16						(0x1 << 16)			//VDD
#define ADC_CHS_AIN17						(0x1 << 17)			//VSS
#define ADC_CHS_AIN18						(0x1 << 18)			//Int/Ext VREF
#define ADC_CHS_AIN19						(0x1 << 19)			//OP0O
#define ADC_CHS_AIN20						(0x1 << 20)			//OP1O
#define ADC_CHS_AIN21						(0x1 << 21)			//OP2O

//ADC Interrupt Enable register(ADC_IE)
#define ADC_IE_AIN_DIS					ADC_CHS_DIS
#define ADC_IE_AIN0							ADC_CHS_AIN0		//P2.0
#define ADC_IE_AIN1							ADC_CHS_AIN1		//P2.1
#define ADC_IE_AIN2							ADC_CHS_AIN2		//P2.2
#define ADC_IE_AIN3							ADC_CHS_AIN3		//P2.3
#define ADC_IE_AIN4							ADC_CHS_AIN4		//P2.4
#define ADC_IE_AIN5							ADC_CHS_AIN5		//P2.5
#define ADC_IE_AIN6							ADC_CHS_AIN6		//P2.6
#define ADC_IE_AIN7							ADC_CHS_AIN7		//P2.7
#define ADC_IE_AIN8							ADC_CHS_AIN8		//P2.8
#define ADC_IE_AIN9							ADC_CHS_AIN9		//P2.9
#define ADC_IE_AIN10						ADC_CHS_AIN10		//P2.10
#define ADC_IE_AIN11						ADC_CHS_AIN11		//P1.0
#define ADC_IE_AIN12						ADC_CHS_AIN12		//P1.1
#define ADC_IE_AIN13						ADC_CHS_AIN13		//P1.2
#define ADC_IE_AIN14						ADC_CHS_AIN14		//P0.5
#define ADC_IE_AIN15						ADC_CHS_AIN15		//P3.0
#define ADC_IE_AIN16						ADC_CHS_AIN16		//VDD
#define ADC_IE_AIN17						ADC_CHS_AIN17		//VSS
#define ADC_IE_AIN18						ADC_CHS_AIN18		//Int/Ext VREF
#define ADC_IE_AIN19						ADC_CHS_AIN19		//OP0O
#define ADC_IE_AIN20						ADC_CHS_AIN20		//OP1O
#define ADC_IE_AIN21						ADC_CHS_AIN21		//OP2O
#define ADC_IE_EOS							(0x1 << 24)			//End of sequence 
#define ADC_IE_AWW							(0x1 << 25)			//ADC window WDT
#define ADC_IE_OVR							(0x1 << 26)			//Overrun raw
#define ADC_IE_EOCAL						(0x1 << 27)			//End of calibration

//ADC Raw Interrupt Status register(ADC_RIS)
#define mskADC_IF_AIN0					ADC_IE_AIN0			//P2.0
#define mskADC_IF_AIN1					ADC_IE_AIN1			//P2.1
#define mskADC_IF_AIN2					ADC_IE_AIN2			//P2.2
#define mskADC_IF_AIN3					ADC_IE_AIN3			//P2.3
#define mskADC_IF_AIN4					ADC_IE_AIN4			//P2.4
#define mskADC_IF_AIN5					ADC_IE_AIN5			//P2.5
#define mskADC_IF_AIN6					ADC_IE_AIN6			//P2.6
#define mskADC_IF_AIN7					ADC_IE_AIN7			//P2.7
#define mskADC_IF_AIN8					ADC_IE_AIN8			//P2.8
#define mskADC_IF_AIN9					ADC_IE_AIN9			//P2.9
#define mskADC_IF_AIN10					ADC_IE_AIN10		//P2.10
#define mskADC_IF_AIN11					ADC_IE_AIN11		//P1.0
#define mskADC_IF_AIN12					ADC_IE_AIN12		//P1.1
#define mskADC_IF_AIN13					ADC_IE_AIN13		//P1.2
#define mskADC_IF_AIN14					ADC_IE_AIN14		//P0.5
#define mskADC_IF_AIN15					ADC_IE_AIN15		//P3.0
#define mskADC_IF_AIN16					ADC_IE_AIN16		//VDD
#define mskADC_IF_AIN17					ADC_IE_AIN17		//VSS
#define mskADC_IF_AIN18					ADC_IE_AIN18		//Int/Ext VREF
#define mskADC_IF_AIN19					ADC_IE_AIN19		//OP0O
#define mskADC_IF_AIN20					ADC_IE_AIN20		//OP1O
#define mskADC_IF_AIN21					ADC_IE_AIN21		//OP2O
#define mskADC_IF_EOS						ADC_IE_EOS			//End of sequence 
#define mskADC_IF_AWW						ADC_IE_AWW			//ADC window WDT
#define mskADC_IF_OVR						ADC_IE_OVR			//Overrun raw
#define mskADC_IF_EOCAL					ADC_IE_EOCAL		//End of calibration

//ADC Window select bit
#define ADC_WINDOW_MODE1				0x0						//ADB > AWDHT
#define ADC_WINDOW_MODE2				0x1						//AWDLT < ADB < AWDHT
#define ADC_WINDOW_MODE3				0x2						//ADB  < AWDLT

//ADC Window watchdog enable bit
#define ADC_AWWENB_DIS					0x0
#define ADC_AWWENB_EN						0x1

//ADC Calibration start bit
#define ADC_ACS_STOP						0x0
#define ADC_ACS_START						0x1

//ADC Calibration value enable bit
#define ADC_CALIVALENB_WITHOUT	0x0
#define ADC_CALIVALENB_WITH			0x1

//ADC function test time out
#define ADC_Convert_Timeout			3000

//ADC function mode
#define ADC_FUNCTION_MODE1			0x0		//Single channel + Single mode example
#define ADC_FUNCTION_MODE2			0x1		//Single channel + Continuous mode example
#define ADC_FUNCTION_MODE3			0x2		//Multiple channel + Single mode example
#define ADC_FUNCTION_MODE4			0x3		//Multiple channel + Continuous mode example
#define ADC_FUNCTION_MODE5			0x4		//Window watchdog (run in Single channel + Single mode)

//ADC DMA mode ADC FIFO Threshold level
#define ADC_DMA_FIFO_TH_0				0
#define ADC_DMA_FIFO_TH_1				1
#define ADC_DMA_FIFO_TH_2				2
#define ADC_DMA_FIFO_TH_3				3
#define ADC_DMA_FIFO_TH_4				4
#define ADC_DMA_FIFO_TH_5				5
#define ADC_DMA_FIFO_TH_6				6
#define ADC_DMA_FIFO_TH_7				7
#define ADC_DMA_FIFO_TH_8				8
#define ADC_DMA_FIFO_TH_9				9
#define ADC_DMA_FIFO_TH_10			10	
#define ADC_DMA_FIFO_TH_11			11	
#define ADC_DMA_FIFO_TH_12			12
#define ADC_DMA_FIFO_TH_13			13
#define ADC_DMA_FIFO_TH_14			14	
#define ADC_DMA_FIFO_TH_15			15	

//ADC DMA mode enable bit
#define ADC_DMA_DIS							0x0
#define ADC_DMA_EN							0x1

enum
{
	//HCLK Clock divider
	HCLK_DIV1 = 0, HCLK_DIV2, HCLK_DIV4, HCLK_DIV8, HCLK_DIV16,
	//ADC Clock divider
	ADC_DIV1 = 0, ADC_DIV2, ADC_DIV4, ADC_DIV8, ADC_DIV16, ADC_DIV32,
	//ADC Resolution
	ADC_8BIT = 0, ADC_12BIT,
	//ADC Converting channel number
	Single_Channel = 0, Multiple_Channel,
	//ADC Converting mode
	Single_Mode = 0, Continuous_Mode,
	//AWW select mode
	AWWMode1 = 0, AWWMode2, AWWMode3,
	//Is first channel
	NotFirst = 0, First,
	//TSEN enable or disable
	TSDISABLE = 0, TSENABLE,
	//End of calibration interrupt enable or disable
	EOCALIE_DIS = 0, EOCALIE_EN,
	//Overrun raw interrupt enable or disable
	OVRIE_DIS = 0, OVRIE_EN,
	//ADC window WDT interrupt enable or disable
	AWWIE_DIS = 0, AWWIE_EN,
	//End of sequence interrupt enable or disable
	EOSIE_DIS = 0, EOSIE_EN,
};

#pragma anon_unions
typedef struct
{
	uint32_t EOS;
	union
	{
		uint32_t AWW;
		struct
		{
			uint32_t CH0	: 1;
			uint32_t CH1	: 1;
			uint32_t CH2	: 1;
			uint32_t CH3	: 1;
			uint32_t CH4	: 1;
			uint32_t CH5	: 1;
			uint32_t CH6	: 1;
			uint32_t CH7	: 1;
			uint32_t CH8	: 1;
			uint32_t CH9	: 1;
			uint32_t CH10 : 1;
			uint32_t CH11 : 1;
			uint32_t CH12 : 1;
			uint32_t CH13 : 1;
			uint32_t CH14 : 1;
			uint32_t CH15 : 1;
			uint32_t CH16 : 1;
			uint32_t CH17 : 1;
			uint32_t CH18 : 1;
			uint32_t CH19 : 1;
			uint32_t CH20 : 1;
			uint32_t CH21 : 1;
			uint32_t			: 10;
		}AWW_b;
	};
	uint32_t OVR;
	uint32_t EOCAL;
	union
	{
		uint32_t EOC;
		struct
		{
			uint32_t CH0	: 1;
			uint32_t CH1	: 1;
			uint32_t CH2	: 1;
			uint32_t CH3	: 1;
			uint32_t CH4	: 1;
			uint32_t CH5	: 1;
			uint32_t CH6	: 1;
			uint32_t CH7	: 1;
			uint32_t CH8	: 1;
			uint32_t CH9	: 1;
			uint32_t CH10 : 1;
			uint32_t CH11 : 1;
			uint32_t CH12 : 1;
			uint32_t CH13 : 1;
			uint32_t CH14 : 1;
			uint32_t CH15 : 1;
			uint32_t CH16 : 1;
			uint32_t CH17 : 1;
			uint32_t CH18 : 1;
			uint32_t CH19 : 1;
			uint32_t CH20 : 1;
			uint32_t CH21 : 1;
			uint32_t			: 10;
		}EOC_b;
	};
} SADC_Interrupt_Flag;

typedef struct
{
	union
	{
		uint32_t ADB;
		struct
		{
			uint16_t DATA	:	12;
			volatile const uint32_t	:	4;
			uint8_t ISFIRSTCH	:	1;
		}b;
	};
} SADC_DATA;

/*_____ M A C R O S ________________________________________________________*/
#define __ADC_INTERRUPT_FLAG_CLEAR	sInterruptFlag.AWW = 0x0;		\
																		sInterruptFlag.EOC = 0x0;		\
																		sInterruptFlag.EOCAL = 0x0;	\
																		sInterruptFlag.EOS = 0x0;		\
																		sInterruptFlag.OVR = 0x0;

//ADC HCLK Enable/Disable
#define	__ADC_ENABLE_HCLK						SN_SYS1->AHBCLKEN_b.ADCCLKEN = ENABLE;
#define	__ADC_DISABLE_HCLK					SN_SYS1->AHBCLKEN_b.ADCCLKEN = DISABLE;

/*_____ D E C L A R A T I O N S ____________________________________________*/
extern uint16_t hwADC_Value[22];
extern SADC_DATA sADCData;
extern SADC_Interrupt_Flag sInterruptFlag;

void ADC_FuncInit(uint8_t bADCClkDiv, uint8_t bADCLen, uint8_t bCHMode, uint8_t bSCMode);
void ADC_AWWInit(uint16_t hwADCAWWCh, uint8_t bAWWMode, uint16_t hwADCLT, uint16_t hwADCHT);
void ADC_InterruptInit(uint8_t bEOCALen, uint8_t bOVRen, uint8_t bAWWen, uint8_t bEOSen, uint16_t bADCCh);
uint8_t ADC_Convert(uint16_t hwADCCh, uint8_t bADCCtrlMode);
uint16_t ADC_Read(void);
void ADC_NvicEnable(void);
void ADC_NvicDisable(void);
void ADC_DMA_Start(uint16_t hwADCCh, uint8_t bADCDMAFifoTh, uint32_t wADCDMASize);

#endif	/*__SN32F400_ADC_H*/
