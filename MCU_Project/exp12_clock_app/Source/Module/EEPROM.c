/******************** (C) COPYRIGHT 2021 SONiX *******************************
* COMPANY:	SONiX
* DATE:			2023/11
* AUTHOR:		SA1
* IC:				SN32F400
*____________________________________________________________________________
*	REVISION	Date				User		Description
*	1.0				2023/11/07	SA1			1. First version released
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
#include "EEPROM.h"
#include "..\Driver\I2C.h"
/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/
/*****************************************************************************
* Function		: eeprom_write
* Description	: write data to eeprom
* Input			: addr: slaver address
						   reg: eeprom addr
							 dat: data to be write
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void eeprom_write(uint8_t addr,uint8_t reg,uint8_t *dat,uint16_t length)
{
	I2C0_Start();															
	if(I2C_write_byte(addr) == I2C_NACK_FALG)					//send slaver addr
	{
		I2C0_Stop();
		return;
	}
	if(I2C_write_byte(reg) == I2C_NACK_FALG)					//send eeprom address
	{
		I2C0_Stop();
		return;
	}	
	
	while(length--)
	{
		if(I2C_write_byte(*dat++) == I2C_NACK_FALG)					//write data
		{
			I2C0_Stop();
			return;
		}	
	}
	I2C0_Stop();
}

/*****************************************************************************
* Function		: eeprom_read
* Description	: read data from eeprom
* Input			: addr: slaver address
						   reg: eeprom addr
							*dat: save read data
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void eeprom_read(uint8_t addr,uint8_t reg,uint8_t *dat,uint16_t length)
{
	I2C0_Start();
	if(I2C_write_byte(addr&0xfe) == I2C_NACK_FALG)			//send slaver addr|W
	{
		I2C0_Stop();
		return;
	}
	if(I2C_write_byte(reg) == I2C_NACK_FALG)						//send eeprom address
	{
		I2C0_Stop();
		return;
	}	
	I2C0_Start();																				//repeat start
	
	if(I2C_write_byte(addr) == I2C_NACK_FALG)						//send slaver addr|R
	{
		I2C0_Stop();
		return;
	}	
	while(length > 1)
	{
		*dat++ = I2C_read_byte(I2C_ACK_FALG);								//read data and return ack
		length--;
	}
	
	*dat++ = I2C_read_byte(I2C_NACK_FALG);								//read data and return nack
	I2C0_Stop();
}

/*****************************************************************************
* Function		: eeprom_check
* Description	: Check if EEPROM internal write cycle is finished (ACK Polling)
* Input			: addr: slaver address
* Output		: None
* Return		: 1 if Ready (ACK), 0 if Busy (NACK)
* Note			: None
*****************************************************************************/
uint8_t eeprom_check(uint8_t addr)
{
    uint8_t status;

    I2C0_Start();

    // luôn dùng write mode cho ACK polling
    status = I2C_write_byte(addr & 0xFE);

    I2C0_Stop();

    return (status == I2C_ACK_FALG);
}
