/*
 * gpio.c

 */


#include <LPC17xx.h>
#include "gpio.h"

/* Function for setting the direction of a pin inside a port as INPUT/OUTPUT
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 * Direction can take values either 0 or 1
 */
void vGPIOSetDir(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint8_t Direction) {
	if (Direction == OUTPUT)
		xGPIOX->FIODIR |= 1 << Pinnum;
	else if (Direction == INPUT)
		xGPIOX->FIODIR &= ~(1 << Pinnum);
}

/* Function for setting the value of a pin inside a port as HIGH
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 */

void vGPIOSetPin(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum) {
	xGPIOX->FIOSET = 1 << Pinnum;
}

/* Function for setting the value of a pin inside a port as CLEAR
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 */
void vGPIOClrPin(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum) {
	xGPIOX->FIOCLR = 1 << Pinnum;
}

/* Function for getting the value of a pin inside a port
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 * Return value is a 32bit number
 */
uint32_t uGPIOGetValue(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum) {
	return xGPIOX->FIOPIN & 1 << Pinnum;
}

/* Function for writing byte value to 8 consecutive pins
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 * Value  -  Can take value from 0x00 to 0xFF / 0 to 255
 */

void vGPIOWriteByteVal(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint8_t Value) {
	xGPIOX->FIOCLR = 0xFF << Pinnum;
	xGPIOX->FIOSET = Value << Pinnum;
}

/* Function for writing nibble value to 4 consecutive pins
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 * Value  -  Can take value from 0x00 to 0xF / 0 to 15
 */

void vGPIOWriteNibble(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint8_t Value) {
	xGPIOX->FIOCLR = 0xF << Pinnum;
	xGPIOX->FIOSET = Value << Pinnum;

}

/* Function for toggling the value of a pin inside a port as HIGH/LOW
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum  - can take values from 0 to 31
 */

void vGPIOTogglePin(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum,uint8_t* state) {

	if(*state==HIGH)
	xGPIOX->FIOSET = 1 << Pinnum;
	else if (*state==LOW)
	xGPIOX->FIOCLR = 1 << Pinnum;

	*state ^=HIGH;

}

/* Function for writing value to any number of consecutive pins
 * Input Arguments
 * xGPIOX - can take values from LPC_GPIO0 to LPC_GPIO4
 * Pinnum - can take values from 0 to 31
 * mask	  -  can take values like 0x1,0x3,x0x7,0xF,0x1F etc
 * Value  -  Can take value from 0x00000000 to 0xFFFFFFFF / 0 to 2^32-1
 */

void vGPIOWritePortVal(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint32_t mask,uint32_t Value) {
	xGPIOX->FIOMASK = ~(mask<<Pinnum);
	xGPIOX->FIOPIN  = Value << Pinnum;
}

