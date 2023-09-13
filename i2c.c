/*
 * i2c.c
 *

 */


#include "i2c.h"
#include "uart.h"

/* Tx and Rx Buffer, write and read lengths are used in I2C Master mode */
volatile uint8_t I2CMasterTxBuffer[70], I2CMasterRxBuffer[70];
volatile uint8_t I2CMasterReadLength=0, I2CMasterWriteLength=0;
volatile uint8_t I2CMasterWriteIndex=0,I2CMasterReadIndex=0;

/* Tx and Rx Buffer, write and read indexes are used in I2C Slave mode */
volatile uint8_t I2CSlaveTxBuffer[70], I2CSlaveRxBuffer[70];
volatile uint8_t I2CSlaveWriteIndex=0,I2CSlaveReadIndex=0;


volatile uint8_t I2CMasterState = I2C_IDLE;

volatile uint8_t I2CSlaveState = I2C_IDLE;


/* Function for enabling and disabling the power to the selected I2C Peripheral*/
void vI2CPowerControl(uint8_t i2cnum,uint8_t mode)
{
	switch(i2cnum)
	{
	case I2C_0:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCI2C0;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCI2C0);
		break;
	case I2C_1:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCI2C1;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCI2C1);
		break;
	case I2C_2:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCI2C2;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCI2C2);
		break;
	}
}

/* Function for selecting the clock for the selected I2C Peripheral*/
void vI2CClockSel(uint8_t i2cnum,uint8_t clocksel)
{
	switch(i2cnum)
	{
	case I2C_0:
	LPC_SC->PCLKSEL0 &= ~(3<<BIT_PCLK_I2C0);
	LPC_SC->PCLKSEL0 |= clocksel<<BIT_PCLK_I2C0;
	break;
	case I2C_1:
	LPC_SC->PCLKSEL1 &= ~(3<<BIT_PCLK_I2C1);
	LPC_SC->PCLKSEL1 |= clocksel<<BIT_PCLK_I2C1;
	break;
	case I2C_2:
	LPC_SC->PCLKSEL1 &= ~(3<<BIT_PCLK_I2C2);
	LPC_SC->PCLKSEL1 |= clocksel<<BIT_PCLK_I2C2;
	break;
	}
}

/* Function for selecting the serial clock out for the selected I2C Peripheral when acting as I2C Master*/
void vI2CSerialClkFreq(LPC_I2C_TypeDef *I2Cx, uint8_t sclclk)
{
	switch (sclclk) {
	case I2C_100KHz:
		I2Cx->I2SCLL = 125;
		I2Cx->I2SCLH = 125;
		break;
	case I2C_400KHz:
		I2Cx->I2SCLL = 31;
		I2Cx->I2SCLH = 31;
		break;
	}
}

/* Function for enabling the selected I2C Peripheral as a Master */
void vI2CMasterEnable(LPC_I2C_TypeDef *I2Cx)
{
	I2Cx->I2CONCLR=BIT_I2CONCLR_AAC | BIT_I2CONCLR_SIC | BIT_I2CONCLR_STAC;
	I2Cx->I2CONSET=BIT_I2CONSET_I2EN;
}

/* Function for enabling the selected I2C Peripheral as a Slave */
void vI2CSlaveEnable(LPC_I2C_TypeDef *I2Cx)
{
	I2Cx->I2CONCLR=BIT_I2CONCLR_AAC | BIT_I2CONCLR_SIC | BIT_I2CONCLR_STAC;
	I2Cx->I2CONSET=BIT_I2CONSET_I2EN | BIT_I2CONSET_SI;

	/* Setting the I2C 7bit  Slave address 0x38 in bits (7:1) and enabling the general call address bit for i2c slave
	 *  to respond when  master sends 0x00 (broad cast address)as the slave address */
	LPC_I2C2->I2ADR0 = 0x38<<1 | 1<<BIT_I2ADRO_GC; //Slave address 0111 000(7:1)  --> 0011 1000 --> 0x38

}

