/*
struct tree
	main.c: initial and main loop function
	PFPA.c: set P3.1/P3.2 are UART0 UTXD/URXD
	GPIO.c: initial gpio pin
	 WDT.c: initial watchdog with 250ms reset while do nothing
   SPI.c:   intital SPI 
 utility.c: delay
 keyscan.c: scan key metrix
 segment.c:	display FLASH R/W address with BCD format
 sst_flash.c: driver to read and write sst flash
 
 function:
 
 	1. keyscan input R/W addr
	   KEY1~KEY10: input data 0~9 with BCD format
	   KEY13:	reset R/W addr with 0
	   KEY12:	read sst flash
	   KEY16:	write sst flash
	   
	2. display R/W flash addr with BCD format
	
	note: limit R/W flash addr less than 9999
	
	
*/