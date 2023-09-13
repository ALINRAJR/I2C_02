/*
 * i2cslavedevice.h
 *
 * 
 */

#ifndef I2CSLAVEDEVICE_H_
#define I2CSLAVEDEVICE_H_

#include "i2c.h"
#define I2CSLAVEDEVICEADDRESS 			0x38
#define I2CSLAVEMAXPAGESIZE              63

void vI2CSlaveByteWrite(uint16_t devicememoryaddress,uint8_t bytetowrite);
void vI2CSlaveByteRead(uint8_t* ptrtobuffer);
void vI2CSlavePageWrite(uint16_t startingmemoryaddress,uint8_t* ptrtobufferofbytes, uint8_t bufferlength);
void vI2CSlaveCurrentAddressRead(uint8_t* ptrtobuffer);
void vI2CSlaveRandomAddressRead(uint16_t startingmemoryaddress,uint8_t* ptrtobufferofbytes, uint8_t bufferlength);
void vI2CSlaveSequentialRead(uint8_t* ptrtobufferofbytes, uint8_t bufferlength);
#endif /* I2CSLAVEDEVICE_H_ */
