#ifndef __SN32F400_CT16_H
#define __SN32F400_CT16_H

/*_____ I N C L U D E S ____________________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
Base Address: 0x4000 0000 (CT16B0)
							0x4000 2000 (CT16B1)
							0x4000 A000 (CT16B5)
*/

/* CT16Bn Timer Control register <CT16Bn_TMRCTRL> (0x00) */
																					//[0:0] Counter enable bit
#define	CT16_CEN_DIS 								0			//Enable
#define	CT16_CEN_EN  								1			//Disable
#define mskCT16_CEN_DIS							(CT16_CEN_DIS << 0)
#define	mskCT16_CEN_EN  						(CT16_CEN_EN << 0)

																					//[1:1] Counter reset bit
#define	CT16_CRST 									1			
#define mskCT16_CRST								(CT16_CRST << 1)	

																					//[6:4] Counting mode selection 
#define CT16_CM_EDGE_UP							0			//Edge-aligned Up-counting mode
#define CT16_CM_EDGE_DOWN						1			//Edge-aligned Down-counting mode
#define CT16_CM_CENTER_DOWN					2			//Center-aligned mode 1. Match interrupt is set during down-counting period
#define CT16_CM_CENTER_UP						4			//Center-aligned mode 2. Match interrupt is set during up-counting period
#define CT16_CM_CENTER_BOTH					6			//Center-aligned mode 3. Match interrupt is set during both up and down period.
#define mskCT16_CM_EDGE_UP					(CT16_CM_EDGE_UP << 4)		
#define mskCT16_CM_EDGE_DOWN				(CT16_CM_EDGE_DOWN << 4)
#define mskCT16_CM_CENTER_DOWN			(CT16_CM_CENTER_DOWN << 4)
#define mskCT16_CM_CENTER_UP				(CT16_CM_CENTER_UP << 4)	
#define mskCT16_CM_CENTER_BOTH			(CT16_CM_CENTER_BOTH << 4)

/* CT16Bn Count Control register <CT16Bn_CNTCTRL> (0x10) */
																					//[1:0] Count/Timer Mode selection.
#define	CT16_CTM_TIMER							0			//Timer mode: Every rising PCLK edge.
#define CT16_CTM_CNTER_RISING				1			//Counter mode: TC increments on rising edge of CAP input.
#define CT16_CTM_CNTER_FALLING			2			//Counter mode: TC increments on falling edge of CAP input.
#define CT16_CTM_CNTER_BOTH					3			//Counter mode: TC increments on both edge of CAP input.
#define	mskCT16_CTM_TIMER						(CT16_CTM_TIMER << 0)		
#define mskCT16_CTM_CNTER_RISING		(CT16_CTM_CNTER_RISING << 0)		
#define mskCT16_CTM_CNTER_FALLING		(CT16_CTM_CNTER_FALLING << 0)		
#define mskCT16_CTM_CNTER_BOTH			(CT16_CTM_CNTER_BOTH << 0)		

/* CT16Bn Match Control register <CT16Bn_MCTRL> (0x14) */
#define	CT16_MRnIE_EN								1
#define	CT16_MRnIE_DIS							0
#define	CT16_MRnRST_EN							1
#define	CT16_MRnRST_DIS							0
#define	CT16_MRnSTOP_EN							1
#define	CT16_MRnSTOP_DIS						0

																					//[0:0] Enable MR0 match interrupt
#define mskCT16_MR0IE_EN						(CT16_MRnIE_EN << 0)
#define mskCT16_MR0IE_DIS						(CT16_MRnIE_DIS << 0)

																					//[1:1] Enable reset TC when MR0 matches TC.
#define mskCT16_MR0RST_EN						(CT16_MRnRST_EN << 1)
#define mskCT16_MR0RST_DIS					(CT16_MRnRST_DIS << 1)

																					//[2:2] Enable stop TC and clear CEN when MR0 matches TC.
#define mskCT16_MR0STOP_EN					(CT16_MRnSTOP_EN << 2)
#define mskCT16_MR0STOP_DIS					(CT16_MRnSTOP_DIS << 2)

																					//[3:3] Enable MR1 match interrupt
