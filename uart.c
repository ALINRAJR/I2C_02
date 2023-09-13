/*
 * uart.c
 *

 */


#include "uart.h"
#include <stdarg.h>

#define NULL ((void*)0)

#define MAXTXBUFFERSIZE   64
#define MAXRXBUFFERSIZE   128

#define MAXFIFOSIZE 16

Queue_t TxQueue,RxQueue;
uint8_t TxBuffer[MAXTXBUFFERSIZE];
uint8_t RxBuffer[MAXRXBUFFERSIZE];

/* Call back function objects for the respective UARTs initialized to NULL to avoid dangling pointers*/
funcptr vUART0isr=NULL;
funcptr vUART1isr=NULL;
funcptr vUART2isr=NULL;
funcptr vUART3isr=NULL;

/* UART interrupt trigger state variable */
uint8_t UARTTxIntTriggerState=DISABLE;

volatile uint8_t receivedbyte=0;

void vUART0Callback(void)
{
	volatile uint8_t readbyte=0;
	volatile uint8_t fifocount=MAXFIFOSIZE;
	volatile uint32_t UART0IntIdentifcationReg=0;
	volatile uint32_t UART0Intsrc=0;


	UART0IntIdentifcationReg=LPC_UART0->IIR;
	UART0Intsrc=UART0IntIdentifcationReg>>1 & 0x07;
	switch(UART0Intsrc)
	{
	case THRE_INT:
		/* Checking the no of available locations in the FIFO and reading available bytes from the software queue */
		while (fifocount && (ucQueueRead(&TxQueue, &readbyte))) {
			LPC_UART0->THR = readbyte;
			fifocount--;
		}
		/* If software queue is empty after the read operation,
		   it means no further data to be written into the hardware FIFO */
		if(ucQueueIsEmpty(&TxQueue))
		{
			UARTTxIntTriggerState=DISABLE;
			vUARTInterruptDisable(LPC_UART0,THRE_INTERRUPT_ENABLE);
		}
		else
		{
			UARTTxIntTriggerState=ENABLE;
			vUARTInterruptEnable(LPC_UART0,THRE_INTERRUPT_ENABLE);
		}
		break;
	case RDA_INT:
		receivedbyte=LPC_UART0->RBR;
		break;
	}
}



/* Function for enabling and disabling the power to the selected UART Peripheral*/
void vUARTPowerControl(uint8_t uartnum,uint8_t mode)
{
	switch(uartnum)
	{
	case UART_0:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCUART0;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCUART0);
		break;
	case UART_1:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCUART1;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCUART1);
		break;
	case UART_2:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCUART2;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCUART2);
		break;
	case UART_3:
		if(mode==POWERON)
			LPC_SC->PCONP |= 1<<BIT_PCUART3;
		else if (mode == POWEROFF)
			LPC_SC->PCONP &= ~(1<<BIT_PCUART3);
		break;
	}
}

/* Function for selecting the clock for the selected UART Peripheral*/
void vUARTClockSel(uint8_t uartnum,uint8_t clocksel)
{
	switch(uartnum)
	{
	case UART_0:
	LPC_SC->PCLKSEL0 &= ~(3<<BIT_PCLK_UART0);
	LPC_SC->PCLKSEL0 |= clocksel<<BIT_PCLK_UART0;
	break;
	case UART_1:
	LPC_SC->PCLKSEL0 &= ~(3<<BIT_PCLK_UART1);
	LPC_SC->PCLKSEL0 |= clocksel<<BIT_PCLK_UART1;
	break;
	case UART_2:
	LPC_SC->PCLKSEL1 &= ~(3<<BIT_PCLK_UART2);
	LPC_SC->PCLKSEL1 |= clocksel<<BIT_PCLK_UART2;
	break;
	case UART_3:
	LPC_SC->PCLKSEL1 &= ~(3<<BIT_PCLK_UART3);
	LPC_SC->PCLKSEL1 |= clocksel<<BIT_PCLK_UART3;
	break;
	}
}

/*Function for setting the baudrate for the selected UART Peripheral  */
void vUARTBaudrateSetup(LPC_UART0_TypeDef* UARTx,uint8_t baudrate)
{
	  /* Enabling the DLAB bit for updating DLL,DLM and FDR Registers and selecting word length as 8 bit */
      UARTx->LCR = 3<<BIT_WORD_LENGTH_SELECT | 1<<BIT_DLAB;
      switch(baudrate)
      {
      case BAUD_115200:
      UARTx->DLL = DLL_BAUD115200_25MHZ;
      UARTx->DLM = DLM_BAUD115200_25MHZ;
      UARTx->FDR = DIVADDVAL_BAUD115200_25MHZ<<BIT_DIVADDVAL | MULVAL_BAUD115200_25MHZ<<BIT_MULVAL;
      /* Disabling the DLAB bit after updating DLL,DLM and FDR Registers */
      UARTx->LCR &= ~(1<<BIT_DLAB);
      break;
      }
}

