#ifndef __KEYSCAN_H
#define __KEYSCAN_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdint.h>
/*_____ D E F I N I T I O N S ______________________________________________*/
#define	KEY_PUSH_FLAG	0x8000
#define	KEY_POP_FLAG	0x0000


//key macro
#define	KEY_COL1	0x01
#define	KEY_COL2	0x02
#define	KEY_COL3	0x04
#define	KEY_COL4	0x08

#define	KEY_ROW1	0x10
#define	KEY_ROW2	0x20
#define	KEY_ROW3	0x40
#define	KEY_ROW4	0x80

enum{
	KEY_1		= KEY_ROW1|KEY_COL1,
	KEY_2		= KEY_ROW1|KEY_COL2,
	KEY_3		= KEY_ROW1|KEY_COL3,
	KEY_4		= KEY_ROW1|KEY_COL4,
	KEY_5		= KEY_ROW2|KEY_COL1,
	KEY_6		= KEY_ROW2|KEY_COL2,
	KEY_7		= KEY_ROW2|KEY_COL3,
	KEY_8		= KEY_ROW2|KEY_COL4,
	KEY_9		= KEY_ROW3|KEY_COL1,
	KEY_10	= KEY_ROW3|KEY_COL2,
	KEY_11	= KEY_ROW3|KEY_COL3,
	KEY_12	= KEY_ROW3|KEY_COL4,
	KEY_13	= KEY_ROW4|KEY_COL1,
	KEY_14	= KEY_ROW4|KEY_COL2,
	KEY_15	= KEY_ROW4|KEY_COL3,
	KEY_16	= KEY_ROW4|KEY_COL4,
};
/*_____ M A C R O S ________________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
uint16_t KeyScan(void);
#endif	/*__KEYSCAN_H*/