/* Function called for starting the I2C Transaction */
uint8_t  ucI2CStart(LPC_I2C_TypeDef *I2Cx)
{

		uint32_t timeout=0;
		/* Starting the I2C Transaction */
		I2Cx->I2CONSET = BIT_I2CONSET_STA;

		while(1)
		{
			timeout++;
			/*Waiting for the I2CMasterState to I2C_STARTED state for a timeout , if it is not changed to I2C_STARTED state means within timeout , I2C transaction is a failure */
			if(I2CMasterState == I2C_STARTED)
			{
					return TRUE;
			}

			if(timeout> MAXTIMEOUT)
				return FALSE;
		}

}

/* Function called for ending the current I2C Transaction */
uint8_t ucI2CStop(LPC_I2C_TypeDef *I2Cx)
{

		/* Stop bit is set for the I2C transaction and indicates the end of I2C transaction */
			I2Cx->I2CONSET = BIT_I2CONSET_STO;
			I2Cx->I2CONCLR = BIT_I2CONCLR_SIC; /* Clear SI flag */
				/*--- Wait for STOP detected ---*/
				while (I2Cx->I2CONSET & BIT_I2CONSET_STO);
				return TRUE;
}

/* Function which waits until a current I2C transaction is complete */
uint8_t  ucI2CEngine(LPC_I2C_TypeDef *I2Cx)
{
				/* Making initial I2CMasterState as I2C_IDLE */
				I2CMasterState=I2C_IDLE;
				/* Clearing I2CMasterWriteIndex & I2CMasterReadIndex */
				I2CMasterWriteIndex=0;
				I2CMasterReadIndex=0;
				/* If ucI2CStart is false , end the transaction by ucI2CStop */
				if(ucI2CStart(I2Cx)==FALSE)
				{
					ucI2CStop(I2Cx);
					return FALSE;
				}
				while(1)
				{
				   if (I2CMasterState == DATA_NACK)
				   {
						ucI2CStop(I2Cx);
						break;
				   }
				}
				return TRUE;
}

/* Function for making the selected I2C Peripheral as I2C Master*/
void vI2CMasterInitialize(LPC_I2C_TypeDef *I2Cx,uint8_t i2cnum,uint8_t sclclk )
{
	vI2CPowerControl(i2cnum, POWERON);
	vI2CClockSel(i2cnum, ONEFOURTH);
	vI2CSerialClkFreq(I2Cx,sclclk);
	vI2CMasterEnable(I2Cx);
	switch (i2cnum) {
	case I2C_0:
		NVIC_EnableIRQ(I2C0_IRQn);
		break;
	case I2C_1:
		NVIC_EnableIRQ(I2C1_IRQn);
		break;
	case I2C_2:
		NVIC_EnableIRQ(I2C2_IRQn);
		break;
	}
}

/* Function for making the selected I2C Peripheral as I2C Slave*/
void vI2CSlaveInitialize(LPC_I2C_TypeDef *I2Cx,uint8_t i2cnum)
{
	vI2CPowerControl(i2cnum, POWERON);
	vI2CClockSel(i2cnum, ONEFOURTH);
	vI2CSlaveEnable(I2Cx);
	switch (i2cnum) {
		case I2C_0:
			NVIC_EnableIRQ(I2C0_IRQn);
			break;
		case I2C_1:
			NVIC_EnableIRQ(I2C1_IRQn);
			break;
		case I2C_2:
			NVIC_EnableIRQ(I2C2_IRQn);
			break;
		}

}

