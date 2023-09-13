/*
 * gpio.h
 *

 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <LPC17xx.h>

#define PORT0 LPC_GPIO0
#define PORT1 LPC_GPIO1
#define PORT2 LPC_GPIO2
#define PORT3 LPC_GPIO3
#define PORT4 LPC_GPIO4


enum {PIN0=0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7,PIN8,PIN9,
	  PIN10,PIN11,PIN12,PIN13,PIN14,PIN15,PIN16,PIN17,PIN18,PIN19,
	  PIN20,PIN21,PIN22,PIN23,PIN24,PIN25,PIN26,PIN27,PIN28,PIN29,
	  PIN30,PIN31};

enum {INPUT=0,OUTPUT};
enum {LOW=0, HIGH};


/*Function for setting the direction of a pin inside a port as INPUT/OUTPUT */
void vGPIOSetDir(LPC_GPIO_TypeDef* xGPIOX,uint8_t Pinnum,uint8_t Direction);
/* Function for setting the value of a pin inside a port as HIGH */
void vGPIOSetPin(LPC_GPIO_TypeDef* xGPIOX,uint8_t Pinnum);
/* Function for setting the value of a pin inside a port as CLEAR */
void vGPIOClrPin(LPC_GPIO_TypeDef* xGPIOX,uint8_t Pinnum);
/* Function for getting the value of a pin inside a port */
uint32_t uGPIOGetValue(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum);
/* Function for writing byte value to 8 consecutive pins */
void vGPIOWriteByteVal(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint8_t Value);
/* Function for writing nibble value to 4 consecutive pins */
void vGPIOWriteNibble(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint8_t Value);
/* Function for toggling the value of a pin inside a port as HIGH/LOW */
void vGPIOTogglePin(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum,uint8_t* state);
/* Function for writing value to any number of consecutive pins */
void vGPIOWritePortVal(LPC_GPIO_TypeDef* xGPIOX, uint8_t Pinnum, uint32_t mask,uint32_t Value);


#endif /* GPIO_H_ */
