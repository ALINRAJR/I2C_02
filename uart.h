/*
 * uart.h
 *

 */


#ifndef UART_H_
#define UART_H_
#include <LPC17xx.h>
#include "pinmux.h"
#include "queue.h"

#define BIT_PCUART0 3
#define BIT_PCUART1 4
#define BIT_PCUART2 24
#define BIT_PCUART3 25

#define BIT_PCLK_UART0  6
#define BIT_PCLK_UART1  8
#define BIT_PCLK_UART2  16
#define BIT_PCLK_UART3  18

enum {UART_0,UART_1,UART_2,UART_3};
enum {RBR_INTERRUPT_ENABLE=0,THRE_INTERRUPT_ENABLE,RX_LINE_STATUS_INTERRUPT_ENABLE,ABEOINTEN,ABTOINTEN};
enum {ONE_CHARACTER=0,FOUR_CHARACTERS,EIGHT_CHARACTERS,FOURTEEN_CHARACTERS};
enum {THRE_INT=1,RDA_INT=2};


#define UART0 LPC_UART0
#define UART1 LPC_UART1
#define UART2 LPC_UART2
#define UART3 LPC_UART3

#define MAXUARTRECEIVETIMEOUT 100000

#define BAUD_115200                     0
#define DLL_BAUD115200_25MHZ   		    10
#define DLM_BAUD115200_25MHZ   			0
#define DIVADDVAL_BAUD115200_25MHZ      5
#define MULVAL_BAUD115200_25MHZ         14