#define mskCT16_MR1IE_EN						(CT16_MRnIE_EN << 3)
#define mskCT16_MR1IE_DIS						(CT16_MRnIE_DIS << 3)

																					//[4:4] Enable reset TC when MR1 matches TC.
#define mskCT16_MR1RST_EN						(CT16_MRnRST_EN << 4)
#define mskCT16_MR1RST_DIS					(CT16_MRnRST_DIS << 4)

																					//[5:5] Enable stop TC and clear CEN when MR1 matches TC.	
#define mskCT16_MR1STOP_EN					(CT16_MRnSTOP_EN << 5)
#define mskCT16_MR1STOP_DIS					(CT16_MRnSTOP_DIS << 5)

																					//[6:6] Enable MR2 match interrupt
#define mskCT16_MR2IE_EN						(CT16_MRnIE_EN << 6)
#define mskCT16_MR2IE_DIS						(CT16_MRnIE_DIS << 6)

																					//[7:7] Enable reset TC when MR2 matches TC.
#define mskCT16_MR2RST_EN						(CT16_MRnRST_EN << 7)
#define mskCT16_MR2RST_DIS					(CT16_MRnRST_DIS << 7)

																					//[8:8] Enable stop TC and clear CEN when MR2 matches TC.
#define mskCT16_MR2STOP_EN					(CT16_MRnSTOP_EN << 8)
#define mskCT16_MR2STOP_DIS					(CT16_MRnSTOP_DIS << 8)

																					//[9:9] Enable MR3 match interrupt
#define mskCT16_MR3IE_EN						(CT16_MRnIE_EN << 9)
#define mskCT16_MR3IE_DIS						(CT16_MRnIE_DIS << 9)

																					//[10:10] Enable reset TC when MR3 matches TC.		
#define mskCT16_MR3RST_EN						(CT16_MRnRST_EN << 10)
#define mskCT16_MR3RST_DIS					(CT16_MRnRST_DIS << 10)

																					//[11:11] Enable stop TC and clear CEN when MR3 matches TC.
#define mskCT16_MR3STOP_EN					(CT16_MRnSTOP_EN << 11)
#define mskCT16_MR3STOP_DIS					(CT16_MRnSTOP_DIS << 11)

																					//[29:29] Enable MR9 match interrupt
#define mskCT16_MR9IE_EN						(CT16_MRnIE_EN << 29)
#define mskCT16_MR9IE_DIS						(CT16_MRnIE_DIS << 29)

																					//[30:30] Enable reset TC when MR9 matches TC.
#define mskCT16_MR9RST_EN						(CT16_MRnRST_EN << 30)
#define mskCT16_MR9RST_DIS					(CT16_MRnRST_DIS << 30)

																					//[31:31] Enable stop TC and clear CEN when MR9 matches TC.
#define mskCT16_MR9STOP_EN					(CT16_MRnSTOP_EN << 31)
#define mskCT16_MR9STOP_DIS					(CT16_MRnSTOP_DIS << 31)


/* CT16Bn Capture Control register <CT16Bn_CAPCTRL> (0x28) */
																					//[0:0] Enable CAP0 capture on rising edge.
#define	CT16_CAP0RE_EN							1		
#define	CT16_CAP0RE_DIS							0
#define mskCT16_CAP0RE_EN						(CT16_CAP0RE_EN << 0)
#define mskCT16_CAP0RE_DIS					(CT16_CAP0RE_DIS << 0)

																					//[1:1] Enable CAP0 capture on fallng edge.
#define	CT16_CAP0FE_EN							1		
#define	CT16_CAP0FE_DIS							0
#define mskCT16_CAP0FE_EN						(CT16_CAP0FE_EN << 1)
#define mskCT16_CAP0FE_DIS					(CT16_CAP0FE_DIS << 1)

																					//[2:2] Enable CAP0 interrupt.