/* Call back function when selected  I2C acts as Master*/
void vI2CMasterStateMachine(LPC_I2C_TypeDef *I2Cx){

	volatile uint8_t I2Cstatus = 0;

	/* Reading the status from the I2C status register to drive the state machine */
	I2Cstatus = I2Cx->I2STAT;
	LPC_UART0->THR = I2Cstatus;

	switch(I2Cstatus)
	{

		case 0x08:
		/* A START condition has been transmitted. The Slave Address + R/W bit will now be transmitted. */

		/*1. Write Slave Address with R/W bit to I2DAT. */
		I2Cx->I2DAT = I2CMasterTxBuffer[0];
		/*2. Write 0x04 to I2CONSET to set the AA bit.  */
		I2Cx->I2CONSET = BIT_I2CONSET_AA;
		/*3. Write 0x08 to I2CONCLR to clear the SI and STA flag. */
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC | BIT_I2CONCLR_STAC;
		/*4. Set up Master Transmit mode data buffer. */
		/* DO NOTHING */
		/* 5. Set up Master Receive mode data buffer. */
		/* DO NOTHING */
		/*6. Initialize Master data counter. */
		I2CMasterWriteIndex = 1;
		I2CMasterReadIndex = 0;


		I2CMasterState= I2C_STARTED;
		break;

		case 0x10:
		/* A repeated START condition has been transmitted. The Slave Address + R/W bit will now be transmitted. */

		/* 1. Write Slave Address with R/W bit to I2DAT. */
		I2Cx->I2DAT = I2CMasterTxBuffer[I2CMasterWriteIndex];
		/*2. Write 0x04 to I2CONSET to set the AA bit.  */
		I2Cx->I2CONSET = BIT_I2CONSET_AA;
		/*3. Write 0x08 to I2CONCLR to clear the SI flag and STA flag.. */
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC | BIT_I2CONCLR_STAC;
		/* 4. Set up Master Transmit mode data buffer. */
		/* DO NOTHING */
		/* 5. Set up Master Receive mode data buffer. */
		/* DO NOTHING */
		/* 6. Initialize Master data counter. */
		I2CMasterReadIndex = 0;

		I2CMasterState= I2C_REPEATED_START;
		break;

		/*********************************I2C MASTER TRANSMIT MODE STATES*************************************/
		case 0x18:
		/*Previous state was State 0x08 or State 0x10, Slave Address + Write has been
		 transmitted, ACK has been received. The first data byte will be transmitted. */

		/*1. Load I2DAT with first data byte from Master Transmit buffer. */
		I2Cx->I2DAT = I2CMasterTxBuffer[I2CMasterWriteIndex];
		/*2. Write 0x04 to I2CONSET to set the AA bit. */
		I2Cx->I2CONSET = BIT_I2CONSET_AA;
		/*3. Write 0x08 to I2CONCLR to clear the SI flag. */
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
		/*4. Increment Master Transmit buffer pointer.*/
		I2CMasterWriteIndex++;

		I2CMasterState= DATA_ACK;
		break;

		case 0x20:
		/*Slave Address + Write has been transmitted, NOT ACK has been received. A STOP condition will be transmitted. */

		/* 1. Write 0x14 to I2CONSET to set the STO and AA bits. */
		I2Cx->I2CONSET = BIT_I2CONSET_STO | BIT_I2CONSET_AA;
		/* 2. Write 0x08 to I2CONCLR to clear the SI flag. */
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;

		I2CMasterState= DATA_NACK;

		break;

		case 0x28:
		/* Data has been transmitted, ACK has been received. If the transmitted data was the last
		 data byte then transmit a STOP condition, otherwise transmit the next data byte. */

		/*1. Decrement the Master data counter, skip to step 5 if not the last data byte.*/
		if (I2CMasterWriteIndex < I2CMasterWriteLength) {
			/*5. Load I2DAT with next data byte from Master Transmit buffer.*/
			I2Cx->I2DAT = I2CMasterTxBuffer[I2CMasterWriteIndex];
			/*6. Write 0x04 to I2CONSET to set the AA bit.*/
			I2Cx->I2CONSET = BIT_I2CONSET_AA;
			/*7. Write 0x08 to I2CONCLR to clear the SI flag. */
			I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
			/*8. Increment Master Transmit buffer pointer */
			I2CMasterWriteIndex++;

			I2CMasterState= DATA_ACK;
		} else {
			/* Sending the repeated start condition as we going ahead with a read operation */
			if (I2CMasterReadLength != 0)
				I2Cx->I2CONSET = BIT_I2CONSET_STA;
			else {
				/*2. Write 0x14 to I2CONSET to set the STO and AA bits.*/
				I2Cx->I2CONSET = BIT_I2CONSET_STO | BIT_I2CONSET_AA;

				I2CMasterState= DATA_NACK;
			}
			/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
					I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;

		}
		break;
		case 0x30:
		/* Data has been transmitted, NOT ACK received. A STOP condition will be transmitted */

		/*1. Write 0x14 to I2CONSET to set the STO and AA bits. */
		I2Cx->I2CONSET = BIT_I2CONSET_STO | BIT_I2CONSET_AA;
		/*2. Write 0x08 to I2CONCLR to clear the SI flag. */
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;

		I2CMasterState= DATA_NACK;
		break;

		case 0x38:
		/* Arbitration has been lost during Slave Address + Write or data. The bus has been
		 released and not addressed Slave mode is entered. A new START condition will be transmitted
		 when the bus is free again. */

		/*1. Write 0x24 to I2CONSET to set the STA and AA bits. */
		I2Cx->I2CONSET = BIT_I2CONSET_STA | BIT_I2CONSET_AA;
		/*2. Write 0x08 to I2CONCLR to clear the SI flag. */
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;

		I2CMasterState= DATA_NACK;
		break;

		/*********************************I2C MASTER RECEIVE MODE STATES**************************************/
		case 0x40:/*Previous state was State 08 or State 10. Slave Address + Read has been transmitted,
		 	 	  ACK has been received. Data will be received and ACK returned.*/

		/* Master is sending no acknowledge as it interested to read only one byte from slave */
		if (I2CMasterReadLength == 1)
			I2Cx->I2CONCLR = BIT_I2CONCLR_AAC;
		else
			/* Master is sending  acknowledge as it interested to read more bytes from slave */
			/*1. Write 0x04 to I2CONSET to set the AA bit. */
			I2Cx->I2CONSET = BIT_I2CONSET_AA;

		/*2. Write 0x08 to I2CONCLR to clear the SI flag. */
		    I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
		break;

		case 0x48:	/*Slave Address + Read has been transmitted, NOT ACK has been received. A STOP condition will be transmitted.*/

		/*1. Write 0x14 to I2CONSET to set the STO and AA bits. */
			I2Cx->I2CONSET = BIT_I2CONSET_STO | BIT_I2CONSET_AA;
		/*2. Write 0x08 to I2CONCLR to clear the SI flag. */
			I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;

			I2CMasterState = I2C_SLA_NACK;
		break;

		case 0x50:	/*Data has been received, ACK has been returned. Data will be read from I2DAT. Additional
		 	 	 data will be received. If this is the last data byte then NOT ACK will be returned, otherwise
		 	 	 ACK will be returned.*/

		/*1. Read data byte from I2DAT into Master Receive buffer. */
			I2CMasterRxBuffer[I2CMasterReadIndex]=I2Cx->I2DAT;

		/*2. Decrement the Master data counter, skip to step 5 if not the last data byte.*/
			I2CMasterReadIndex++;
			if(I2CMasterReadIndex<I2CMasterReadLength-1)
			{
				/*5. Write 0x04 to I2CONSET to set the AA bit.*/
							I2Cx->I2CONSET = BIT_I2CONSET_AA;
			/*6. Write 0x08 to I2CONCLR to clear the SI flag.*/
						I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
					/*7. Increment Master Receive buffer pointer*/
						I2CMasterState = DATA_ACK;
			}
			else
			{
		/*3. Write 0x0C to I2CONCLR to clear the SI flag and the AA bit.*/
			I2Cx->I2CONCLR = BIT_I2CONCLR_SIC | BIT_I2CONCLR_AAC;
						I2CMasterState = DATA_ACK;
			}

		break;

		case 0x58:
		/* Data has been received, NOT ACK has been returned. Data will be read from I2DAT. A STOP condition will be
		 transmitted. */
		/*1. Read data byte from I2DAT into Master Receive buffer. */
			I2CMasterRxBuffer[I2CMasterReadIndex]=I2Cx->I2DAT;
		/*2. Write 0x14 to I2CONSET to set the STO and AA bits. */
			I2Cx->I2CONSET = BIT_I2CONSET_STO | BIT_I2CONSET_AA;
		/*3. Write 0x08 to I2CONCLR to clear the SI flag. */
			I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;

			I2CMasterState = DATA_NACK;
		 break;

		 }
}

