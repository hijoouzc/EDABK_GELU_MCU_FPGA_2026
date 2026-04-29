#ifndef __SN32F400_CMP_H
#define __SN32F400_CMP_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
//CM0PS, CM1PS, CM2PS, CM3PS
#define	CMP_VPREF_VIREFn					0
#define	CMP_VPREF_CMnP0						1
#define	CMP_VPREF_CMnP1						2
#define	CMP_VPREF_CMnP2						3
#define	CMP_VPREF_OP0O    				4
#define	CMP_VPREF_OP1O						5
#define	CMP_VPREF_OP2O						6

#define	mskCMP_CM0PS_VIREF0				(CMP_VPREF_VIREFn << 1)
#define	mskCMP_CM0PS_CM0P0				(CMP_VPREF_CMnP0 << 1)
#define	mskCMP_CM0PS_CM0P1				(CMP_VPREF_CMnP1 << 1)
#define	mskCMP_CM0PS_CM0P2				(CMP_VPREF_CMnP2 << 1)
#define	mskCMP_CM0PS_OP0O				  (CMP_VPREF_OP0O << 1)
#define	mskCMP_CM0PS_OP1O				  (CMP_VPREF_OP1O << 1)
#define	mskCMP_CM0PS_OP2O 				(CMP_VPREF_OP2O << 1)

#define	mskCMP_CM1PS_VIREF0				(CMP_VPREF_VIREFn << 17)
#define	mskCMP_CM1PS_CM0P0				(CMP_VPREF_CMnP0 << 17)
#define	mskCMP_CM1PS_CM0P1				(CMP_VPREF_CMnP1 << 17)
#define	mskCMP_CM1PS_CM0P2				(CMP_VPREF_CMnP2 << 17)
#define	mskCMP_CM1PS_OP0O				  (CMP_VPREF_OP0O << 17)
#define	mskCMP_CM1PS_OP1O				  (CMP_VPREF_OP1O << 17)
#define	mskCMP_CM1PS_OP2O 				(CMP_VPREF_OP2O << 17)

#define	mskCMP_CM2PS_VIREF0				(CMP_VPREF_VIREFn << 1)
#define	mskCMP_CM2PS_CM0P0				(CMP_VPREF_CMnP0 << 1)
#define	mskCMP_CM2PS_CM0P1				(CMP_VPREF_CMnP1 << 1)
#define	mskCMP_CM2PS_CM0P2				(CMP_VPREF_CMnP2 << 1)
#define	mskCMP_CM2PS_OP0O				  (CMP_VPREF_OP0O << 1)
#define	mskCMP_CM2PS_OP1O				  (CMP_VPREF_OP1O << 1)
#define	mskCMP_CM2PS_OP2O 				(CMP_VPREF_OP2O << 1)

#define	mskCMP_CM3PS_VIREF0				(CMP_VPREF_VIREFn << 17)
#define	mskCMP_CM3PS_CM0P0				(CMP_VPREF_CMnP0 << 17)
#define	mskCMP_CM3PS_CM0P1				(CMP_VPREF_CMnP1 << 17)
#define	mskCMP_CM3PS_CM0P2				(CMP_VPREF_CMnP2 << 17)
#define	mskCMP_CM3PS_OP0O				  (CMP_VPREF_OP0O << 17)
#define	mskCMP_CM3PS_OP1O				  (CMP_VPREF_OP1O << 17)
#define	mskCMP_CM3PS_OP2O 				(CMP_VPREF_OP2O << 17)

//CM0NS, CM1NS, CM2NS, CM3NS
#define	CMP_VPREF_CMnN0						0
#define	CMP_VPREF_CMnN1						1
#define	CMP_VPREF_CMnN2						2

#define	mskCMP_CM0NS_CM0N0				(CMP_VPREF_CMnN0 << 4)
#define	mskCMP_CM0NS_CM0N1				(CMP_VPREF_CMnN1 << 4)
#define	mskCMP_CM0NS_CM0N2				(CMP_VPREF_CMnN2 << 4)
#define mskCMP_CM0NS_VIREF0				((CMP_VPREF_VIREFn+3) << 4)

#define	mskCMP_CM1NS_CM1N0				(CMP_VPREF_CMnN0 << 20)
#define	mskCMP_CM1NS_CM1N1				(CMP_VPREF_CMnN1 << 20)
#define	mskCMP_CM1NS_CM1N2				(CMP_VPREF_CMnN2 << 20)
#define mskCMP_CM1NS_VIREF1				((CMP_VPREF_VIREFn+3) << 20)

//CM0OEN, CM1OEN, CM2OEN, CM3OEN
#define	CMP_CMnOn_DISABLE					0
#define	CMP_CMnOn_ENABLE					1

