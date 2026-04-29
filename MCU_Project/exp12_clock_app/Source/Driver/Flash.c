/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	Flash related functions.
*____________________________________________________________________________
* REVISION	Date				User		Description
* 1.0				2023/11/06	SA1			First release
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
#include "Flash.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/
uint32_t wFLASH_PGRAM[128];

/*_____ D E F I N I T I O N S ______________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*****************************************************************************
* Function		: FLASH_MassErase
* Description	: Mass Erase Flash ROM
* Input			: None
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void FLASH_MassErase(void)
{
	__FLASH_CLEAR_ERROR_STATUS;			// Reset Error Flags
 	
	SN_FLASH->CTRL = FLASH_MER;			// Mass Erase Enabled
	SN_FLASH->ADDR = 0x0;						// Page Address

	__FLASH_WAIT_FOR_DONE;
	
	__FLASH_START_OPERATION;				// Start Erase

	__FLASH_WAIT_FOR_DONE;
}

/*****************************************************************************
* Function		: FLASH_EraseSector
* Description	: Erase assigned sector address in Flash ROM
* Input			: adr - Sector start address
* Output		: None
* Return		: None
* Note			: None
*****************************************************************************/
void FLASH_EraseSector(volatile uint32_t adr)
{
	__FLASH_CLEAR_ERROR_STATUS;			// Reset Error Flags
	
 	SN_FLASH->CTRL = FLASH_PER;			// Page Erase Enabled
	SN_FLASH->ADDR = adr;						// Page Address

	__FLASH_WAIT_FOR_DONE;	
	
	__FLASH_START_OPERATION;				// Start Erase

	__FLASH_WAIT_FOR_DONE;
}

/*****************************************************************************
* Function		: Flash_ProgramPage
* Description	: Program assigned page in Flash ROM
* Input			: adr - Page start address (word-alignment) of Flash
*				  		sz - Content size to be programmed (Bytes)
*				  		pBuf - pointer to the Source data
* Output		: None
* Return		: OK or FAIL
* Note			: None
*****************************************************************************/
uint32_t FLASH_ProgramPage(volatile uint32_t adr, volatile uint32_t sz, uint8_t *pBuf)
{
	sz = (sz + 3) & ~3;											// Adjust size for Words
	
	SN_FLASH->STATUS  &= ~(FLASH_ERR);			// Reset Error Flags
	
	SN_FLASH->CTRL = FLASH_PG;                  // Programming Enabled
	
	SN_FLASH->ADDR = adr;
	
	while (sz)
	{
		SN_FLASH->DATA = *((uint32_t *)pBuf);

		if ((((adr >> 2) % 2) == 1) || (sz == 4)) 
		{
			SN_FLASH->CTRL |= FLASH_START;			// Start Program
			FLASH_WAIT_FOR_DONE;

			// FLASH_ERR = 0x04
			if (SN_FLASH->STATUS & FLASH_ERR) {	// Check for Errors
				return (FAIL);												// Failed
			}
    }
		
		// Go to next Word
		adr += 4;
		pBuf += 4;
		sz  -= 4;
		
	  if ((((adr >> 2) % 2) == 0)) 
		{
			SN_FLASH->CTRL = FLASH_PG;					// Programming Enabled
		  SN_FLASH->ADDR = adr;
		}
	}

	return (OK);
}

/*****************************************************************************
* Function		: FLASH_Checksum
* Description	: Calculate Checksum in Flash ROM
* Input			: None
* Output		: Checksum of User ROM
* Return		: None
* Note			: None
*****************************************************************************/
uint16_t FLASH_Checksum(void)
{
 	SN_FLASH->CTRL = FLASH_CHK;

	__FLASH_WAIT_FOR_DONE;
	
	return (uint16_t) (SN_FLASH->CHKSUM);
}