#define	CT16_CAP0IE_EN							1		
#define	CT16_CAP0IE_DIS							0
#define mskCT16_CAP0IE_EN						(CT16_CAP0IE_EN << 2)
#define mskCT16_CAP0IE_DIS					(CT16_CAP0IE_DIS << 2)

																					//[3:3] Enable CAP0 function.
#define	CT16_CAP0EN_EN							1		
#define	CT16_CAP0EN_DIS							0
#define mskCT16_CAP0EN_EN						(CT16_CAP0EN_EN << 3)
#define mskCT16_CAP0EN_DIS					(CT16_CAP0EN_DIS << 3)

/* CT16Bn External Match register <CT16Bn_EM> (0x30) */
#define	CT16_EM_LOW									0			//Drive output to Low
#define	CT16_EM_HIGH								1			//Drive output to high

																					//[0:0] CT16Bn PWM0 drive state	
#define mskCT16_EM0_LOW							(CT16_EM_LOW << 0)
#define mskCT16_EM0_HIGH						(CT16_EM_HIGH << 0)
																					//[1:1] CT16Bn PWM1 drive state
#define mskCT16_EM1_LOW							(CT16_EM_LOW << 1)
#define mskCT16_EM1_HIGH						(CT16_EM_HIGH << 1)
																					//[2:2] CT16Bn PWM2 drive state
#define mskCT16_EM2_LOW							(CT16_EM_LOW << 2)
#define mskCT16_EM2_HIGH						(CT16_EM_HIGH << 2)
																					//[3:3] CT16Bn PWM3 drive state
#define mskCT16_EM3_LOW							(CT16_EM_LOW << 3)
#define mskCT16_EM3_HIGH						(CT16_EM_HIGH << 3)
																		
#define	CT16_EMC_DO_NOTHING					0			//Do nothing.
#define	CT16_EMC_LOW								1			//CT16Bn PWMn pin is low.
#define	CT16_EMC_HIGH								2			//CT16Bn PWMn pin is high.
#define	CT16_EMC_TOGGLE							3			//Toggle CT16Bn PWMn pin.

																					//[5:4] CT16Bn PWM0 functionality
#define mskCT16_EMC0_DO_NOTHING			(CT16_EMC_LOW << 4)
#define mskCT16_EMC0_LOW						(CT16_EMC_LOW << 4)
#define mskCT16_EMC0_HIGH						(CT16_EMC_HIGH << 4)
#define mskCT16_EMC0_TOGGLE					(CT16_EMC_TOGGLE << 4)

																					//[7:6] CT16Bn PWM1 functionality
#define mskCT16_EMC1_DO_NOTHING			(CT16_EMC_LOW << 6)
#define mskCT16_EMC1_LOW						(CT16_EMC_LOW << 6)
#define mskCT16_EMC1_HIGH						(CT16_EMC_HIGH << 6)
#define mskCT16_EMC1_TOGGLE					(CT16_EMC_TOGGLE << 6)

																					//[9:8] CT16Bn PWM2 functionality
#define mskCT16_EMC2_DO_NOTHING			(CT16_EMC_LOW << 8)
#define mskCT16_EMC2_LOW						(CT16_EMC_LOW << 8)
#define mskCT16_EMC2_HIGH						(CT16_EMC_HIGH << 8)
#define mskCT16_EMC2_TOGGLE					(CT16_EMC_TOGGLE << 8)

																					//[11:10] CT16Bn PWM3 functionality
#define mskCT16_EMC3_DO_NOTHING			(CT16_EMC_LOW << 10)
#define mskCT16_EMC3_LOW						(CT16_EMC_LOW << 10)
#define mskCT16_EMC3_HIGH						(CT16_EMC_HIGH << 10)
#define mskCT16_EMC3_TOGGLE					(CT16_EMC_TOGGLE << 10)


/* CT16Bn PWM Control register <CT16Bn_PWMCTRL> (0x34) */
#define	CT16_PWMnEN_EN							1	// CT16Bn PWMn is enabled for PWM mode.	
#define	CT16_PWMnEN_EMn							0 // CT16Bn PWMn is controlled by EMn.

																			//[0:0] CT16Bn PWM0 enable.
