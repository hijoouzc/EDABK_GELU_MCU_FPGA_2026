/******************** (C) COPYRIGHT 2023 SONiX *******************************
* COMPANY:			SONiX
* DATE:					2023/11
* AUTHOR:				SA1
* IC:						SN32F400
* DESCRIPTION:	PFPA related functions.
*____________________________________________________________________________
*	REVISION	Date				User		Description
*	1.0				2023/11/06	SA1			1. First version release
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


/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
//<e0> UART0
//		<o8.2> URXD0=
//					<0=> P0.11
//					<1=> P2.0
//					<2=> P3.2
//					<3=> P2.10
//		<o8.0> UTXD0=
//					<0=> P0.10
//					<1=> P2.1
//					<2=> P3.1
//					<3=> P2.9
//</e>
//<e1> UART1
//		<o9.2> URXD1=
//					<0=> P1.8
//					<1=> P2.3
//					<2=> P2.8
//					<3=> P1.1
//		<o9.0> UTXD1=
//					<0=> P1.9
//					<1=> P2.2
//					<2=> P2.7
//					<3=> P1.0
//</e>
//<e2> SPI0
//		<o10.4> SCK0=
//					<0=> P0.0
//					<1=> P2.5
//					<2=> P1.0
//					<3=> P3.0
//		<o10.6> SEL0=
//					<0=> P0.1
//					<1=> P2.4
//					<2=> P1.8
//					<3=> P1.7
//		<o10.0> MISO0=
//					<0=> P0.2
//					<1=> P2.6
//					<2=> P1.1
//					<3=> P3.1
//		<o10.2> MOSI0=
//					<0=> P0.3
//					<1=> P2.7
//					<2=> P1.2
//					<3=> P3.2
//</e>
//<e3> I2C0
//		<o11.2..3> SCL0=
//					<0=> P0.6
//					<1=> P1.4
//					<2=> P0.10
//					<3=> P1.1
//		<o11.0..1> SDA0=
//					<0=> P0.7
//					<1=> P1.5
//					<2=> P0.11
//					<3=> P1.2
//</e>
//<e4> CT16B0
//		<o12.0> PWM0=
//					<0=> P0.2
//					<1=> P3.0
//					<2=> P2.6
//					<3=> P0.0
//		<o12.2> PWM0N=
//					<0=> P0.3
//					<1=> P0.1
//					<2=> P2.7
//					<3=> P1.1
//		<o12.4> PWM1=
//					<0=> P2.9
//					<1=> P3.1
//					<2=> P0.1
//					<3=> P2.5
//		<o12.6> PWM1N=
//					<0=> P0.2
//					<1=> P0.0
//					<2=> P2.8
//					<3=> P2.4
//		<o12.8> PWM2=
//					<0=> P2.7
//					<1=> P3.2
//					<2=> P0.0
//					<3=> P2.8
//		<o12.10> PWM2N=
//					<0=> P2.8
//					<1=> P2.6
//					<2=> P2.9
//					<3=> P0.1
//		<o12.12> PWM3=
//					<0=> P0.1
//					<1=> P0.5
//					<2=> P0.3
//					<3=> P3.2
//		<o12.14> PWM3N=
//					<0=> P0.0
//					<1=> P0.1
//					<2=> P0.2
//					<3=> P3.1
//		<o12.30> BRK=
//					<0=> P0.5
//					<1=> P0.10
//					<2=> P1.12
//					<3=> P2.10
//</e>
//<e5> CT16B1
//		<o13.0> PWM0=
//					<0=> P2.10
//					<1=> P1.1
//					<2=> P1.12
//					<3=> P2.0
//		<o13.2> PWM1=
//					<0=> P0.5
//					<1=> P1.2
//					<2=> P2.8
//					<3=> P2.4
//		<o13.4> PWM2=
//					<0=> P0.6
//					<1=> P0.10
//					<2=> P2.0
//					<3=> P2.7
//		<o13.6> PWM3=
//					<0=> P0.7
//					<1=> P0.11
//					<2=> P2.1
//					<3=> P2.9
//</e>
//<e6> CT16B5
//		<o14.0> PWM0=
//					<0=> P2.6
//					<1=> P2.4
//					<2=> P1.1
//					<3=> P0.3
//		<o14.2> PWM1=
//					<0=> P2.7
//					<1=> P2.3
//					<2=> P1.2
//					<3=> P0.2
//		<o14.4> PWM2=
//					<0=> P2.8
//					<1=> P2.2
//					<2=> P1.0
//					<3=> P0.1
//		<o14.6> PWM3=
//					<0=> P2.9
//					<1=> P2.1
//					<2=> P1.3
//					<3=> P0.0
//</e>
//<e7> CMP
//		<o15.0> CM0O=
//					<0=> P2.0
//					<1=> P2.6
//					<2=> P1.6
//					<3=> P3.0
//		<o15.2> CM1O=
//					<0=> P2.2
//					<1=> P2.7
//					<2=> P1.10
//					<3=> P3.1
//		<o15.4> CM2O=
//					<0=> P1.0
//					<1=> P0.3
//					<2=> P3.8
//					<3=> P1.11
//		<o15.6> CM3O=
//					<0=> P3.0
//					<1=> P2.8
//					<2=> P3.12
//					<3=> P1.3
//</e>
*/

#define UART0_EN		1	//e0
#define UART1_EN		1	//e1
#define SPI0_EN			0	//e2
#define I2C0_EN			1	//e3
#define CT16B0_EN		0	//e4
#define CT16B1_EN		0	//e5
#define CT16B5_EN		0	//e6
#define CMP_EN			0	//e7

#define PFPA_UART0_VAL			0x00000000
#define PFPA_UART1_VAL			0x00000005
#define PFPA_SPI0_VAL			  0x00000000
#define PFPA_I2C0_VAL			  0x0000000A
#define PFPA_CT16B0_VAL		  0x00000000
#define PFPA_CT16B1_VAL		  0x00000000
#define PFPA_CT16B5_VAL		  0x00000000
#define PFPA_CMP_VAL		    0x00000000


/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*_____ D E C L A R A T I O N S ____________________________________________*/



/*_____ F U N C T I O N S __________________________________________________*/
void PFPA_Init (void)
{
	SN_PFPA->UART0  = PFPA_UART0_VAL;
	SN_PFPA->UART1  = PFPA_UART1_VAL;
	SN_PFPA->SPI0   = PFPA_SPI0_VAL;
	SN_PFPA->I2C0   = PFPA_I2C0_VAL;
	SN_PFPA->CT16B0 = PFPA_CT16B0_VAL;
	SN_PFPA->CT16B1 = PFPA_CT16B1_VAL;
	SN_PFPA->CT16B5 = PFPA_CT16B5_VAL;
	SN_PFPA->CMP    = PFPA_CMP_VAL;
}