void vI2CSlaveStateMachine(LPC_I2C_TypeDef *I2Cx){

	uint8_t I2Cstatus = 0;
		I2Cstatus = I2Cx->I2STAT;
		LPC_UART0->THR = I2Cstatus;

		switch (I2Cstatus) {
		/*************************************************SLAVE RECEIVER MODE**************************************************************************/
		case 0x60: //SLA+W have been received
		case 0x68: //Arbitration lost in SLA+R/W as master; Own SLA+W has been received, ACK returned
		case 0x70: // General call address have been received
		case 0x78: //Arbitration lost in SLA+R/W as master; General Call address has been received, ACK has been returned.
			I2Cx->I2CONSET = BIT_I2CONSET_AA;
			I2CSlaveState = I2C_WR_STARTED;
			break;

		case 0x80: //Previously addressed with own SLA address; DATA has been  received; ACK has been returned.
		case 0x90: // Previously addressed with General Call; DATA byte has been received; ACK has been returned
			if (I2CSlaveState == I2C_WR_STARTED) {
				/* Receiving the data send from the master into the slave rx buffer */
				I2CSlaveRxBuffer[I2CSlaveReadIndex++] = I2Cx->I2DAT;
				/* Providing acknowledgment for master for receiving further data */
				I2Cx->I2CONSET = BIT_I2CONSET_AA;
			} else
				/* Providing no acknowledgment for master for receiving no further data */
				I2Cx->I2CONCLR = BIT_I2CONCLR_AAC;
			break;

		case 0xA0:
			I2Cx->I2CONSET = BIT_I2CONSET_AA;
			I2CSlaveState = I2C_IDLE;
			break;
			/*************************************************SLAVE TRANSMITER MODE***********************************************************************/

		case 0xA8: //Own SLA+R has been received; ACK has been returned.
		case 0xB0: //Arbitration lost in SLA+R/W as master; 	Own SLA+R has been received, ACK has 	been returned.
			       	I2CSlaveWriteIndex =0;
					I2Cx->I2DAT = I2CSlaveTxBuffer[I2CSlaveWriteIndex]; /* write the same data back to master */
					I2CSlaveWriteIndex++;
					I2Cx->I2CONSET = BIT_I2CONSET_AA; /* assert ACK after SLV_R is received */
					I2CSlaveState = I2C_RD_STARTED;
		case 0xC8://Last data byte in I2DAT has been transmitted (AA = 0); ACK has been received.
		case 0xB8:
			if (I2CSlaveState == I2C_RD_STARTED) {
				I2Cx->I2DAT = I2CSlaveTxBuffer[I2CSlaveWriteIndex++];
				I2Cx->I2CONSET = BIT_I2CONSET_AA;
			}
			else
				/* Providing no acknowledgement for master for transmitting no further data */
				I2Cx->I2CONCLR = BIT_I2CONCLR_AAC;
		case 0xC0:
			I2Cx->I2CONCLR = BIT_I2CONCLR_AAC;
			I2CSlaveState = DATA_NACK;
		break;

		}

		/* Clearing the I2C interrupt for reenabling the I2C interrrupts again*/
		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
}



