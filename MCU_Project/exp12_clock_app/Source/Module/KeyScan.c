/******************** (C) COPYRIGHT 2013 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2016/03
* AUTHOR:				SA1
* IC:						SN32F240/230/220 
* DESCRIPTION:	LED_Function.c
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2018/12/21	SA1			1. First release
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
#include "KeyScan.h"
#include "..\Driver\Utility.h"
/*_____ D E C L A R A T I O N S ____________________________________________*/
#define	KEY_SHORT_PUSH_TIME	50
#define	KEY_DEBOUNCE_MAX_TIME	200

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ M A C R O S ________________________________________________________*/
uint8_t key_check = 0;
uint8_t key_cvt = 0;

	
uint8_t key_debounce = 0;
/*_____ F U N C T I O N S __________________________________________________*/
/*****************************************************************************
* Function		: KeyScan
* Description	: 
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
uint16_t KeyScan(void)
{
	uint8_t key_col,key_row;  
	
	uint8_t key = 0;
	uint16_t key_action = 0;
	
//read column
		//1. set column input pull up
		SN_GPIO2->MODE &= ~(0xf << 4);	//SN_GPIO2->MODE = SN_GPIO2->MODE & 0x3f0f;  		set P24~P27 input mode
		SN_GPIO2->CFG &= ~(0xff << 8);	//SN_GPIO2->CFG = SN_GPIO2->CFG & 0x0fff00ff;		set P24~P27 pull up 
		//2. set row output low
		SN_GPIO1->MODE |= 0xf << 4;			//set P14~P17 output
		SN_GPIO1->BCLR = 0xf << 4;
		//delay to wait gpio level stable
		UT_DelayNx10us(1);
		
		key_col = (SN_GPIO2->DATA >> 4) & 0xf;		//read P24~P27,at key_col bit0~bit3
		
		if(key_col)												// occur key push
		{
		//read row			
			//1. set row input pull up
			SN_GPIO1->MODE &= ~(0xf << 4);	//SN_GPIO1->MODE = SN_GPIO2->MODE & 0x3f0f;  		set P24~P27 input mode
			SN_GPIO1->CFG &= ~(0xff << 8);	//SN_GPIO1->CFG = SN_GPIO2->CFG & 0x0fff00ff;		set P24~P27 pull up 
			//2. set row output low
			SN_GPIO2->MODE |= 0xf << 4;			//set P24~P27 output
			SN_GPIO2->BCLR = 0xf << 4;
			//delay to wait gpio level stable
			UT_DelayNx10us(1);
			
			key_row = SN_GPIO1->DATA & 0xf0;		//read P14~P17,at key_row bit4~bit7
			
			key = key_col | key_row;
			
			key ^= 0xff;											//inverse to read push key's flag;
			
		}
		else																	//key idle
		{
			key = 0;													//none key push
		}


	if(key != key_check)									// key action change
	{						
		key_check = key;												
		key_debounce = 0;											
	}
	
	else if(key_debounce < KEY_DEBOUNCE_MAX_TIME)			//key debounce
	{
		key_debounce++;
	
		if(key_debounce == KEY_SHORT_PUSH_TIME)					//short key action
		{
			key = key_check ^ key_cvt;							
			key_cvt = key_check;
			
			if(key)																// key flag have been change
			{
				if(key & key_check)										//key push
				{
					key_action = KEY_PUSH_FLAG | key & key_check;
				}
				// key pop have not any function,mask key pop event
				else 																	//key pop
				{
					key_action = KEY_POP_FLAG | key;
				}				
				
			}

		}
	}
	
	
	return key_action;
}  

