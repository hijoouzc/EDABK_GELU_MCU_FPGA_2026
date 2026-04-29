#ifndef __BUZZER_H
#define __BUZZER_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>

/*_____ D E F I N I T I O N S ______________________________________________*/


/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
void set_buzzer_pitch(uint8_t pitch);
void buzzer_on(void);   // Bat buzzer 1kHz (khong thay doi timer period MR9)
void buzzer_off(void);  // Tat buzzer
#endif	/*__BUZZER_H*/