#define mskCT16_PWM0EN_EN						(CT16_PWMnEN_EN << 0)
#define mskCT16_PWM0EN_EM0					(CT16_PWMnEN_EMn << 0)

																			//[1:1] CT16Bn PWM1 enable.
#define mskCT16_PWM1EN_EN						(CT16_PWMnEN_EN << 1)
#define mskCT16_PWM1EN_EM1					(CT16_PWMnEN_EMn << 1)

																			//[2:2] CT16Bn PWM2 enable.
#define mskCT16_PWM2EN_EN						(CT16_PWMnEN_EN << 2)
#define mskCT16_PWM2EN_EM2					(CT16_PWMnEN_EMn << 2)

																			//[3:3] CT16Bn PWM3 enable.
#define mskCT16_PWM3EN_EN						(CT16_PWMnEN_EN << 3)
#define mskCT16_PWM3EN_EM3					(CT16_PWMnEN_EMn << 3)

#define	CT16_PWMnMODE_1							0	// PWMn mode 1.	
#define	CT16_PWMnMODE_2							1 // PWMn mode 2.
#define	CT16_PWMnMODE_FORCE_0				2 // Force 0.
#define	CT16_PWMnMODE_FORCE_1				3 // Force 1.

																			//[5:4] CT16Bn PWM0 output mode.
#define mskCT16_PWM0MODE_1					(CT16_PWMnMODE_1 << 4)
#define mskCT16_PWM0MODE_2					(CT16_PWMnMODE_2 << 4)
#define mskCT16_PWM0MODE_FORCE_0		(CT16_PWMnMODE_FORCE_0 << 4)
#define mskCT16_PWM0MODE_FORCE_1		(CT16_PWMnMODE_FORCE_1 << 4)

																			//[7:6] CT16Bn PWM1 output mode.
#define mskCT16_PWM1MODE_1					(CT16_PWMnMODE_1 << 6)
#define mskCT16_PWM1MODE_2					(CT16_PWMnMODE_2 << 6)
#define mskCT16_PWM1MODE_FORCE_0		(CT16_PWMnMODE_FORCE_0 << 6)
#define mskCT16_PWM1MODE_FORCE_1		(CT16_PWMnMODE_FORCE_1 << 6)

																			//[9:8] CT16Bn PWM2 output mode.
#define mskCT16_PWM2MODE_1					(CT16_PWMnMODE_1 << 8)
#define mskCT16_PWM2MODE_2					(CT16_PWMnMODE_2 << 8)
#define mskCT16_PWM2MODE_FORCE_0		(CT16_PWMnMODE_FORCE_0 << 8)
#define mskCT16_PWM2MODE_FORCE_1		(CT16_PWMnMODE_FORCE_1 << 8)

																			//[11:10] CT16Bn PWM3 output mode.
#define mskCT16_PWM3MODE_1					(CT16_PWMnMODE_1 << 10)
#define mskCT16_PWM3MODE_2					(CT16_PWMnMODE_2 << 10)
#define mskCT16_PWM3MODE_FORCE_0		(CT16_PWMnMODE_FORCE_0 << 10)
#define mskCT16_PWM3MODE_FORCE_1		(CT16_PWMnMODE_FORCE_1 << 10)

#define	CT16_PWMnIOEN_EN						1	// PWMn pin acts as match output.
#define	CT16_PWMnIOEN_DIS						0	// PWMn pin acts as GPIO.	

																			//[20:20] CT16Bn PWM0 IO selection.
#define mskCT16_PWM0IOEN_EN					(CT16_PWMnIOEN_EN << 20)
#define mskCT16_PWM0IOEN_DIS				(CT16_PWMnIOEN_DIS << 20)

																			//[21:21] CT16Bn PWM1 IO selection.
#define mskCT16_PWM1IOEN_EN					(CT16_PWMnIOEN_EN << 21)
#define mskCT16_PWM1IOEN_DIS				(CT16_PWMnIOEN_DIS << 21)

																			//[22:22] CT16Bn PWM2 IO selection.
