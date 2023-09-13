/*
 * pinmux.c
 *

 */

#include "pinmux.h"
#include <LPC17xx.h>


/*const Pinconfig_t Pinsconfig[]={

		{ LPC_GPIO0, P0_0, FUNC0 },      //CAN_RD_1 ,
		{ LPC_GPIO0, RD1, FUNC1 },       //CAN_RD_1
		{ LPC_GPIO0, TXD3, FUNC2 },      //CAN_RD_1
		{ LPC_GPIO0, SDA1, FUNC3 },      //CAN_RD_1
		{ LPC_GPIO0, P0_1, FUNC0 },      //CAN_TD_1
		{ LPC_GPIO0, TD1, FUNC1 },       //CAN_TD_1
		{ LPC_GPIO0, RXD3, FUNC2 },      //CAN_TD_1
		{ LPC_GPIO0, SCL1, FUNC3 },      //CAN_TD_1
		{ LPC_GPIO0, P0_2, FUNC0 },      //UART_TX_0
		{ LPC_GPIO0, TXD0, FUNC1 },      //UART_TX_0
		{ LPC_GPIO0, AD0_7, FUNC2 },     //UART_TX_0
		{ LPC_GPIO0, P0_3, FUNC0 },      //UART_RX_0
		{ LPC_GPIO0, RXD0, FUNC1 },      //UART_RX_0
		{ LPC_GPIO0, AD0_6, FUNC2 },     //UART_RX_0
		{ LPC_GPIO0, P0_4, FUNC0 },      //P0_4
		{ LPC_GPIO0, I2SRX_CLK, FUNC1 }, //P0_4
		{ LPC_GPIO0, RD2, FUNC2 },       //P0_4
		{ LPC_GPIO0, CAP2_0, FUNC3 },    //P0_4
		{ LPC_GPIO0, P0_5, FUNC0 },      //P0_5
		{ LPC_GPIO0, I2SRX_WS, FUNC1 },  //P0_5
		{ LPC_GPIO0, TD2, FUNC2 },       //P0_5
		{ LPC_GPIO0, CAP2_1, FUNC3 },    //P0_5
		{ LPC_GPIO0, P0_6, FUNC0 },      //P0_6
		{ LPC_GPIO0, I2SRX_SDA, FUNC1 }, //P0_6
		{ LPC_GPIO0, SSEL, FUNC2 },      //P0_6
		{ LPC_GPIO0, MAT2_0, FUNC3 },    //P0_6
		{ LPC_GPIO0, P0_7, FUNC0 },      //P0_7
		{ LPC_GPIO0, I2STX_CLK, FUNC1 }, //P0_7
		{ LPC_GPIO0, SCK1, FUNC2 },      //P0_7
		{ LPC_GPIO0, MAT2_1, FUNC3 },    //P0_7
		{ LPC_GPIO0, P0_8, FUNC0 },      //P0_8
		{ LPC_GPIO0, I2STX_WS, FUNC1 },  //P0_8
		{ LPC_GPIO0, MISO1, FUNC2 },     //P0_8
		{ LPC_GPIO0, MAT2_2, FUNC3 },    //P0_8
		{ LPC_GPIO0, P0_9, FUNC0 },      //P0_9
		{ LPC_GPIO0, I2STX_SDA, FUNC1 }, //P0_9
		{ LPC_GPIO0, MOSI1, FUNC2 },     //P0_9
		{ LPC_GPIO0, MAT2_3, FUNC3 },    //P0_9
		{ LPC_GPIO0, P0_10, FUNC0 },     //P0_10
		{ LPC_GPIO0, TXD2, FUNC1 },      //P0_10
		{ LPC_GPIO0, SDA2, FUNC2 },      //P0_10
		{ LPC_GPIO0, MAT3_0, FUNC3 },    //P0_10
		{ LPC_GPIO0, P0_11, FUNC0 },     //P0_11
		{ LPC_GPIO0, RXD2, FUNC1 },      //P0_11
		{ LPC_GPIO0, SCL2, FUNC2 },      //P0_11
		{ LPC_GPIO0, MAT3_1, FUNC3 },    //P0_11
		{ LPC_GPIO0, P0_15, FUNC0 },     //SPI_SCK_0
		{ LPC_GPIO0, TXD1, FUNC1 },      //SPI_SCK_0
		{ LPC_GPIO0, SCK0, FUNC2 },      //SPI_SCK_0
		{ LPC_GPIO0, SCK, FUNC3 },       //SPI_SCK_0
		{ LPC_GPIO0, P0_16, FUNC0 },     //SPI_SSEL_0
		{ LPC_GPIO0, RXD1, FUNC1 },      //SPI_SSEL_0
		{ LPC_GPIO0, SSELO, FUNC2 },     //SPI_SSEL_0
		{ LPC_GPIO0, SSEL, FUNC3 },      //SPI_SSEL_0
		{ LPC_GPIO0, P0_17, FUNC0 },     //SPI_MISO_0
		{ LPC_GPIO0, CTS1, FUNC1 },      //SPI_MISO_0
		{ LPC_GPIO0, MISO0, FUNC2 },     //SPI_MISO_0
		{ LPC_GPIO0, MISO, FUNC3 },      //SPI_MISO_0
		{ LPC_GPIO0, P0_18, FUNC0 },     //SPI_MOSI_0
		{ LPC_GPIO0, DCD1, FUNC1 },      //SPI_MOSI_0
		{ LPC_GPIO0, MOSI0, FUNC2 },     //SPI_MOSI_0
		{ LPC_GPIO0, MOSI, FUNC3 },      //SPI_MOSI_0
		{ LPC_GPIO0, P0_19, FUNC0 },     //P0_19
		{ LPC_GPIO0, DSR1, FUNC1 },      //P0_19
		{ LPC_GPIO0, SDA1, FUNC2 },      //P0_19
		{ LPC_GPIO0, P0_20, FUNC0 },     //P0_20
		{ LPC_GPIO0, DTR1, FUNC1 },      //P0_20
		{ LPC_GPIO0, SCL1, FUNC2 },      //P0_20
		{ LPC_GPIO0, P0_21, FUNC0 },     //P0_21
		{ LPC_GPIO0, RI1, FUNC1 },       //P0_21
		{ LPC_GPIO0, RD1, FUNC2 },       //P0_21
		{ LPC_GPIO0, P0_22, FUNC0 },     //P0_22
		{ LPC_GPIO0, RTS1, FUNC1 },      //P0_22
		{ LPC_GPIO0, TD1, FUNC2 },       //P0_22
		{ LPC_GPIO0, P0_23, FUNC0 },     //AD0_0
		{ LPC_GPIO0, AD0_0, FUNC1 },     //AD0_0
		{ LPC_GPIO0, I2SRX_CLK, FUNC2 }, //AD0_0
		{ LPC_GPIO0, CAP3_0, FUNC2 },    //AD0_0
		{ LPC_GPIO0, P0_24, FUNC0 },     //AD0_1
		{ LPC_GPIO0, AD0_1, FUNC1 },     //AD0_1
		{ LPC_GPIO0, I2SRX_WS, FUNC2 },  //AD0_1
		{ LPC_GPIO0, CAP3_1, FUNC2 },    //AD0_1
		{ LPC_GPIO0, P0_25, FUNC0 },     //AD0_2
		{ LPC_GPIO0, AD0_2, FUNC1 },     //AD0_2
		{ LPC_GPIO0, I2SRX_SDA, FUNC2 }, //AD0_2
		{ LPC_GPIO0, TXD3, FUNC2 },      //AD0_2
		{ LPC_GPIO0, P0_26, FUNC0 },     //AD0_3/AOUT
		{ LPC_GPIO0, AD0_3, FUNC1 },     //AD0_3/AOUT
		{ LPC_GPIO0, AOUT, FUNC2 },      //AD0_3/AOUT
		{ LPC_GPIO0, RXD3, FUNC2 },      //AD0_3/AOUT
		{ LPC_GPIO0, P0_27, FUNC0 },     //I2C_SDA_0
		{ LPC_GPIO0, SDA0, FUNC1 },      //I2C_SDA_0
		{ LPC_GPIO0, USB_SDA, FUNC2 },   //I2C_SDA_0
		{ LPC_GPIO0, P0_28, FUNC0 },     //I2C_SCL_0
		{ LPC_GPIO0, SCL0, FUNC1 },      //I2C_SCL_0
		{ LPC_GPIO0, USB_SCL, FUNC2 },   //I2C_SCL_0
		{ LPC_GPIO0, P0_29, FUNC0 },     //USB_DP
		{ LPC_GPIO0, USB_DP, FUNC1 },    //USB_DP
		{ LPC_GPIO0, P0_30, FUNC0 },     //USB_DN
		{ LPC_GPIO0, USB_DN, FUNC1 },    //USB_DN
		{ LPC_GPIO1, P1_0, FUNC0 },      //ENET_TXD0
		{ LPC_GPIO1, ENET_TXD0, FUNC1 }, //ENET_TXD0
		{ LPC_GPIO1, P1_1, FUNC0 },      //ENET_TXD1
		{ LPC_GPIO1, ENET_TXD1, FUNC1 }, //ENET_TXD1
		{ LPC_GPIO1, P1_4, FUNC0 },      //ENET_TX_EN
		{ LPC_GPIO1, ENET_TX_EN, FUNC1 }, //ENET_TX_EN
		{ LPC_GPIO1, P1_8, FUNC0 },       //ENET_CRS
		{ LPC_GPIO1, ENET_CRS, FUNC1 },   //ENET_CRS
		{ LPC_GPIO1, P1_9, FUNC0 },       //ENET_RXD0
		{ LPC_GPIO1, ENET_RXD0, FUNC1 },  //ENET_RXD0
		{ LPC_GPIO1, P1_10, FUNC0 },      //ENET_RXD1
		{ LPC_GPIO1, ENET_RXD1, FUNC1 },  //ENET_RXD1
		{ LPC_GPIO1, P1_14, FUNC0 },      //ENET_RX_ER
		{ LPC_GPIO1, ENET_RX_ER, FUNC1 }, //ENET_RX_ER
		{ LPC_GPIO1, P1_15, FUNC0 },      //ENET_REF_CLK
		{ LPC_GPIO1, ENET_REF_CLK, FUNC1 }, //ENET_REF_CLK
		{ LPC_GPIO1, P1_16, FUNC0 },        //ENET_MDC
		{ LPC_GPIO1, ENET_MDC, FUNC1 },     //ENET_MDC
		{ LPC_GPIO1, P1_17, FUNC0 },         //ENET_MDIO
		{ LPC_GPIO1, ENET_MDIO, FUNC1 },    //ENET_MDIO
		{ LPC_GPIO1, P1_18, FUNC0 },        //USB_UP_LED
		{ LPC_GPIO1, USB_UP_LED, FUNC1 },   //USB_UP_LED
		{ LPC_GPIO1, PWM1_1, FUNC2 },       //USB_UP_LED
		{ LPC_GPIO1, CAP1_0, FUNC3 },       //USB_UP_LED
		{ LPC_GPIO1, P1_19, FUNC0 },             //P1_19
		{ LPC_GPIO1, MC0A, FUNC1 },              //P1_19
		{ LPC_GPIO1, nUSB_PPW, FUNC2 },          //P1_19
		{ LPC_GPIO1, CAP1_1, FUNC3 },            //P1_19
		{ LPC_GPIO1, P1_20, FUNC0 },             //P1_20
		{ LPC_GPIO1, MCFB0, FUNC1 },             //P1_20
		{ LPC_GPIO1, PWM1_2, FUNC2 },            //P1_20
		{ LPC_GPIO1, SCK0, FUNC3 },              //P1_20
		{ LPC_GPIO1, P1_21, FUNC0 },             //P1_21
		{ LPC_GPIO1, MCABORT, FUNC1 },           //P1_21
		{ LPC_GPIO1, PWM1_3, FUNC2 },            //P1_21
		{ LPC_GPIO1, SSEL0, FUNC3 },             //P1_21
		{ LPC_GPIO1, P1_22, FUNC0 },             //P1_22
		{ LPC_GPIO1, MC0B, FUNC1 },              //P1_22
		{ LPC_GPIO1, USB_PWRD, FUNC2 },          //P1_22
		{ LPC_GPIO1, MAT1_0, FUNC3 },            //P1_22
		{ LPC_GPIO1, P1_23, FUNC0 },             //P1_23
		{ LPC_GPIO1, MCFB1, FUNC1 },             //P1_23
		{ LPC_GPIO1, PWM1_4, FUNC2 },            //P1_23
		{ LPC_GPIO1, MISO0, FUNC3 },             //P1_23
		{ LPC_GPIO1, P1_24, FUNC0 },             //P1_24
		{ LPC_GPIO1, MCFB2, FUNC1 },             //P1_24
		{ LPC_GPIO1, PWM1_5, FUNC2 },            //P1_24
		{ LPC_GPIO1, MOSI0, FUNC3 },             //P1_24
		{ LPC_GPIO1, P1_25, FUNC0 },             //P1_25
		{ LPC_GPIO1, MC1A, FUNC1 },              //P1_25
		{ LPC_GPIO1, MAT1_1, FUNC2 },            //P1_25
		{ LPC_GPIO1, P1_26, FUNC0 },             //P1_26

		{ LPC_GPIO1, MC1B, FUNC1 },              //P1_26
		{ LPC_GPIO1, PWM1_6, FUNC2 },            //P1_26
		{ LPC_GPIO1, CAP0_0, FUNC3 },            //P1_26
		{ LPC_GPIO1, P1_27, FUNC0 },             //P1_27
		{ LPC_GPIO1, CLKOUT, FUNC1 },            //P1_27
		{ LPC_GPIO1, nUSB_OVRCR, FUNC2 },        //P1_27
		{ LPC_GPIO1, CAP0_1, FUNC3 },            //P1_27
		{ LPC_GPIO1, P1_28, FUNC0 },             //P1_28
		{ LPC_GPIO1, MC2A1_0, FUNC1 },            //P1_28
		{ LPC_GPIO1, MAT0_0, FUNC2 },            //P1_28
		{ LPC_GPIO1, P1_29, FUNC0 },             //TEST_LED
		{ LPC_GPIO1, MC2B, FUNC1 },              //TEST_LED
		{ LPC_GPIO1, PCAP1_1, FUNC2 },           //TEST_LED
		{ LPC_GPIO1, MAT0_1, FUNC3 },            //TEST_LED
		{ LPC_GPIO1, P1_30, FUNC0 },             //VBUS
		{ LPC_GPIO1, VBUS, FUNC1 },              //VBUS

		{ LPC_GPIO1, AD0_4, FUNC2 },             //VBUS
		{ LPC_GPIO1, P1_31, FUNC0 },             //AD0_5
		{ LPC_GPIO1, SCK1, FUNC1 },              //AD0_5
		{ LPC_GPIO1, AD0_5, FUNC2 },             //AD0_5
		{ LPC_GPIO2, P2_0, FUNC0 },              //UART_TX_1
		{ LPC_GPIO2, PWM1_1, FUNC1 },            //UART_TX_1
		{ LPC_GPIO2, TXD1, FUNC2 },              //UART_TX_1
		{ LPC_GPIO2, P2_1, FUNC0 },              //UART_RX_1
		{ LPC_GPIO2, PWM1_2, FUNC1 },            //UART_RX_1
		{ LPC_GPIO2, RXD1, FUNC2 },              //UART_RX_1
		{ LPC_GPIO2, P2_2, FUNC0 },              //PWM_1_3
		{ LPC_GPIO2, PWM1_3, FUNC1 },            //PWM_1_3
		{ LPC_GPIO2, CTS1, FUNC2 },              //PWM_1_3
		{ LPC_GPIO2, TRACEDATA3, FUNC3 },        //PWM_1_3
		{ LPC_GPIO2, P2_3, FUNC0 },              //PWM_1_4
		{ LPC_GPIO2, PWM1_4, FUNC1 },            //PWM_1_4
		{ LPC_GPIO2, DCD1, FUNC2 },              //PWM_1_4
		{ LPC_GPIO2, TRACEDATA2, FUNC3 },        //PWM_1_4
		{ LPC_GPIO2, P2_4, FUNC0 },              //PWM_1_5
		{ LPC_GPIO2, PWM1_5, FUNC1 },            //PWM_1_5
		{ LPC_GPIO2, DSR1, FUNC2 },              //PWM_1_5
		{ LPC_GPIO2, TRACEDATA1, FUNC3 },        //PWM_1_5
		{ LPC_GPIO2, P2_5, FUNC0 },              //PWM_1_6
		{ LPC_GPIO2, PWM1_6, FUNC1 },            //PWM_1_6
		{ LPC_GPIO2, DTR1, FUNC2 },              //PWM_1_6
		{ LPC_GPIO2, TRACEDATA0, FUNC3 },        //PWM_1_6
		{ LPC_GPIO2, P2_6, FUNC0 },              //P2_6
		{ LPC_GPIO2, PCAP1_0, FUNC1 },           //P2_6
		{ LPC_GPIO2, RI1, FUNC2 },               //P2_6
		{ LPC_GPIO2, TRACECLK, FUNC3 },         //P2_6
		{ LPC_GPIO2, P2_7, FUNC0 },              //P2_7
		{ LPC_GPIO2, RD2, FUNC1 },               //P2_7
		{ LPC_GPIO2, RTS1, FUNC2 },              //P2_7
		{ LPC_GPIO2, P2_8, FUNC0 },              //P2_8
		{ LPC_GPIO2, TD2, FUNC1 },               //P2_8
		{ LPC_GPIO2, TXD2, FUNC2 },              //P2_8
		{ LPC_GPIO2, P2_9, FUNC0 },              //CONNECTOR
		{ LPC_GPIO2, USB_CONNECT, FUNC1 },     //CONNECTOR
		{ LPC_GPIO2, RXD2, FUNC2 },              //CONNECTOR
		{ LPC_GPIO2, P2_10, FUNC0 },             //P2_10/BLD
		{ LPC_GPIO2, nEINT0, FUNC1 },            //P2_10/BLD
		{ LPC_GPIO2, NMI, FUNC2 },               //P2_10/BLD
		{ LPC_GPIO2, P2_11, FUNC0 },             //P2_11
		{ LPC_GPIO2, nEINT1, FUNC1 },            //P2_11
		{ LPC_GPIO2, I2STX_CLK, FUNC2 },         //P2_11
		{ LPC_GPIO2, P2_12, FUNC0 },             //P2_12
		{ LPC_GPIO2, nEINT2, FUNC1 },            //P2_12
		{ LPC_GPIO2, I2STX_WS, FUNC2 },          //P2_12
		{ LPC_GPIO2, P2_13, FUNC0 },             //P2_13
		{ LPC_GPIO2, nEINT3, FUNC1 },            //P2_13
		{ LPC_GPIO2, I2STX_SDA, FUNC2 },         //P2_13
		{ LPC_GPIO3, P3_25, FUNC0 },             //PWM_1_2
		{ LPC_GPIO3, MAT0_0, FUNC1 },            //PWM_1_2
		{ LPC_GPIO3, PWM1_2, FUNC2 },            //PWM_1_2
		{ LPC_GPIO3, P3_26, FUNC0 },             //P3_26
		{ LPC_GPIO3, STCLK, FUNC1 },             //P3_26
		{ LPC_GPIO3, MAT0_1, FUNC2 },            //P3_26
		{ LPC_GPIO3, PWM1_3, FUNC2 },            //P3_26
		{ LPC_GPIO4, P4_28, FUNC0 },             //P4_28
		{ LPC_GPIO4, RX_MCLK, FUNC1 },           //P4_28
		{ LPC_GPIO4, MAT2_0, FUNC2 },            //P4_28
		{ LPC_GPIO4, TXD3, FUNC2 },              //P4_28
		{ LPC_GPIO4, P4_29, FUNC0 },             //P4_29
		{ LPC_GPIO4, TX_MCLK, FUNC1 },           //P4_29
		{ LPC_GPIO4, MAT2_1, FUNC2 },            //P4_29
		{ LPC_GPIO4, RXD3, FUNC2 },              //P4_29

};*/

