#ifndef __EEPROM_H
#define __EEPROM_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>

/*_____ D E F I N I T I O N S ______________________________________________*/


/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
void eeprom_write(uint8_t addr,uint8_t reg,uint8_t *dat,uint16_t length);
void eeprom_read(uint8_t addr,uint8_t reg,uint8_t *dat,uint16_t length);
uint8_t eeprom_check(uint8_t addr);
#endif	/*__EEPROM_H*/