/* Blocking Function for UART transmitting a byte */
void vUARTWriteChar(LPC_UART0_TypeDef* UARTx,uint8_t data)
{
   /* Waiting until UART Transmit hold register is empty */
	while(!(UARTx->LSR & 1<<BIT_THRE));

	/*If UART Transmit hold register is empty we are placing the data */
	UARTx->THR = data;
}

/* Blocking Function for UART receving a byte */
void vUARTReadChar(LPC_UART0_TypeDef* UARTx,uint8_t* ptrdata, uint32_t timeout)
{
	/* Waiting until UART Receives a byte or until timeout occurs */
	while(!(UARTx->LSR & 1<<BIT_RECEIVER_DATA_READY) && timeout--);
	if(timeout<=0)
	*ptrdata= NULL;
	else
	/*If UART receives a byte it is placed into the RAM buffer that we are passing */
	*ptrdata = UARTx->RBR;
}

/* Function for enabling the UART interrupt for selected UART interrupt source */
void vUARTInterruptEnable(LPC_UART0_TypeDef* UARTx,uint8_t interruptsource)
{
	switch (interruptsource) {
	case RBR_INTERRUPT_ENABLE:
		UARTx->IER |= 1<<BIT_RBR_INTERRUPT_ENABLE;
		break;
	case THRE_INTERRUPT_ENABLE:
		UARTx->IER |= 1<<BIT_THRE_INTERRUPT_ENABLE;
		break;
	case RX_LINE_STATUS_INTERRUPT_ENABLE:
		UARTx->IER |= 1<<BIT_RX_LINE_STATUS_INTERRUPT_ENABLE;
		break;
	case ABEOINTEN:
		UARTx->IER |= 1<<BIT_ABEOINTEN;
		break;
	case ABTOINTEN:
		UARTx->IER |= 1<<BIT_ABTOINTEN;
		break;
	}
}

/* Function for disabling the UART interrupt for selected UART interrupt source */
void vUARTInterruptDisable(LPC_UART0_TypeDef* UARTx,uint8_t interruptsource)
{
		switch (interruptsource) {
		case RBR_INTERRUPT_ENABLE:
			UARTx->IER &=~(1<<BIT_RBR_INTERRUPT_ENABLE);
			break;
		case THRE_INTERRUPT_ENABLE:
			UARTx->IER &=~(1<<BIT_THRE_INTERRUPT_ENABLE);
			break;
		case RX_LINE_STATUS_INTERRUPT_ENABLE:
			UARTx->IER &=~(1<<BIT_RX_LINE_STATUS_INTERRUPT_ENABLE);
			break;
		case ABEOINTEN:
			UARTx->IER &=~(1<<BIT_ABEOINTEN);
			break;
		case ABTOINTEN:
			UARTx->IER &=~(1<<BIT_ABTOINTEN);
			break;
		}
}

/*Function for enabling the FIFO for selected UART*/
void vUARTFIFOEnable(LPC_UART0_TypeDef* UARTx,uint8_t mode)
{
	if(mode==ENABLE)
    UARTx->FCR |= 1<<BIT_FCR_FIFO_ENABLE;
	else
	UARTx->FCR &= ~(1<<BIT_FCR_FIFO_ENABLE);
}

/*Function for reseting the UART Transmitter FIFO for selected UART*/
void vUARTTxFIFOReset(LPC_UART0_TypeDef* UARTx)
{
	 UARTx->FCR = 1<<BIT_TX_FIFO_RESET;

}
/*Function for reseting the UART Receiver FIFO for selected UART*/
void vUARTRxFIFOReset(LPC_UART0_TypeDef* UARTx)
{
	 UARTx->FCR = 1<<BIT_RX_FIFO_RESET;

}
/*Function for setting the trigger levels for generating UART receive interrupts for selected UART*/
void vUARTRxTriggerLevel(LPC_UART0_TypeDef* UARTx, uint8_t triggerlevel)
{
	 UARTx->FCR = triggerlevel<<BIT_RX_TRIGGER_LEVEL;

}

/* Function for attaching user defined functions for the selected UART */
void vUARTCallback(uint8_t uartnum, funcptr funcptrobj)
{
	switch (uartnum) {
		case UART_0:
			vUART0isr = funcptrobj;
			break;
		case UART_1:
			vUART1isr = funcptrobj;
			break;
		case UART_2:
			vUART2isr = funcptrobj;
			break;
		case UART_3:
			vUART3isr = funcptrobj;
			break;
		}
}
/* Function for UART initialization with basic configuration and interrupt */
void vUARTInitialize(void)
{
	vUARTPowerControl(UART_0,POWERON);
	vUARTClockSel(UART_0,ONEFOURTH);
	vUARTBaudrateSetup(UART0,BAUD_115200);

	vUARTTxFIFOReset(LPC_UART0);
	vUARTRxFIFOReset(LPC_UART0);
	/* Trigger UART receive interrupt for every character */
	vUARTRxTriggerLevel(LPC_UART0,ONE_CHARACTER);

	vUARTFIFOEnable(LPC_UART0,ENABLE);

	vQueueInitialize(&TxQueue,TxBuffer,MAXTXBUFFERSIZE);
	vQueueInitialize(&RxQueue,RxBuffer,MAXRXBUFFERSIZE);

}