#define mskCT16_PWM2IOEN_EN					(CT16_PWMnIOEN_EN << 22)
#define mskCT16_PWM2IOEN_DIS				(CT16_PWMnIOEN_DIS << 22)

																			//[23:23] CT16Bn PWM3 IO selection.
#define mskCT16_PWM3IOEN_EN					(CT16_PWMnIOEN_EN << 23)
#define mskCT16_PWM3IOEN_DIS				(CT16_PWMnIOEN_DIS << 23)

#define	CT16_PWMnN_GPIO							0	// PWMnN pin acts as GPIO
#define	CT16_PWMnN_MODE1						1 // PWMnN pin outputs the inverse signal with dead-band of PWMn, but same High signal during dead-band period.
#define	CT16_PWMnN_MODE2						2 // PWMnN pin outputs the inverse signal with dead-band of PWMn, but same Low signal during dead-band period.
#define	CT16_PWMnN_MODE3						3 // PWMnN pin outputs the same signal with dead-band of PWMn.

																			//[25:24] CT16Bn PWM0N IO selection.
#define mskCT16_PWM0N_GPIO					(CT16_PWMnN_GPIO << 24)
#define mskCT16_PWM0N_MODE1					(CT16_PWMnN_MODE1 << 24)
#define mskCT16_PWM0N_MODE2					(CT16_PWMnN_MODE2 << 24)
#define mskCT16_PWM0N_MODE3					(CT16_PWMnN_MODE3 << 24)

																			//[27:26] CT16Bn PWM1N IO selection.
#define mskCT16_PWM1N_GPIO					(CT16_PWMnN_GPIO << 26)
#define mskCT16_PWM1N_MODE1					(CT16_PWMnN_MODE1 << 26)
#define mskCT16_PWM1N_MODE2					(CT16_PWMnN_MODE2 << 26)
#define mskCT16_PWM1N_MODE3					(CT16_PWMnN_MODE3 << 26)

																			//[29:28] CT16Bn PWM2N IO selection.
#define mskCT16_PWM2N_GPIO					(CT16_PWMnN_GPIO << 28)
#define mskCT16_PWM2N_MODE1					(CT16_PWMnN_MODE1 << 28)
#define mskCT16_PWM2N_MODE2					(CT16_PWMnN_MODE2 << 28)
#define mskCT16_PWM2N_MODE3					(CT16_PWMnN_MODE3 << 28)

																			//[31:30] CT16Bn PWM3N IO selection.
#define mskCT16_PWM3N_GPIO					(CT16_PWMnN_GPIO << 30)
#define mskCT16_PWM3N_MODE1					(CT16_PWMnN_MODE1 << 30)
#define mskCT16_PWM3N_MODE2					(CT16_PWMnN_MODE2 << 30)
#define mskCT16_PWM3N_MODE3					(CT16_PWMnN_MODE3 << 30)

/* CT16Bn Timer Raw Interrupt Status register <CT16Bn_RIS> (0x38) */
/* CT16Bn Timer Interrupt Clear register <CT16Bn_IC> (0x3C) */
/* The bitmask usage of iwCT16Bn_IrqEvent is the same with CT16Bn_RIS*/
#define mskCT16_MR0IF								(0x1 << 0) //[0:0] Interrupt flag for match channel 0
#define mskCT16_MR0IC								mskCT16_MR0IF 
#define mskCT16_MR1IF								(0x1 << 1) //[1:1] Interrupt flag for match channel 1
#define mskCT16_MR1IC								mskCT16_MR1IF 
#define mskCT16_MR2IF								(0x1 << 2) //[2:2] Interrupt flag for match channel 2
#define mskCT16_MR2IC								mskCT16_MR2IF 
#define mskCT16_MR3IF								(0x1 << 3) //[3:3] Interrupt flag for match channel 3
#define mskCT16_MR3IC								mskCT16_MR3IF 
#define mskCT16_CAP0IF							(0x1 << 4) //[4:4] Interrupt flag for capture channel 0
#define mskCT16_CAP0IC							mskCT16_CAP0IF 
#define mskCT16_MR9IF								(0x1 << 5) //[5:5] Interrupt flag for match channel 9
#define mskCT16_MR9IC								mskCT16_MR9IF
#define mskCT16_BRKIF								(0x1U << 31) //[31:31] Interrupt flag for Break condition
#define mskCT16_BRKIC								mskCT16_BRKIF

