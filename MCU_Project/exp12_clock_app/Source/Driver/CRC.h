#ifndef __SN32F400_CRC_H
#define __SN32F400_CRC_H

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>
#include <SN32F400_Def.h>

/*_____ D E F I N I T I O N S ______________________________________________*/
/*
	Base Address : 0x4003 8000 (CRC)
*/

/* CRC Control register <CRC_CTRL> (0x00) */
																	//[1:0] CRC Polynomial
#define CRC_16_CCITT					0
#define CRC_16								1
#define CRC_32								2
#define mskCRC_TYPE						(CRC_16_CCITT << 0)

																	//[2:2] Reset bit
#define mskCRC_RESET					(1 << 2)

																	//[3:3] Enable bit of the CRC calculation for the 128KB/256KB User ROM.
#define CRC_CALC_NOR					0		// CRC operation for the fix data.
#define CRC_CALC_ROM					1		// CRC operation for the User ROM.
#define mskCRC_CALC_MODE			(CRC_CALC_ROM << 3)
														
																	//[4:4] CRC calculation busy flag.
#define mskCRC_BUSY						(1 << 4)

union crc_data_format
{
	uint32_t word;
	uint8_t	byte[4];
};

/*_____ M A C R O S ________________________________________________________*/
#define __CRC_ENABLE_PCLK			SN_SYS1->AHBCLKEN_b.CRCCLKEN = ENABLE		
#define __CRC_DISABLE_PCLK		SN_SYS1->AHBCLKEN_b.CRCCLKEN = DISABLE	
#define __CRC_BUSY						while (SN_CRC->CTRL_b.BUSY != 0);

/*_____ D E C L A R A T I O N S ____________________________________________*/
void CRC_Enable(void);
void CRC_Disable(void);
uint32_t CRC_Calc_NOR(uint32_t Start_Addr, uint32_t End_Addr);
uint32_t CRC_Calc_ROM(void);

#endif	/*__SN32F400_CRC_H*/