const Pinconfig_t UARTPins[]={
		{ LPC_GPIO0, TXD0, FUNC1 },               //UART_TX_0
		{ LPC_GPIO0, RXD0, FUNC1 },               //UART_RX_0
};


const Pinconfig_t I2CPins[]={
		{ LPC_GPIO0, SDA0, FUNC1 },      //I2C_SDA_0
		{ LPC_GPIO0, SCL0, FUNC1 },      //I2C_SCL_0
		{ LPC_GPIO0, SDA1, FUNC3 },      //CAN_RD_1
		{ LPC_GPIO0, SCL1, FUNC3 },      //CAN_TD_1
		{ LPC_GPIO0, SDA2, FUNC2 },      //P0_10
		{ LPC_GPIO0, SCL2, FUNC2 },      //P0_11
};

const Pinconfig_t GPIOPins[]={
		{ LPC_GPIO0, P0_7, FUNC0 },               //P0_7
		{ LPC_GPIO1, P1_29,  FUNC0 },     		 //P1_29

};

/* Function for selecting the pin muxing by giving the GPIO base address and the pinnum and functionality */
void vPinmuxSel(LPC_GPIO_TypeDef *GPIOx,uint8_t Pinnum, uint8_t functionality)
{

/*	0x2009C000  considering last byte in this 0x00 ->0000 0000 we can shift this 5 times to right and we get 000
	0x2009C020  considering last byte in this 0x20 ->0010 0000 we can shift this 5 times to right and we get 001
	0x2009C040  considering last byte in this 0x40 ->0100 0000 we can shift this 5 times to right and we get 010
	0x2009C060  considering last byte in this 0x60 ->0110 0000 we can shift this 5 times to right and we get 011
	0x2009C080  considering last byte in this 0x80 ->1000 0000 we can shift this 5 times to right and we get 100
*/
	uint8_t pinselnum=0,bitpos=0;
	/*Converting the address into an integer */
	uint32_t portnum = (uint32_t) GPIOx;
	portnum = (portnum>>5)&0x7;

	pinselnum = portnum * 2; // Alternatively we can get pinselnum = portnum<<1
	if(Pinnum>15)
		pinselnum = pinselnum+1;

	/* For example we have P0.6 to find the  bit position for the P0.6 in PINSEL0 we need to do multiplication by 2
	 * i.e. 6*2=12, starting bit position is 12
	 * Similar way for P0.27 to find out the bit position for the P0.27 in PINSEL1 we need to multiply by 2 and subtract 32 to
	 * get the bit position i.e. 27*2=54-32 starting bit position is 22
 	 */
	bitpos = Pinnum *2;
	if(bitpos>31)
	{
		bitpos = bitpos-32;
	}

	Pinnum = Pinnum *2;

	*((uint32_t *)((&LPC_PINCON->PINSEL0) + pinselnum)) &= ~(3<<bitpos);
	*((uint32_t *)((&LPC_PINCON->PINSEL0) + pinselnum)) |= functionality<<bitpos;

	/*switch(pinselnum)
	{

	case 0:
		LPC_PINCON->PINSEL0 &= ~(3<<Pinnum);
		LPC_PINCON->PINSEL0 |= functionality<<Pinnum;
	break;
	case 1:
		LPC_PINCON->PINSEL1 &= ~(3<<Pinnum);
		LPC_PINCON->PINSEL1 |= functionality<<Pinnum;
	break;

	}*/

}