/* Call back function when selected  I2C acts as Slave*/
//void vI2CSlaveStateMachine(LPC_I2C_TypeDef *I2Cx){
//
//	volatile uint8_t I2Cstatus = 0;
//
//	/* Reading the status from the I2C status register to drive the state machine */
//	I2Cstatus = I2Cx->I2STAT;
//	LPC_UART0->THR = I2Cstatus;
//
//	switch (I2Cstatus) {
//
//	/*********************************I2C SLAVE RECEIVER MODE STATES*************************************/
//	case 0x60:/* Own Slave Address + Write has been received, ACK has been returned. Data will be received and ACK returned.*/
//
//		/* 1. Write 0x04 to I2CONSET to set the AA bit.*/
//			I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/* 2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//			I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		/* 3. Set up Slave Receive mode data buffer.*/
//			/* DO NOTHING already done in the declaration */
//		/* 4. Initialize Slave data counter. */
//			I2CSlaveReadIndex=0;
//			I2CSlaveState = I2C_RD_STARTED;
//		break;
//
//	case 0x68:/* Arbitration lost in Slave Address and R/W bit as bus Master. Own Slave Address + Read
//		 	 has been received, ACK has been returned. Data will be transmitted, ACK bit will be
//		 	 received. STA is set to restart Master mode after the bus is free again. */
//
//		/*1. Load I2DAT from Slave Transmit buffer with first data byte.*/
//		  I2Cx->I2DAT=I2CSlaveTxBuffer[I2CSlaveWriteIndex];
//		/*2. Write 0x24 to I2CONSET to set the STA and AA bits.*/
//		  I2Cx->I2CONSET = BIT_I2CONSET_STA |BIT_I2CONSET_AA;
//		/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		  I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		/*4. Set up Slave Transmit mode data buffer.*/
//		  /* DO NOTHING already done in the declaration */
//		/*5. Increment Slave Transmit buffer pointer. */
//		  I2CSlaveWriteIndex++;
//		break;
//
//	case 0x70: /* General Call has been received, ACK has been returned. Data will be received and ACK returned */
//		/*1. Write 0x04 to I2CONSET to set the AA bit.*/
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		  I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		/*3. Set up Slave Receive mode data buffer.*/
//		/*4. Initialize Slave data counter.*/
//		break;
//
//	case 0x78:/*Arbitration has been lost in Slave Address + R/W bit as bus Master. General Call has
//			  been received and ACK has been returned. Data will be received and ACK returned. STA
//			  is set to restart Master mode after the bus is free again. */
//
//		/*1. Write 0x24 to I2CONSET to set the STA and AA bits. */
//		  I2Cx->I2CONSET = BIT_I2CONSET_STA |BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		  I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		/*3. Set up Slave Receive mode data buffer.*/
//		/*4. Initialize Slave data counter.*/
//		break;
//
//	case 0x80:/*Previously addressed with own Slave Address. Data has been received and ACK has been returned.
//			    Additional data will be read. */
//
//		/*1. Read data byte from I2DAT into the Slave Receive buffer.*/
//		/*2. Decrement the Slave data counter, skip to step 5 if not the last data byte. */
//		/*3. Write 0x0C to I2CONCLR to clear the SI flag and the AA bit.*/
//		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC | BIT_I2CONCLR_AAC;
//		/*4. Exit. */
//		/*5. Write 0x04 to I2CONSET to set the AA bit. */
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*6. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		  I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		/*7. Increment Slave Receive buffer pointer.*/
//		break;
//
//	case 0x88:/* Previously addressed with own Slave Address. Data has been received and NOT ACK
//			 has been returned. Received data will not be saved. Not addressed Slave mode is entered. */
//
//		/*1. Write 0x04 to I2CONSET to set the AA bit. */
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		  I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		break;
//
//	case 0x90:/* Previously addressed with General Call. Data has been received, ACK has been returned.
//	 	 	 Received data will be saved. Only the first data byte will be received with ACK. Additional
//	 	 	 data will be received with NOT ACK. */
//
//		/*1. Read data byte from I2DAT into the Slave Receive buffer. */
//		/*2. Write 0x0C to I2CONCLR to clear the SI flag and the AA bit.*/
//		I2Cx->I2CONCLR = BIT_I2CONCLR_SIC | BIT_I2CONCLR_AAC;
//			break;
//
//	case 0x98:/*Previously addressed with General Call. Data has been received, NOT ACK has been
//	 	 	 returned. Received data will not be saved. Not addressed Slave mode is entered. */
//
//		/*1. Write 0x04 to I2CONSET to set the AA bit. */
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag. */
//		  I2Cx->I2CONCLR = BIT_I2CONCLR_SIC;
//		break;
//
//	case 0xA0:/*A STOP condition or repeated START has been received, while still addressed as a Slave.
//	 	 	 Data will not be saved. Not addressed Slave mode is entered. */
//
//		/*1. Write 0x04 to I2CONSET to set the AA bit. */
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		I2Cx->I2CONCLR =BIT_I2CONCLR_SIC;
//
//		break;
//		/*********************************I2C SLAVE TRANSMIT MODE STATES*************************************/
//
//	case 0xA8:/*Own Slave Address + Read has been received, ACK has been returned. Data will be
//			 transmitted, ACK bit will be received. */
//		/*1. Load I2DAT from Slave Transmit buffer with first data byte.*/
//		/*2. Write 0x04 to I2CONSET to set the AA bit.*/
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		I2Cx->I2CONCLR =BIT_I2CONCLR_SIC;
//		/*4. Set up Slave Transmit mode data buffer.*/
//		/*5. Increment Slave Transmit buffer pointer.*/
//		break;
//
//	case 0xB0:/*Arbitration lost in Slave Address and R/W bit as bus Master. Own Slave Address + Read
//			  has been received, ACK has been returned. Data will be transmitted, ACK bit will be received.
//			  STA is set to restart Master mode after the bus is free again.*/
//
//		/*1. Load I2DAT from Slave Transmit buffer with first data byte.*/
//		/*2. Write 0x24 to I2CONSET to set the STA and AA bits.*/
//		  I2Cx->I2CONSET = BIT_I2CONSET_STA |BIT_I2CONSET_AA;
//		/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		I2Cx->I2CONCLR =BIT_I2CONCLR_SIC;
//		/*4. Set up Slave Transmit mode data buffer.*/
//		/*5. Increment Slave Transmit buffer pointer.*/
//		break;
//
//	case 0xB8:/*Data has been transmitted, ACK has been received. Data will be transmitted, ACK bit will be received. */
//
//		/*1. Load I2DAT from Slave Transmit buffer with data byte.*/
//		/*2. Write 0x04 to I2CONSET to set the AA bit.*/
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*3. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		I2Cx->I2CONCLR =BIT_I2CONCLR_SIC;
//		/*4. Increment Slave Transmit buffer pointer.*/
//		break;
//
//	case 0xC0: /*Data has been transmitted, NOT ACK has been received. Not addressed Slave mode is entered */
//
//		/*1. Write 0x04 to I2CONSET to set the AA bit. */
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		I2Cx->I2CONCLR =BIT_I2CONCLR_SIC;
//		break;
//
//	case 0xC8:/* The last data byte has been transmitted, ACK has been received. Not addressed Slave mode is entered. */
//
//		/*1. Write 0x04 to I2CONSET to set the AA bit. */
//		I2Cx->I2CONSET = BIT_I2CONSET_AA;
//		/*2. Write 0x08 to I2CONCLR to clear the SI flag.*/
//		I2Cx->I2CONCLR =BIT_I2CONCLR_SIC;
//		break;
//
//	}
//}
//



void I2C0_IRQHandler(void)
{
	vI2CMasterStateMachine(I2C0);
}
void I2C1_IRQHandler(void)
{
	/* DO NOTHING */
}
void I2C2_IRQHandler(void)
{
	vI2CSlaveStateMachine(I2C2);
}








