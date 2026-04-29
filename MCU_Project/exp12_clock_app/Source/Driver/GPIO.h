#ifndef __SN32F400_GPIO_H
#define __SN32F400_GPIO_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
/*							
Base Address: 0x4004 4000 (GPIO 0)
							0x4004 6000 (GPIO 1)
							0x4004 8000 (GPIO 2)
							0x4004 A000 (GPIO 3)
*/

#define	SET_LED0_ON		SN_GPIO3->BCLR = 1 << 8
#define	SET_LED0_OFF	SN_GPIO3->BSET = 1 << 8

#define	SET_LED1_ON		SN_GPIO3->BCLR = 1 << 9
#define	SET_LED1_OFF	SN_GPIO3->BSET = 1 << 9

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
void GPIO_Init (void);

#endif	/*__SN32F400_GPIO_H*/
