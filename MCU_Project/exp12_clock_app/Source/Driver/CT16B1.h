#ifndef __SN32F400_CT16B1_H
#define __SN32F400_CT16B1_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdint.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	CT16B1_IRQ	INTERRUPT_METHOD		//INTERRUPT_METHOD:	Enable CT16B1 timer and interrupt
																				//POLLING_METHOD: 	Enable CT16B1 timer ONLY

/*_____ M A C R O S ________________________________________________________*/
#define __CT16B1_ENABLE						SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = ENABLE		
#define __CT16B1_DISABLE					SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = DISABLE	

/* CT16Bn Clock Source Select register <SYS0_CT_CLKSEL> (0x40060044) */
																					//[1:1] CT16B1 PCLK source
#define	CT16B1_CLKSEL_HCLK 								0
#define	CT16B1_CLKSEL_PLL_VCO							1
#define mskCT16B1_CLKSEL_HCLK							(CT16B1_CLKSEL_HCLK << 1)
#define	mskCT16B1_CLKSEL_PLL_VCO  				(CT16B1_CLKSEL_PLL_VCO << 1)

#define __CT16B1_CLKSEL_HCLK							SN_SYS0->CT_CLKSEL_b.CLKSEL1 = CT16B1_CLKSEL_HCLK
#define __CT16B1_CLKSEL_PLL_VCO						SN_SYS0->CT_CLKSEL_b.CLKSEL1 = CT16B1_CLKSEL_PLL_VCO

/*_____ D E C L A R A T I O N S ____________________________________________*/
extern uint8_t timer_1s_flag;
extern uint8_t timer_1ms_flag;

void CT16B1_Init(void);
void CT16B1_NvicEnable(void);
void CT16B1_NvicDisable(void);

#endif	/*__SN32F400_CT16B1_H*/
