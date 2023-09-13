/*
===============================================================================
 Name        : Day38_Ex43_I2C002.c

 Description : I2C Master interfacing with AT24C256 EEPROM (I2C slave device) and
 	 	 	   another LPC1768 I2C slave device
 ===============================================================================
 Application.c/.h
 *********************
 eeprom.c/.h
 *********************
 uart.c/uart.h,gpio.c/.h,i2c.c/.h, pinmux.c/.h (chip level)
 **********************
 Hardware
 **********************
 */

#include "gpio.h"
#include <LPC17xx.h>
#include "pinmux.h"
#include "uart.h"
#include "i2c.h"
#include "eeprom.h"

/**
  * @brief  Crude Delay
  * @retval none
  */
void vAppDelay(uint32_t count)
{
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<0xA00;j++);

}

int main(void){

	    uint8_t buffer[4];
	    uint8_t rxbuffer[4];
	    uint8_t readbyte=0;
		/* Pinmux Initialize */
		vPinmuxInitialize();

		vUARTInitialize();
		vUARTPrintf(LPC_UART0,"I2C SLAVE Demonstration:\r\n");

		/* Master Initialization only required when the selected I2C controller act as a I2C master device */
		vI2CMasterInitialize(I2C0,I2C_0,I2C_100KHz);

		/* Slave Initialization only required only when the  selected I2C Peripheral act as I2C Slave device */
		vI2CSlaveInitialize(I2C2,I2C_2);

	    vI2CSlaveByteWrite(0x0050,0x0D);
	    vAppDelay(0xA00);


		//vI2CSlaveByteRead(buffer);
		//vAppDelay(0xA00);


		//vI2CSlaveCurrentAddressRead(&readbyte);
		//vUARTPrintf(LPC_UART0,"%c",readbyte);


		//vI2CSlavePageWrite(0x00A0,buffer,6);
		//vAppDelay(0xA00);


		//vI2CSlaveRandomAddressRead(0x0050,rxbuffer,6);
		//vUARTPrintf(LPC_UART0,"%s",rxbuffer);

/*
			vI2CSlaveSequentialRead(rxbuffer,4);
			vUARTPrintf(LPC_UART0,"%c",rxbuffer[0]);
			vUARTPrintf(LPC_UART0,"%c",rxbuffer[1]);
			vUARTPrintf(LPC_UART0,"%c",rxbuffer[2]);
			vUARTPrintf(LPC_UART0,"%c",rxbuffer[3]);
			vUARTPrintf(LPC_UART0,"%c",rxbuffer[4]);
			vUARTPrintf(LPC_UART0,"%c",rxbuffer[5]);

*/
			vUARTPrintf(LPC_UART0,"i2C Slave TEST FINISHED\r\n");

			/* Put a delay ()
		 *
		 */

		while(1)
	    {

		}
}
