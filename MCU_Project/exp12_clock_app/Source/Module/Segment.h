#ifndef __SEGMENT_H
#define __SEGMENT_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>

/*_____ D E F I N I T I O N S ______________________________________________*/


/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
extern uint8_t segment_buff[4];
extern const uint8_t SEGMENT_TABLE[];
void Digital_DisplayDEC(uint16_t dec);
void Digital_DisplayHEX(uint16_t dec);
void Digital_Display_Clock(uint8_t hour, uint8_t minute);

void Digital_Scan(void);
#endif	/*__SN32F400_CMP_H*/
