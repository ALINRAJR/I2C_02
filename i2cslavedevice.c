/*
 * i2cslavedevice.c


 */

#include "i2cslavedevice.h"

extern volatile uint8_t I2CMasterTxBuffer[70], I2CMasterRxBuffer[70];
extern volatile uint8_t I2CMasterReadLength, I2CMasterWriteLength;

void vI2CSlaveByteWrite(uint16_t devicememoryaddress,uint8_t bytetowrite)
{
	I2CMasterReadLength = 0; /* Nothing do with read length*/
	I2CMasterWriteLength = 4; /* 4 bytes -> SLA+MSB memory address + LSB memory address + byte */

	/* Placing the Slave Address in write mode into the I2C Master tx buffer */
	I2CMasterTxBuffer[0] = I2CSLAVEDEVICEADDRESS << 1 | I2CWRITEOPERATION;
	/* Placing the device MSB of the memory address into the I2C Master tx buffer */
	I2CMasterTxBuffer[1] = devicememoryaddress >> 8 & 0xFF;
	/* Placing the device LSB of the memory address into the I2C Master tx buffer */
	I2CMasterTxBuffer[2] = devicememoryaddress & 0xFF;
	/* Placing the byte to be written to the selected memory address into the I2C Master tx buffer */
	I2CMasterTxBuffer[3] = bytetowrite;
	/* Starting the I2C Engine */
	ucI2CEngine(LPC_I2C0);
}



/* Function for read a byte from the current location */
void vI2CSlaveByteRead(uint8_t* ptrtobuffer)
{
	I2CMasterReadLength = 1; /* Reading a byte */
	I2CMasterWriteLength =1; /* For writing the slave address in read mode */

	/* Placing the  Slave Address in read mode into the I2C Master tx buffer */
	I2CMasterTxBuffer[0] = I2CSLAVEDEVICEADDRESS << 1 | I2CREADOPERATION;

	/* Starting the I2C Engine */
	ucI2CEngine(LPC_I2C0);

	 /* Placing the received byte from I2C Master Rx buffer into our application buffer */
	*ptrtobuffer =I2CMasterRxBuffer[0];

}

void vI2CSlavePageWrite(uint16_t startingmemoryaddress,uint8_t* ptrtobufferofbytes, uint8_t bufferlength)
{
		int i=0;

		I2CMasterReadLength = 0; /* Nothing do with read length*/

		if (bufferlength <= I2CSLAVEMAXPAGESIZE )
			I2CMasterWriteLength = 3 + bufferlength; /* 3 + bufferlength no of bytes -> SLA+MSB memory address + LSB memory address + byte */

		/* Placing the EEPROM Slave Address in write mode  into the I2C Master tx buffer */
		I2CMasterTxBuffer[0] = I2CSLAVEDEVICEADDRESS << 1 | I2CWRITEOPERATION;
		/* Placing the EEPROM device MSB of the memory address into the I2C Master tx buffer */
		I2CMasterTxBuffer[1] = startingmemoryaddress >> 8 & 0xFF;
		/* Placing the EEPROM device LSB of the memory address into the I2C Master tx buffer */
		I2CMasterTxBuffer[2] = startingmemoryaddress & 0xFF;

		/* Placing the bytes to be written to the selected starting memory address into the I2C Master tx buffer */
		for(i=0;i<bufferlength;i++)
			I2CMasterTxBuffer[3+i]= ptrtobufferofbytes[i];

		/* Starting the I2C Engine */
			ucI2CEngine(LPC_I2C0);
}

void vI2CSlaveCurrentAddressRead(uint8_t* ptrtobuffer)
{
		I2CMasterReadLength = 1; /* Reading a byte */
		I2CMasterWriteLength =1; /* For writing the EEPROM slave address in read mode */

		/* Placing the EEPROM Slave Address in read mode into the I2C Master tx buffer */
		I2CMasterTxBuffer[0] = I2CSLAVEDEVICEADDRESS << 1 | I2CREADOPERATION;

		/* Starting the I2C Engine */
		ucI2CEngine(LPC_I2C0);

		 /* Placing the received byte from I2C Master Rx buffer into our application buffer */
		*ptrtobuffer =I2CMasterRxBuffer[0];

}

void vI2CSlaveRandomAddressRead(uint16_t startingmemoryaddress,uint8_t* ptrtobufferofbytes, uint8_t bufferlength)
{
		int i = 0;

		if (bufferlength <= I2CSLAVEMAXPAGESIZE )
			I2CMasterWriteLength = 3; /* 3bytes -> SLA+MSB memory address + LSB memory address*/

		/* Placing the EEPROM Slave Address in write mode into the I2C Master tx buffer */
		I2CMasterTxBuffer[0] = I2CSLAVEDEVICEADDRESS << 1 | I2CWRITEOPERATION;
		/* Placing the EEPROM device MSB of the memory address into the I2C Master tx buffer */
		I2CMasterTxBuffer[1] = startingmemoryaddress >> 8 & 0xFF;
		/* Placing the EEPROM device LSB of the memory address into the I2C Master tx buffer */
		I2CMasterTxBuffer[2] = startingmemoryaddress & 0xFF;


		I2CMasterReadLength = bufferlength; /* Nothing do with read length*/
		/* Placing the EEPROM Slave Address in read mode into the I2C Master tx buffer */
		I2CMasterTxBuffer[3] = I2CSLAVEDEVICEADDRESS << 1 | I2CREADOPERATION;

	   /* Starting the I2C Engine */
		ucI2CEngine(LPC_I2C0);

		 /* Placing the received bytes from I2C Master Rx buffer into our application buffer */
		for(i=0;i<bufferlength;i++)
			ptrtobufferofbytes[i] =I2CMasterRxBuffer[i];

}

void vI2CSlaveSequentialRead(uint8_t* ptrtobufferofbytes, uint8_t bufferlength)
{
			int i = 0;

			if (bufferlength <= I2CSLAVEMAXPAGESIZE )
				I2CMasterReadLength = bufferlength;

			I2CMasterWriteLength = 1; /* 1 byte -> SLA*/
			/* Placing the EEPROM Slave Address in read mode into the I2C Master tx buffer */
			I2CMasterTxBuffer[0] = I2CSLAVEDEVICEADDRESS << 1 | I2CREADOPERATION;

			/* Starting the I2C Engine */
			ucI2CEngine(LPC_I2C0);

			/* Placing the received bytes from I2C Master Rx buffer into our application buffer */
			for(i=0;i<bufferlength;i++)
				ptrtobufferofbytes[i] =I2CMasterRxBuffer[i];


}