#define	mskCMP_CM0O_DISABLE				(CMP_CMnOn_DISABLE << 11)
#define	mskCMP_CM0O_ENABLE				(CMP_CMnOn_ENABLE << 11)

#define	mskCMP_CM1O_DISABLE				(CMP_CMnOn_DISABLE << 27)
#define	mskCMP_CM1O_ENABLE				(CMP_CMnOn_ENABLE << 27)

#define	mskCMP_CM2O_DISABLE				(CMP_CMnOn_DISABLE << 11)
#define	mskCMP_CM2O_ENABLE				(CMP_CMnOn_ENABLE << 11)

#define	mskCMP_CM3O_DISABLE				(CMP_CMnOn_DISABLE << 27)
#define	mskCMP_CM3O_ENABLE				(CMP_CMnOn_ENABLE << 27)

//CM0G, CM1G, CM2G, CM3G
#define	CMP_CMnG_FALLING					0
#define	CMP_CMnG_RISING						1

#define	mskCMP_CM0G_FALLING				(CMP_CMnG_FALLING << 13)
#define	mskCMP_CM0G_RISING				(CMP_CMnG_RISING << 13)

#define	mskCMP_CM1G_FALLING				(CMP_CMnG_FALLING << 29)
#define	mskCMP_CM1G_RISING				(CMP_CMnG_RISING << 29)

#define	mskCMP_CM2G_FALLING				(CMP_CMnG_FALLING << 13)
#define	mskCMP_CM2G_RISING				(CMP_CMnG_RISING << 13)

#define	mskCMP_CM3G_FALLING				(CMP_CMnG_FALLING << 29)
#define	mskCMP_CM3G_RISING				(CMP_CMnG_RISING << 29)

//CMPIREF
#define	mskCMP_CMPIREFEN_DISABLE	(DISBALE << 0)
#define	mskCMP_CMPIREFEN_ENABLE		(ENABLE << 0)
#define	mskCMP_CMPIREF1EN_DISABLE	(DISBALE << 16)
#define	mskCMP_CMPIREF1EN_ENABLE	(ENABLE << 16)
#define	mskCMP_DATA(value)				(value << 4)
#define	mskCMP_DATA1(value)				(value << 20)

//CM0IE, CM1IE, CM2IE, CM3IE
#define	mskCMP_CM0IE_DISABLE			(DISABLE << 0)
#define	mskCMP_CM0IE_ENABLE				(ENABLE << 0)
#define	mskCMP_CM1IE_DISABLE			(DISABLE << 1)
#define	mskCMP_CM1IE_ENABLE				(ENABLE << 1) 
#define	mskCMP_CM2IE_DISABLE			(DISABLE << 2)
#define	mskCMP_CM2IE_ENABLE				(ENABLE << 2) 
#define	mskCMP_CM3IE_DISABLE			(DISABLE << 3)
#define	mskCMP_CM3IE_ENABLE				(ENABLE << 3) 

//CM0IC, CM1IC, CM2IC, CM3IC
#define	mskCMP_CM0IC_ENABLE				(ENABLE << 0)
#define	mskCMP_CM1IC_ENABLE				(ENABLE << 1)
#define	mskCMP_CM2IC_ENABLE				(ENABLE << 2)
#define	mskCMP_CM3IC_ENABLE				(ENABLE << 3)

/*_____ M A C R O S ________________________________________________________*/

//CMP HCLK Enable/Disable
#define	__CMP_ENABLE_CMPHCLK			SN_SYS1->AHBCLKEN_b.CMPCLKEN = ENABLE;
#define	__CMP_DISABLE_CMPHCLK			SN_SYS1->AHBCLKEN_b.CMPCLKEN = DISABLE;

//CMP0/1/2/3 Enable/Disable
#define	__CMP0_ENABLE							SN_CMP->CTRL_b.CM0EN = ENABLE;
#define	__CMP0_DISABLE						SN_CMP->CTRL_b.CM0EN = DISABLE;
#define	__CMP1_ENABLE							SN_CMP->CTRL_b.CM1EN = ENABLE;
#define	__CMP1_DISABLE						SN_CMP->CTRL_b.CM1EN = DISABLE;
#define	__CMP2_ENABLE							SN_CMP->CTRL1_b.CM2EN = ENABLE;
#define	__CMP2_DISABLE						SN_CMP->CTRL1_b.CM2EN = DISABLE;
#define	__CMP3_ENABLE							SN_CMP->CTRL1_b.CM3EN = ENABLE;
#define	__CMP3_DISABLE						SN_CMP->CTRL1_b.CM3EN = DISABLE;


/*_____ D E C L A R A T I O N S ____________________________________________*/
void CMP_init(void);
void CMP_VIREF_Enable(uint8_t);

#endif	/*__SN32F400_CMP_H*/
