#ifndef __SN32F400_CT16B0_H
#define __SN32F400_CT16B0_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdint.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	CT16B0_IRQ	INTERRUPT_METHOD		//INTERRUPT_METHOD:	Enable CT16B0 timer and interrupt
																				//POLLING_METHOD: 	Enable CT16B0 timer ONLY

/*_____ M A C R O S ________________________________________________________*/
#define __CT16B0_ENABLE										SN_SYS1->AHBCLKEN_b.CT16B0CLKEN = ENABLE		
#define __CT16B0_DISABLE									SN_SYS1->AHBCLKEN_b.CT16B0CLKEN = DISABLE	

/* CT16Bn Clock Source Select register <SYS0_CT_CLKSEL> (0x40060044) */
																					//[0:0] CT16B0 PCLK source
#define	CT16B0_CLKSEL_HCLK 								0
#define	CT16B0_CLKSEL_PLL_VCO							1
#define mskCT16B0_CLKSEL_HCLK							(CT16B0_CLKSEL_HCLK << 0)
#define	mskCT16B0_CLKSEL_PLL_VCO  				(CT16B0_CLKSEL_PLL_VCO << 0)

#define __CT16B0_CLKSEL_HCLK							SN_SYS0->CT_CLKSEL_b.CLKSEL0 = CT16B0_CLKSEL_HCLK
#define __CT16B0_CLKSEL_PLL_VCO						SN_SYS0->CT_CLKSEL_b.CLKSEL0 = CT16B0_CLKSEL_PLL_VCO

/*_____ D E C L A R A T I O N S ____________________________________________*/

void CT16B0_Init(void);
void CT16B0_NvicEnable(void);
void CT16B0_NvicDisable(void);

#endif	/*__SN32F400_CT16B0_H*/