/* CT16Bn PWM Load Mode Control register <CT16Bn_LOADCTRL> (0x74) */
#define	CT16_LOAD_MRn_MODE0					0	//No effect.
#define	CT16_LOAD_MRn_MODE1					1 //Load MR3 value at TC=0 and MR3 value is unchanged at TC=MR9.
#define	CT16_LOAD_MRn_MODE2					2	//MR3 value is unchanged at TC=0 and Load MR3 value at TC=MR9.	
#define	CT16_LOAD_MRn_MODE3					3 //Load MR3 value at TC=0 and TC=MR9.

																			//[1:0] MR0 load mode selection in center-aligned mode.
#define mskCT16_LOAD_MR0_MODE0			(CT16_LOAD_MRn_MODE0 << 0)
#define mskCT16_LOAD_MR0_MODE1			(CT16_LOAD_MRn_MODE1 << 0)
#define mskCT16_LOAD_MR0_MODE2			(CT16_LOAD_MRn_MODE2 << 0)
#define mskCT16_LOAD_MR0_MODE3			(CT16_LOAD_MRn_MODE3 << 0)

																			//[3:2] MR1 load mode selection in center-aligned mode.
#define mskCT16_LOAD_MR1_MODE0			(CT16_LOAD_MRn_MODE0 << 2)
#define mskCT16_LOAD_MR1_MODE1			(CT16_LOAD_MRn_MODE1 << 2)
#define mskCT16_LOAD_MR1_MODE2			(CT16_LOAD_MRn_MODE2 << 2)
#define mskCT16_LOAD_MR1_MODE3			(CT16_LOAD_MRn_MODE3 << 2)

																			//[5:4] MR2 load mode selection in center-aligned mode.
#define mskCT16_LOAD_MR2_MODE0			(CT16_LOAD_MRn_MODE0 << 4)
#define mskCT16_LOAD_MR2_MODE1			(CT16_LOAD_MRn_MODE1 << 4)
#define mskCT16_LOAD_MR2_MODE2			(CT16_LOAD_MRn_MODE2 << 4)
#define mskCT16_LOAD_MR2_MODE3			(CT16_LOAD_MRn_MODE3 << 4)

																			//[7:6] MR3 load mode selection in center-aligned mode.
#define mskCT16_LOAD_MR3_MODE0			(CT16_LOAD_MRn_MODE0 << 6)
#define mskCT16_LOAD_MR3_MODE1			(CT16_LOAD_MRn_MODE1 << 6)
#define mskCT16_LOAD_MR3_MODE2			(CT16_LOAD_MRn_MODE2 << 6)
#define mskCT16_LOAD_MR3_MODE3			(CT16_LOAD_MRn_MODE3 << 6)

/* CT16Bn DMA mode register <CT16Bn_DMA> (0xD0) */
#define	CT16_DMA_DIS								0	//Disable, DMA request cannot issue.
#define	CT16_DMA_EN									1 //Enable, DMA request can issue.

																			//[0:0] MR0 DMA request active enable.
#define mskCT16_MR0_DMA_DIS					(CT16_DMA_DIS << 0)
#define mskCT16_MR0_DMA_EN					(CT16_DMA_EN << 0)

																			//[1:1] MR1 DMA request active enable.
#define mskCT16_MR1_DMA_DIS					(CT16_DMA_DIS << 1)
#define mskCT16_MR1_DMA_EN					(CT16_DMA_EN << 1)

																			//[2:2] MR2 DMA request active enable.
#define mskCT16_MR2_DMA_DIS					(CT16_DMA_DIS << 2)
#define mskCT16_MR2_DMA_EN					(CT16_DMA_EN << 2)

																			//[3:3] MR3 DMA request active enable.
#define mskCT16_MR3_DMA_DIS					(CT16_DMA_DIS << 3)
#define mskCT16_MR3_DMA_EN					(CT16_DMA_EN << 3)

																			//[4:4] CAP0 DMA request active enable.
