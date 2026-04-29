#ifndef __SN32F400_WDT_H
#define __SN32F400_WDT_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
	Base Address: 0x4001 0000 (WDT)
*/

/* Watchdog Configuration register <WDT_CFG> (0x00) */
																	//[0:0]Watchdog enable bit
#define WDT_WDTEN_DIS				0			//Disable
#define WDT_WDTEN_EN				1			//Enable																								
#define mskWDT_WDTEN_DIS		(WDT_WDTEN_DIS << 0)
#define mskWDT_WDTEN_EN			(WDT_WDTEN_EN << 0)

																	//[1:1]Watchdog interrupt enable bit
#define WDT_WDTIE_DIS				0			//Watchdog time-out will cause a chip reset.
#define WDT_WDTIE_EN				1			//Watchdog time-out will cause an interrupt. 
#define mskWDT_WDTIE_DIS		(WDT_WDTIE_DIS << 1)
#define mskWDT_WDTIE_EN			(WDT_WDTIE_EN << 1)

																	//[2:2]Watchdog interrupt flag bit
#define mskWDT_WDTINT				(1 << 2)

																	//Watchdog register key	
#define mskWDT_WDKEY		 		(0x5AFA << 16)

																	//Watchdog Feed value
#define mskWDT_FV		 				0x55AA

#define RESET								0			//WDT as Reset mode
#define INTERRUPT						1			//WDT as Interrupt mode
#define	WDT_MODE						RESET
																										
/*_____ M A C R O S ________________________________________________________*/
//Watchdog Feed Value
#define	__WDT_FEED_VALUE				(SN_WDT->FEED = (mskWDT_WDKEY | mskWDT_FV))	

//WDT Enable/Disable
#define	__WDT_ENABLE						(SN_WDT->CFG |= (mskWDT_WDKEY | mskWDT_WDTEN_EN))
#define	__WDT_DISABLE						(SN_WDT->CFG = (mskWDT_WDKEY | (SN_WDT->CFG & ~mskWDT_WDTEN_EN))) 
																 
//WDT INT status register clear
#define __WDT_CLRINSTS		      (SN_WDT->CFG = (mskWDT_WDKEY | (SN_WDT->CFG & ~mskWDT_WDTINT)))   

/*_____ D E C L A R A T I O N S ____________________________________________*/
void WDT_Init(void);
void WDT_ReloadValue(uint32_t);
void WDT_SelectClockSource(uint32_t);
void WDT_NvicEnable(void);
void WDT_NvicDisable(void);

#endif	/*__SN32F400_WDT_H*/