/* Function for converting the number to string based on the base */
char* pcConvertNumtoString(uint32_t number, uint8_t base) {

	const uint8_t representation[] = "0123456789ABCDEF";
		static char numarray[20];
		char *ptrnumarray = &numarray[19];

		*ptrnumarray = '\0';
		if (number == 0)
			*--ptrnumarray = '0';
		while (number > 0) {
			*--ptrnumarray = representation[number % base];
			number = number / base;
		}
		return ptrnumarray;



}

/* Function for displaying the string in the selected UART */
void vUARTPutstring(LPC_UART0_TypeDef* UARTx,char *string) {

	while(*string !='\0')
	{
		vUARTWriteChar(UARTx,*string++);
	}

}


/* Printf function for displaying in UART */
void vUARTPrintf(LPC_UART0_TypeDef* UARTx,char *format, ...) {
	char ch;
		int num;
		char *string;
		va_list obj;

		va_start(obj, *format);
		while (*format != '\0') {

			if (*format != '%') {
				vUARTWriteChar(UARTx, *format);
			}

			else if (*format == '%') {
				format++;

				switch (*format) {

				case 'b':
					num = va_arg(obj, int);
					vUARTPutstring(UARTx, pcConvertNumtoString(num, 2));
				case 'c':
					ch = va_arg(obj, int);
					vUARTWriteChar(UARTx, ch);
					break;
				case 'd':
					num = va_arg(obj, int);
					if (num < 0)
						vUARTWriteChar(UARTx, '-');
					vUARTPutstring(UARTx, pcConvertNumtoString(num, 10));
					break;
				case 'o':
					num = va_arg(obj, int);
					vUARTPutstring(UARTx, pcConvertNumtoString(num, 8));
					break;
				case 's':
					string = va_arg(obj, char*);
					vUARTPutstring(UARTx, string);
					break;
				case 'x':
					num = va_arg(obj, int);
					vUARTPutstring(UARTx, pcConvertNumtoString(num, 16));
					break;
				}
			}

			format++;
		}

		va_end(obj);

	}




void UART0_IRQHandler(void) {
	/*function pointer calling the registered call back function using vUARTCallback */
	vUART0isr();
}

void UART1_IRQHandler(void) {
	/*function pointer calling the registered call back function using vUARTCallback */
	vUART1isr();
}
void UART2_IRQHandler(void) {
	/*function pointer calling the registered call back function using vUARTCallback */
	vUART2isr();
}

void UART3_IRQHandler(void) {
	/*function pointer calling the registered call back function using vExtIntCallback */
	vUART3isr();
}

/* Non Blocking Function for UART transmitting a byte */
uint8_t ucUARTWriteBytestoFIFO(LPC_UART0_TypeDef* UARTx,uint8_t* ptrbuffer, uint32_t numofbytes)
{
	uint8_t fifocount=MAXFIFOSIZE;
	uint8_t numofbytessent=0;
	while(numofbytes)
	{
		 if(!(UARTx->LSR & 1<<BIT_THRE))
			 break;
		 while(numofbytes && fifocount)
		 {
			 UARTx->THR = *ptrbuffer++;
			 numofbytes--;
			 fifocount--;
			 numofbytessent++;
		 }
	}
	return numofbytessent;
}


/* Function to write into software queue available for the UART */
uint8_t ucUARTSend(LPC_UART0_TypeDef* UARTx,uint8_t* ptrbuffer, uint32_t numofbytes)
{
	uint8_t numofbytessent=0;
	uint8_t readbyte=0;
	while(numofbytes)
	{
		/* Writing the bytes of data into the software buffer until number of bytes becomes zero
		 * or until software buffer is full*/
		if(!ucQueueWrite(&TxQueue,*ptrbuffer))
		break;
		numofbytessent++;
		ptrbuffer++;
		numofbytes--;
	}
	/* Triggering the transmit interrupt by reading a byte from the software buffer and writing into HW FIFO*/
	if(UARTTxIntTriggerState==DISABLE)
	{
		/*reading a byte from the software buffer */
		if(ucQueueRead(&TxQueue,&readbyte))
			/* and writing into HW FIFO */
			ucUARTWriteBytestoFIFO(UARTx,&readbyte,1);
		UARTTxIntTriggerState= ENABLE;
		vUARTInterruptEnable(LPC_UART0,THRE_INTERRUPT_ENABLE);
	}

 return numofbytessent;
}