/* Function for initializing the selected pins with appropriate functionality */
void vPinmuxInitialize(void)
{
    /* Configuring GPIO pins */
    vPinmuxSel(GPIOPins[0].GPIOx,GPIOPins[0].pin,GPIOPins[0].func);
    vPinmuxSel(GPIOPins[1].GPIOx,GPIOPins[1].pin,GPIOPins[1].func);
    /* Configuring UART0 pins */
    vPinmuxSel(UARTPins[0].GPIOx,UARTPins[0].pin,UARTPins[0].func);
    vPinmuxSel(UARTPins[1].GPIOx,UARTPins[1].pin,UARTPins[1].func);
    /* Configuring I2C0 pins */
    vPinmuxSel(I2CPins[0].GPIOx,I2CPins[0].pin,I2CPins[0].func);
    vPinmuxSel(I2CPins[1].GPIOx,I2CPins[1].pin,I2CPins[1].func);
    /* Configuring I2C1 pins */
	vPinmuxSel(I2CPins[2].GPIOx, I2CPins[2].pin, I2CPins[2].func);
	vPinmuxSel(I2CPins[3].GPIOx, I2CPins[3].pin, I2CPins[3].func);
	/* Configuring I2C2 pins */
	vPinmuxSel(I2CPins[4].GPIOx, I2CPins[4].pin, I2CPins[4].func);
	vPinmuxSel(I2CPins[5].GPIOx, I2CPins[5].pin, I2CPins[5].func);

}

