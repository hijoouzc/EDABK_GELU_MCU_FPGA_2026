#ifndef __SN32F400_CT16B5_H
#define __SN32F400_CT16B5_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdint.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	CT16B5_IRQ	INTERRUPT_METHOD		//INTERRUPT_METHOD:	Enable CT16B5 timer and interrupt
																				//POLLING_METHOD: 	Enable CT16B5 timer ONLY

/*_____ M A C R O S ________________________________________________________*/
#define __CT16B5_ENABLE			SN_SYS1->AHBCLKEN_b.CT16B5CLKEN = ENABLE		
#define __CT16B5_DISABLE		SN_SYS1->AHBCLKEN_b.CT16B5CLKEN = DISABLE

/* CT16Bn Clock Source Select register <SYS0_CT_CLKSEL> (0x40060044) */
																					//[6:5] CT16B5 PCLK source
#define	CT16B5_CLKSEL_HCLK 								0
#define	CT16B5_CLKSEL_PLL_VCO							1
#define	CT16B5_CLKSEL_LXTAL 							2
#define	CT16B5_CLKSEL_ILRC								3
#define mskCT16B5_CLKSEL_HCLK							(CT16B5_CLKSEL_HCLK << 5)
#define	mskCT16B5_CLKSEL_PLL_VCO  				(CT16B5_CLKSEL_PLL_VCO << 5)
#define mskCT16B5_CLKSEL_LXTAL						(CT16B5_CLKSEL_LXTAL << 5)
#define	mskCT16B5_CLKSEL_ILRC  						(CT16B5_CLKSEL_ILRC << 5)

#define __CT16B5_CLKSEL_HCLK							SN_SYS0->CT_CLKSEL_b.CLKSEL5 = CT16B5_CLKSEL_HCLK
#define __CT16B5_CLKSEL_PLL_VCO						SN_SYS0->CT_CLKSEL_b.CLKSEL5 = CT16B5_CLKSEL_PLL_VCO
#define __CT16B5_CLKSEL_LXTAL							SN_SYS0->CT_CLKSEL_b.CLKSEL5 = CT16B5_CLKSEL_LXTAL
#define __CT16B5_CLKSEL_ILRC							SN_SYS0->CT_CLKSEL_b.CLKSEL5 = CT16B5_CLKSEL_ILRC

/*_____ D E C L A R A T I O N S ____________________________________________*/
extern volatile uint32_t iwCT16B5_IrqEvent; //The bitmask usage of iwCT16Bn_IrqEvent is the same with CT16Bn_RIS

void CT16B5_Init(void);
void CT16B5_NvicEnable(void);
void CT16B5_NvicDisable(void);

#endif	/*__SN32F400_CT16B5_H*/
