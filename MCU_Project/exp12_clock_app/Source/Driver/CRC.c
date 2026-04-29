/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	CRC related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2023/11/07	SA1			First release
*
*____________________________________________________________________________
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS TIME TO MARKET.
* SONiX SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL 
* DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE
* AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN 
* IN CONNECTION WITH THEIR PRODUCTS.
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/
#include <SN32F400.h>
#include <SN32F400_Def.h>
#include "CRC.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: CRC_Enable
* Description	: Enable PCLK for CRC
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CRC_Enable(void)
{
	__CRC_ENABLE_PCLK;
}

/*****************************************************************************
* Function		: CRC_Disable
* Description	: Disable PCLK for CRC
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void CRC_Disable(void)
{
	__CRC_DISABLE_PCLK;
}

/*****************************************************************************
* Function		: CRC_Calc_NOR
* Description	: Calculate CRC value within setting range
* Input			: None
* Output		: None
* Return		: CRC caliculate result
* Note			: None
*****************************************************************************/
uint32_t CRC_Calc_NOR(uint32_t Start_Addr, uint32_t End_Addr)
{
	union crc_data_format crc_data;
	
	for (; Start_Addr <= End_Addr; Start_Addr += 4)
	{
		//Get ROM Data and Split ROM Data(1 Word Split to 4Byte)
		crc_data.word = __REV(*(volatile uint32_t *)(Start_Addr));
		
		SN_CRC->DATA = crc_data.byte[0];
		SN_CRC->DATA = crc_data.byte[1];
		SN_CRC->DATA = crc_data.byte[2];
		SN_CRC->DATA = crc_data.byte[3];
	}
	return (SN_CRC->DATA);
}

/*****************************************************************************
* Function		: CRC_Calc_ROM
* Description	: Start calculate ROM CRC by HW
* Input			: None
* Output		: None
* Return		: CRC caliculate result
* Note			: None
*****************************************************************************/
uint32_t CRC_Calc_ROM(void)
{
	SN_CRC->CTRL |= mskCRC_CALC_MODE;
	__CRC_BUSY;
	return SN_CRC->DATA;
}
