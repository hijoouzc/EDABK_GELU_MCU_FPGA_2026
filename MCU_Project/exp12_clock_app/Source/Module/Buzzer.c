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
#include "buzzer.h"
#include "..\Driver\CT16B0.h"
/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
#define	SET_PITCH1_FREQ		261.62557f
#define	SET_PITCH2_FREQ		277.18263f
#define	SET_PITCH3_FREQ		293.66477f
#define	SET_PITCH4_FREQ		311.12698f
#define	SET_PITCH5_FREQ		329.62756f
#define	SET_PITCH6_FREQ		349.22823f
#define	SET_PITCH7_FREQ		369.99442f
#define	SET_PITCH8_FREQ		391.99544f
#define	SET_PITCH9_FREQ		415.30470f
#define	SET_PITCH10_FREQ	440.0f
#define	SET_PITCH11_FREQ	466.16376f
#define	SET_PITCH12_FREQ	493.88330f
#define	SET_PITCH13_FREQ	523.25113f

#define	HCLK_FREQ					12000000

/*_____ M A C R O S ________________________________________________________*/
const uint16_t musical_table[] = {
	
	(uint16_t)HCLK_FREQ/SET_PITCH1_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH2_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH3_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH4_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH5_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH6_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH7_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH8_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH9_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH10_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH11_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH12_FREQ,
	(uint16_t)HCLK_FREQ/SET_PITCH13_FREQ,
	
};
/*_____ F U N C T I O N S __________________________________________________*/
/*****************************************************************************
* Function		: set_buzzer_pitch
* Description	: set buzzer frequency
* Input			: pitch: input the pitch of buzzer
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void set_buzzer_pitch(uint8_t pitch)
{
	if(pitch < (sizeof(musical_table)>>1))
	{
		SN_CT16B0->MR9 = musical_table[pitch];
		SN_CT16B0->MR0 = SN_CT16B0->MR9 >> 1;
	}
	else
	{
		SN_CT16B0->MR0 = 0;		//disable buzzer;
	}
}
/*****************************************************************************
* Function		: buzzer_on
* Description	: Turn buzzer ON at fixed 1kHz (uses MR9 period, no change to MR9)
* Input			: None
* Output		: None
* Return		: None
* Note			: MR9 must be 11999 (1ms period). MR0 = MR9/2 = 50% duty = 1kHz
*****************************************************************************/
void buzzer_on(void)
{
	SN_CT16B0->MR9 = musical_table[1];
	SN_CT16B0->MR0 = SN_CT16B0->MR9 >> 1;	// 50% duty cycle, freq = 1/MR9_period
}

/*****************************************************************************
* Function		: buzzer_off
* Description	: Turn buzzer OFF
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void buzzer_off(void)
{
	SN_CT16B0->MR0 = 0;	// duty = 0% -> no output
}