#define mskCT16_CAP0_DMA_DIS				(CT16_DMA_DIS << 4)
#define mskCT16_CAP0_DMA_EN					(CT16_DMA_EN << 4)

																			//[5:5] MR9 DMA request active enable.
#define mskCT16_MR9_DMA_DIS					(CT16_DMA_DIS << 5)
#define mskCT16_MR9_DMA_EN					(CT16_DMA_EN << 5)

/* CT16Bn Break Function Control register <CT16Bn_BRKCTRL> (0xE0) */
																					//[2:0] The trigger source selection of PWM channels break function.
#define	CT16_BRKSEL_DIS							0			//Disable.
#define CT16_BRKSEL_CMP0O						1			//CMP0 output
#define CT16_BRKSEL_CMP1O						2			//CMP1 output
#define CT16_BRKSEL_CMP2O						3			//CMP2 output
#define CT16_BRKSEL_BRK							4			//Break pin
#define	mskCT16_BRKSEL_DIS					(CT16_BRKSEL_DIS << 0)		
#define	mskCT16_BRKSEL_CMP0O				(CT16_BRKSEL_CMP0O << 0)
#define	mskCT16_BRKSEL_CMP1O				(CT16_BRKSEL_CMP1O << 0)
#define	mskCT16_BRKSEL_CMP2O				(CT16_BRKSEL_CMP2O << 0)
#define	mskCT16_BRKSEL_BRK					(CT16_BRKSEL_BRK << 0)

																					//[3:3] The trigger level of PWM channels break function.
#define	CT16_BRKLEVEL_LOW						0			//Low level. (CMP V- > V+)
#define CT16_BRKLEVEL_HIGH					1			//High level. (CMP V+ > V-)
#define	mskCT16_BRKLEVEL_LOW				(CT16_BRKLEVEL_LOW << 3)		
#define	mskCT16_BRKLEVEL_HIGH				(CT16_BRKLEVEL_HIGH << 3)

																					//[6:4] Break pin (BRK) debounce time.
#define	CT16_BRKDB_1T								0			// Debounce time=(1~3)T*CT16B0_PCLK
#define	CT16_BRKDB_2T								1 		// Debounce time=(2~4)T*CT16B0_PCLK
#define	CT16_BRKDB_4T								2			// Debounce time=(4~6)T*CT16B0_PCLK
#define	CT16_BRKDB_8T								3 		// Debounce time=(8~10)T*CT16B0_PCLK
#define	CT16_BRKDB_16T							4			// Debounce time=(16~18)T*CT16B0_PCLK
#define	CT16_BRKDB_32T							5 		// Debounce time=(32~34)T*CT16B0_PCLK
#define	CT16_BRKDB_64T							6			// Debounce time=(64~66)T*CT16B0_PCLK
#define	CT16_BRKDB_128T							7 		// Debounce time=(128~130)T*CT16B0_PCLK.
#define mskCT16_BRKDB_1T						(CT16_BRKDB_1T << 4)
#define mskCT16_BRKDB_2T						(CT16_BRKDB_2T << 4)
#define mskCT16_BRKDB_4T						(CT16_BRKDB_4T << 4)
#define mskCT16_BRKDB_8T						(CT16_BRKDB_8T << 4)
#define mskCT16_BRKDB_16T						(CT16_BRKDB_16T << 4)
#define mskCT16_BRKDB_32T						(CT16_BRKDB_32T << 4)
#define mskCT16_BRKDB_64T						(CT16_BRKDB_64T << 4)
#define mskCT16_BRKDB_128T					(CT16_BRKDB_128T << 4)

																					//[30:30] Enable generating an interrupt when BRKIF = 1.
#define	CT16_BRKIE_DIS							0	
#define	CT16_BRKIE_EN								1 
#define mskCT16_BRKIE_EN						(CT16_BRKIE_EN << 30)
#define mskCT16_BRKIE_DIS						(CT16_BRKIE_DIS << 30)

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/

#endif	/*__SN32F400_CT16_H*/

