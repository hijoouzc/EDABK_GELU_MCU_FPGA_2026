/******************** (C) COPYRIGHT 2020 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	I2C0 related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2023/11/06	SA1			1. First release
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
#include "I2C.h"
#include "SysTick.h"
#include "Utility.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: I2C_IRQHandler
* Description	: I2C interrupt service routine
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void I2C0_IRQHandler(void)
{		
	SN_I2C0->STAT = 1 << 15;
}
/*****************************************************************************
* Function		: I2C0_Init
* Description	: Set specified value to specified bits of assigned register
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void I2C0_Init(void)
{
//	//I2C0 interrupt enable
//	NVIC_ClearPendingIRQ(I2C0_IRQn);	
//	NVIC_EnableIRQ(I2C0_IRQn);
//	NVIC_SetPriority(I2C0_IRQn, 0);

	//Enable HCLK for I2C0
	SN_SYS1->AHBCLKEN_b.I2C0CLKEN = 1;						//Enable clock for I2C0

	//I2C0 speed
	SN_I2C0->SCLHT = I2C0_SCLHT;
	SN_I2C0->SCLLT = I2C0_SCLLT;
	
	//I2C0 enable
	SN_I2C0->CTRL_b.I2CEN = I2C_I2CEN_EN;
}

/*****************************************************************************
* Function		: I2C0_Start
* Description	: transmit a START bit
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void I2C0_Start(void)
{
	SN_I2C0->STAT = 1 << 15;		//clear I2C status change flag
	
	SN_I2C0->CTRL_b.STA = 1;		// tiggle a START or REPEAT START signal
	
	while((SN_I2C0->STAT & (1<<15)) == 0);	//while status change(STA have been tiggle)
}

/*****************************************************************************
* Function		: I2C0_Stop
* Description	: transmit a STOP condition in master mode
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void I2C0_Stop(void)
{
	SN_I2C0->STAT = 1 << 15;
	
	SN_I2C0->CTRL_b.STO = 1;		// tiggle a STOP signal
	
	while((SN_I2C0->STAT & (1<<15)) == 0);
}
/*****************************************************************************
* Function		: I2C_write_byte
* Description	: i2c write byte,and return ack/nack
* Input			: dat: data to be write
* Output		: None
* Return		: ack/nack
* Note			: None
*****************************************************************************/
uint8_t I2C_write_byte(uint8_t dat)
{
	SN_I2C0->STAT = 1 << 15;
	
	SN_I2C0->TXDATA = dat;									//send data
	
	while((SN_I2C0->STAT & (1<<15)) == 0);	//while status change,data send and received ACK or NACK
	
	if(SN_I2C0->STAT & (1 << 1))						//received an ack signal
		return I2C_ACK_FALG;
	else
		return I2C_NACK_FALG;
}

/*****************************************************************************
* Function		: I2C_read_byte
* Description	: i2c read byte,and return ack/nack
* Input			: ack: return ack/nack
* Output		: None
* Return		: read data
* Note			: None
*****************************************************************************/
uint8_t I2C_read_byte(uint8_t ack)
{
	SN_I2C0->STAT = 1 << 15;
	
	if(ack == I2C_ACK_FALG)									//insert an ACK or NACK after received data
	{
		SN_I2C0->CTRL_b.ACK = 1;
	}
	else
	{
		SN_I2C0->CTRL_b.NACK = 1;
	}
	
	while((SN_I2C0->STAT & (1<<15)) == 0);//i2c status change
	
	
	return SN_I2C0->RXDATA;
}




