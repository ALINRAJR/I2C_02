/*
 * i2c.h
 *
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include <LPC17xx.h>
#include "pinmux.h"

#define MAXTIMEOUT 0x00FFFFFF

enum {I2C_0=0,I2C_1,I2C_2};

enum {I2C_100KHz=0,I2C_400KHz};
enum {FALSE=0,TRUE};

enum{I2C_IDLE=0, I2C_STARTED, I2C_RESTARTED, I2C_REPEATED_START, DATA_ACK, DATA_NACK, I2C_WR_STARTED, I2C_RD_STARTED,I2C_SLA_NACK};


#define I2CWRITEOPERATION      0
#define I2CREADOPERATION       1

#define BIT_PCI2C0        7
#define BIT_PCI2C1        19
#define BIT_PCI2C2        26

#define BIT_PCLK_I2C0     14
#define BIT_PCLK_I2C1     6
#define BIT_PCLK_I2C2     20

#define I2C0 LPC_I2C0
#define I2C1 LPC_I2C1
#define I2C2 LPC_I2C2

#define BIT_I2CONSET_AA         1<<2            //(0x4001 C000,0x4005 C000,0X400A 0000)
#define BIT_I2CONSET_SI         1<<3
#define BIT_I2CONSET_STO        1<<4
#define BIT_I2CONSET_STA        1<<5
#define BIT_I2CONSET_I2EN       1<<6
#define BIT_I2CONCLR_AAC        1<<2           //(0x4001 C018,0x4005 C018,0x400A 0018)
#define BIT_I2CONCLR_SIC        1<<3
#define BIT_I2CONCLR_STAC       1<<5
#define BIT_I2CONCLR_I2ENC      1<<6
#define BIT_I2STAT_STATUS       3          //(0x4001 C004,0x4005 C004,0x400A 0004)
#define BIT_I2DAT_DATA          0          //(0x4001 C008,0x4005 C008,0x400A 0008)
#define BIT_I2MMCTRL_MM_ENA     0          //(0x4001 C01C,0x4005 C01C,0x400A 001C)
#define BIT_I2MMCTRL_ENA_SCL    1
#define BIT_I2MMCTRL_MATCH_ALL  2
#define BIT_I2DATA_BUFFER_DATA  0          //(0x4001 C02C,0x4005 C02C,0x400A 002C)
#define BIT_I2ADRO_GC           0          //(0x4001 C0[0C,20,24,28],0x4005 C0[0C,20,24,28],0x400A 00[0C,20,24,28])
#define BIT_I2ADRO_ADDRESS      1
#define BIT_I2MASK_MASK         1          //(0x4001 C0[30,34,38,3C],0x4005 C0[30,34,38,3C],0x400A 00[30,34,38,3C])
#define BIT_I2SCLH_SCLL         0          //(0x4001 C014,0x4005 C014,0x400A 0014)



/* Function for making the selected I2C Peripheral as I2C Master*/
void vI2CMasterInitialize(LPC_I2C_TypeDef *I2Cx,uint8_t i2cnum,uint8_t sclclk );
/* Function for making the selected I2C Peripheral as I2C Slave*/
void vI2CSlaveInitialize(LPC_I2C_TypeDef *I2Cx,uint8_t i2cnum);
/* Call back function when selected  I2C acts as Master*/
void vI2CMasterStateMachine(LPC_I2C_TypeDef *I2Cx);
/* Call back function when selected  I2C acts as Slave*/
void vI2CSlaveStateMachine(LPC_I2C_TypeDef *I2Cx);

/* Function which waits until a current I2C transaction is complete */
uint8_t ucI2CEngine(LPC_I2C_TypeDef *I2Cx);

#endif /* I2C_H_ */
