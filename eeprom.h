/*
 * eeprom.h

 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "i2c.h"

#define AT24C256EEPROMADEVICEADDRESS     0x50
#define AT24C256MAXPAGESIZE              63


#define EEPROMI2C I2C0

/* Funcion for writing a byte ins a selected device memory location */
void vEEPROMByteWrite(uint16_t devicememoryaddress,uint8_t bytetowrite);
/* Function for writing bytes of data from the buffer into the selected starting memory location */
void vEEPROMPageWrite(uint16_t startingmemoryaddress,uint8_t* ptrtobufferofbytes, uint8_t bufferlength);
/* Function for read a byte from the current location */
void vEEPROMCurrentAddressRead(uint8_t* ptrtobuffer);
/* Function for reading bytes of data to the buffer from the selected starting memory location */
void vEEPROMRandomAddressRead(uint16_t startingmemoryaddress,uint8_t* ptrtobufferofbytes, uint8_t bufferlength);
/* Function for reading bytes of data to the buffer from the selected starting memory location */
void vEEPROMSequentialRead(uint8_t* ptrtobufferofbytes, uint8_t bufferlength);


#endif /* EEPROM_H_ */
