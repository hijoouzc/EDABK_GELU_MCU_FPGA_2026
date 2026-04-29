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
#include "Segment.h"
#include "..\Driver\GPIO.h"
/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	SEG_A		0x01
#define	SEG_B		0x02
#define	SEG_C		0x04
#define	SEG_D		0x08
#define	SEG_E		0x10
#define	SEG_F		0x20
#define	SEG_G		0x40
#define	SEG_H		0x80

/*_____ M A C R O S ________________________________________________________*/
const uint8_t SEGMENT_TABLE[] = {
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F),					//0
	(SEG_B|SEG_C),																	//1
	(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G),								//2
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G),								//3
	(SEG_B|SEG_C|SEG_F|SEG_G),											//4
	(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G),								//5
	(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),					//6
	(SEG_A|SEG_B|SEG_C),														//7
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),		//8
	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G),					//9
	(SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G),					//A
	(SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),											//b
	(SEG_A|SEG_D|SEG_E|SEG_F),											//C
	(SEG_B|SEG_C|SEG_D|SEG_E|SEG_G),								//d
	(SEG_A|SEG_D|SEG_E|SEG_F|SEG_G),								//E
	(SEG_A|SEG_E|SEG_F|SEG_G),											//F
	(SEG_A|SEG_E|SEG_F|SEG_G),											//-   //unknow
	
};
uint8_t com_scan = 0;

uint8_t segment_buff[4];
/*_____ F U N C T I O N S __________________________________________________*/
/*****************************************************************************
* Function		: Digital_Display_Clock
* Description	: Display time (Hour : Minute) on the 7-segment LED
* Input			: hour: the hour to be displayed (0-23)
* minute: the minute to be displayed (0-59)
* show_colon: 1 to enable the middle dot, 0 to disable (for blinking effect)
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void Digital_Display_Clock(uint8_t hour, uint8_t minute)
{
	// 1. Check the validity of the input data
	if(hour > 23 || minute > 59)
	{
		// If the data is invalid, display 4 dashes "----" to indicate an error
		segment_buff[0] = SEG_G;
		segment_buff[1] = SEG_G;
		segment_buff[2] = SEG_G;
		segment_buff[3] = SEG_G;
		return;
	}

	// 2. Process Hour display (LED 0 and LED 1)
	segment_buff[0] = SEGMENT_TABLE[hour / 10];    // Get the tens digit of the hour
	segment_buff[1] = SEGMENT_TABLE[hour % 10] | SEG_H;    // Get the units digit of the hour

	// 3. Process Minute display (LED 2 and LED 3)
	segment_buff[2] = SEGMENT_TABLE[minute / 10];  // Get the tens digit of the minute
	segment_buff[3] = SEGMENT_TABLE[minute % 10];  // Get the units digit of the minute
}
/*****************************************************************************
* Function		: Digital_DisplayDEC
* Description	: set display number with decimalism
* Input			: number: the number to be display
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void Digital_DisplayDEC(uint16_t dec)
{
	if(dec > 9999)
	{
		segment_buff[0] = SEG_G;
		segment_buff[1] = SEG_G;
		segment_buff[2] = SEG_G;
		segment_buff[3] = SEG_G;
	}
	else
	{
		segment_buff[3] = SEGMENT_TABLE[dec % 10];
		dec /= 10;                            
		segment_buff[2] = SEGMENT_TABLE[dec % 10];
		dec /= 10;                            
		segment_buff[1] = SEGMENT_TABLE[dec % 10];
		dec /= 10;		                        
		segment_buff[0] = SEGMENT_TABLE[dec % 10];	
	}
}
/*****************************************************************************
* Function		: Digital_DisplayHEX
* Description	: set display number with hexadecimal
* Input			: number: the number to be display
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void Digital_DisplayHEX(uint16_t dec)
{
	
		segment_buff[3] = SEGMENT_TABLE[dec & 0xf];
		dec >>= 4;
		segment_buff[2] = SEGMENT_TABLE[dec & 0xf];
		dec >>= 4;
		segment_buff[1] = SEGMENT_TABLE[dec & 0xf];
		dec >>= 4;
		segment_buff[0] = SEGMENT_TABLE[dec & 0xf];
	
}
/*****************************************************************************
* Function		: Digital_Scan
* Description	: polling driver digital tube COM to display by order
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void Digital_Scan(void)
{
	//segment off to change COM pin
	SN_GPIO0->BCLR = 0xff;
	SN_GPIO1->BCLR = 0xf << 9;
	
	//COM pin change
	com_scan++;
	if(com_scan >= 4)									//COM0~COM3 
		com_scan = 0;
	
	//set COM pin output high
	switch(com_scan)
	{
		case 0:													//display COM0
			SN_GPIO1->BSET = 1 << 9;
			break;
		case 1:													//display COM1
			SN_GPIO1->BSET = 1 << 10;
			break;		
		case 2:													//display COM2
			SN_GPIO1->BSET = 1 << 11;
			break;
		case 3:													//display COM3
			SN_GPIO1->BSET = 1 << 12;								
			break;
		default:
			break;
	}
	//set segment display
	SN_GPIO0->BSET = segment_buff[com_scan];
	
	
	
}