/*UARTn Receiver Buffer Register*/
#define BIT_RBR                                      0    //(U0RBR-0x4000 C000,U2RBR-0x4009 8000,U3RBR-04009 C000 when DLAB=0)
/*UARTn Transmit Holding Register*/
#define BIT_THR                                      0                               //(U0THR-0x4000 C000,U2THR -0x4009 8000,U3THR-0x4009 C000 when DLAB=0)
/*UARTn Divisor Latch LSB register*/
#define BIT_DLLSB                                    0                              //(U0DLL-0x4000 C000,U2DLL -0x4009 8000,U3DLL-0x4009 C000 when DLAB=1)
#define BIT_DLMSB                                    0                             //(U0DLM-0x4000 C000,U2DLM -0x4009 8000,U3DLM-0x4009 C000 when DLAB=1)
/*UARTn Interrupt Enable Register*/
#define BIT_RBR_INTERRUPT_ENABLE                     0                            //(U0IER-0x4000 C004,U2IER-0x4009 8004,U3IER-0x4009 C004 when DLAB =0)
#define BIT_THRE_INTERRUPT_ENABLE                    1
#define BIT_RX_LINE_STATUS_INTERRUPT_ENABLE          2
#define BIT_MODERN_SSTATUSIE_UART1                   3
#define BIT_CTSIE_UART1                              4
#define BIT_ABEOINTEN                                8
#define BIT_ABTOINTEN                                9                          //(U0IER- 0x4000 C004,U2IER - 0x4009 8004,U3IER - 0x4009 C004 when DLAB =0)
/*UARTn Interrupt Identification Register*/
#define BIT_INTSTATUS                                0                         //(U0IIR- 0x4000 C008,U2I1R - 0x4009 8008,U3IIR - 0x4009 C008 )
#define BIT_INTLD                                    1
#define BIT_IIR_FIFO_ENABLE                          6
#define BIT_ABEOINT                                  8
#define BIT_ABTOINT                                  9
/*UARTn FIFO Control Register*/
#define BIT_FCR_FIFO_ENABLE                          0                         //(U0FCR - 0x4000 C008,U2FCR-0x4009 8008,U3FCR - 0x4009 C008)
#define BIT_RX_FIFO_RESET                            1
#define BIT_TX_FIFO_RESET                            2
#define BIT_DMA_MODE_SELECT                          3
#define BIT_RX_TRIGGER_LEVEL                         6
/*UARTn Line Control Register */
#define BIT_WORD_LENGTH_SELECT                       0                       //(U0LCR-0x4000 C00C,U2LCR - 0x4009 800C,U3LCR-0x4009 C00C)
#define  BIT_STOP_BIT_SELECT                         2
#define BIT_PARITY_ENABLE                            3
#define BIT_PARITY_SELECT                            4
#define BIT_BREAK_CONTROL                            6
#define BIT_DLAB                                     7
/*UARTn Line Status Register*/
#define BIT_RECEIVER_DATA_READY                      0                      //(U0LSR-0x4000 C014,U2LSR-0x4009 8014,U3LSR-0x4009 C014)
#define BIT_OVERRUN_ERROR                            1
#define BIT_PARITY_ERROR                             2
#define BIT_FRAMING_ERROR                            3
#define BIT_BREAK_INTERRUPT                          4
#define BIT_THRE                                     5
#define BIT_TRANSMITTER_EMPTY                        6
#define BIT_RXFE                                     7
/*UARTn Scratch Pad Register*/
#define BIT_PAD                                      0                      //(U0SCR-0x4000 C01C,U2SCR-0x4009 801C,U3SCR-0x4009 C01C)
/*UARTn Auto-baud Control Register*/
#define BIT_START                                    0                     //(U0ACR-0x4000 C020,U2ACR-0x4009 8020,U3ACR-0x4009 C020)
#define BIT_MODE                                     1
#define BIT_AUTORESTART                              2
#define BIT_ABEOINTCLR                               8
#define BIT_ABTOINTCLR                               9
/*UARTn IrDA Control Register*/
#define BIT_IRDAEN                                   0                     //(U0ICR-0x4000 C024,U2ICR-0x4009 8024,U3ICR-0x4009 C024)
#define BIT_IRDAINV                                  1
#define BIT_FIXPULSEEN                               2
#define BIT_PULSEDIV                                 3
/*UARTn Fractional Divider Register*/
#define BIT_DIVADDVAL                                0                     //(U0FDR-0x4000 C028,U2FDR-0x4009 8028,U3FDR-0x4009 C028)
#define BIT_MULVAL                                   4
/*UARTn Transmit Enable Register*/
#define BIT_TXEN                                     7                    //(U0TER-0x4000 C030,U2TER-0x4009 8030,U3TER-0x4009 C030)
/*UART1 Modem Control Register*/
#define BIT_DTR_CONTROL_UART1                        0                   //(U1MCR-0x4001 0010)
#define BIT_RTS_CONTROL_UART1                        1
#define BIT_LOOPBACK_MODE_SELECT_UART1               4
#define BIT_RTSEN_UART1                              6
#define BIT_CTSEN_UART1                              7
/*UART1 Modem Status Register*/
#define BIT_DELTA_CTS_UART1                          0                  //(U1MSR-0x4001 0018)
#define BIT_DELTA_DSR_UART1                          1
#define BIT_TRAILING_EDGE_RI_UART1                   2
#define BIT_DELTA_DCD_UART1                          3
#define BIT_CTS_UART1                                4
#define BIT_DSR_UART1                                5
#define BIT_RI_UART                                  6
#define BIT_DCD_UART1                                7
/*UART1 RS485 Control register*/
#define BIT_NMMEN_UART1                               0                //(U1RS485CTRL-0x4001 004C)
#define BIT_RXDIS_UART1                               1
#define BIT_AADEN_UART1                               2
#define BIT_SEL_UART1                                 3
#define BIT_DCTRL_UART1                               4
#define BIT_OINV_UART1                                5
/*UART1 RS-485 Address Match register*/
#define BIT_ADRMATCH_UART1                            0                 //(U1RS485ADRMATCH - 0x4001 0050)
/*UART1 RS-485 Delay value register*/
#define BIT_DLY_UART1                                 0                 //(U1RS485DLY - 0x4001 0054)







/* Blocking Function for UART transmitting a byte */
void vUARTWriteChar(LPC_UART0_TypeDef* UARTx,uint8_t data);
/* Blocking Function for UART receving a byte */
void vUARTReadChar(LPC_UART0_TypeDef* UARTx,uint8_t* ptrdata, uint32_t timeout);
/* Function for UART initialization with basic configuration*/
void vUARTInitialize();
/* Function for enabling the UART interrupt for selected UART interrupt source */
void vUARTInterruptEnable(LPC_UART0_TypeDef* UARTx,uint8_t interruptsource);
/* Function for disabling the UART interrupt for selected UART interrupt source */
void vUARTInterruptDisable(LPC_UART0_TypeDef* UARTx,uint8_t interruptsource);
/* Function for attaching user defined functions for the selected UART */
void vUARTCallback(uint8_t uartnum, funcptr funcptrobj);
/* Function for converting the number to string based on the base */
char* pcConvertNumtoString(uint32_t number, uint8_t base);
/* Function for displaying the string in the selected UART */
void vUARTPutstring(LPC_UART0_TypeDef* UARTx,char *string);
/* Printf function for displaying in UART */
void vUARTPrintf(LPC_UART0_TypeDef* UARTx,char *format, ...);
/* Function to write into software queue available for the UART */
uint8_t ucUARTSend(LPC_UART0_TypeDef* UARTx,uint8_t* ptrbuffer, uint32_t numofbytes);

#endif /* UART_H_ */
