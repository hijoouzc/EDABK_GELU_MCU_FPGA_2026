#ifndef __SN32F400_OPA_H
#define __SN32F400_OPA_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
	Base Address : 0x4002 A000 (OPA)
*/

/* OPA Control register <OPA_CTRL> (0x00) */
																	//[0:0] OP-Amp 0 enable bit.
#define OP0EN_DIS							0		//Disable. OP0O/OP0P/OP0N pins are GPIO mode
#define OP0EN_EN							1		//Enable. OP0O is OP-Amp 0 output pin.
#define	mskOP0EN_DIS					(OP0EN_DIS << 0)
#define	mskOP0EN_EN						(OP0EN_EN << 0)
#define OP0_SEL_OP0O					0		
#define OP0_SEL_GPIO					1		
#define	mskOP0_SEL_OP0O				(OP0_SEL_OP0O << 1)
#define	mskOP0_SEL_GPIO				(OP0_SEL_GPIO << 1)

																	//[8:8] OP-Amp 1 enable bit.
#define OP1EN_DIS							0		//Disable. OP1O/OP1P/OP1N pins are GPIO mode
#define OP1EN_EN							1		//Enable. OP1O is OP-Amp 1 output pin.
#define	mskOP1EN_DIS					(OP1EN_DIS << 8)
#define	mskOP1EN_EN						(OP1EN_EN << 8)
#define OP1_SEL_OP1O					0		
#define OP1_SEL_GPIO					1		
#define	mskOP1_SEL_OP1O				(OP1_SEL_OP1O << 9)
#define	mskOP1_SEL_GPIO				(OP1_SEL_GPIO << 9)

																	//[16:16] OP-Amp 2 enable bit.
#define OP2EN_DIS							0		//Disable. OP2O/OP2P/OP2N pins are GPIO mode
#define OP2EN_EN							1		//Enable. OP2O is OP-Amp 2 output pin.
#define	mskOP2EN_DIS					(OP2EN_DIS << 16)
#define	mskOP2EN_EN						(OP2EN_EN << 16)
#define OP2_SEL_OP2O					0		
#define OP2_SEL_GPIO					1		
#define	mskOP2_SEL_OP2O				(OP2_SEL_OP2O << 17)
#define	mskOP2_SEL_GPIO				(OP2_SEL_GPIO << 17)


/* OPA PGA Control register <OPA_PGACTRL> (0x04) */
//OPA0																	
#define OP0PS_DIS							0		
#define OP0PS_EN							1		
#define	mskOP0PS_DIS					(OP0PS_DIS << 0)
#define	mskOP0PS_EN						(OP0PS_EN << 0)
#define OP0NS_DIS							0		
#define OP0NS_EN							1		
#define	mskOP0NS_DIS					(OP0NS_DIS << 1)
#define	mskOP0NS_EN						(OP0NS_EN << 1)	
#define	mskOP0PRS_10K					(0 << 2)
#define	mskOP0PRS_SHORT				(1 << 2)
#define	mskOP0NRS_10K					(0 << 3)
#define	mskOP0NRS_SHORT				(1 << 3)
#define	mskOP0GS_GAIN(x)			((x & 0x1F) << 4)

//OPA1																	
#define OP1PS_DIS							0		
#define OP1PS_EN							1		
#define	mskOP1PS_DIS					(OP1PS_DIS << 12)
#define	mskOP1PS_EN						(OP1PS_EN << 12)
#define OP1NS_DIS							0		
#define OP1NS_EN							1		
#define	mskOP1NS_DIS					(OP1NS_DIS << 13)
#define	mskOP1NS_EN						(OP1NS_EN << 13)	
#define	mskOP1PRS_10K					(0 << 14)
#define	mskOP1PRS_SHORT				(1 << 14)
#define	mskOP1NRS_10K					(0 << 15)
#define	mskOP1NRS_SHORT				(1 << 15)
#define	mskOP1GS_GAIN(x)			((x & 0x1F) << 16)

//OPA2																	
#define OP2PS_DIS							0		
#define OP2PS_EN							1		
#define	mskOP2PS_DIS					(OP2PS_DIS << 0)
#define	mskOP2PS_EN						(OP2PS_EN << 0)
#define OP2NS_DIS							0		
#define OP2NS_EN							1		
#define	mskOP2NS_DIS					(OP2NS_DIS << 1)
#define	mskOP2NS_EN						(OP2NS_EN << 1)	
#define	mskOP2PRS_10K					(0 << 2)
#define	mskOP2PRS_SHORT				(1 << 2)
#define	mskOP2NRS_10K					(0 << 3)
#define	mskOP2NRS_SHORT				(1 << 3)
#define	mskOP2GS_GAIN(x)			((x & 0x1F) << 4)

/*_____ M A C R O S ________________________________________________________*/
#define __OPA_ENABLE_PCLK			SN_SYS1->AHBCLKEN_b.OPACLKEN = ENABLE		
#define __OPA_DISABLE_PCLK		SN_SYS1->AHBCLKEN_b.OPACLKEN = DISABLE	

extern uint8_t OPA0_ENABLE;		
extern uint8_t OPA1_ENABLE;		
extern uint8_t OPA2_ENABLE;
extern uint8_t ALL_OPA_ENABLE;

/*_____ D E C L A R A T I O N S ____________________________________________*/
void OPA_Enable(void);
void OPA_Disable(void);
void OPA_PGA_Test(uint8_t number, uint8_t gain);

#endif	/*__SN32F400_OPA_H*/
