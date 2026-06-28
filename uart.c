#include "stm32f401rbt6.h"
#include "uart.h"
#include "lcd.h"
#include "systick.h"
#include "lcd.h"
#include "esp8266.h"
#include "adc.h"


void UART6_OutChar(unsigned char outData)
{
	while((USART6_SR & (0x1<<7))==0);	// Wait until transmit data register is empty
	USART6_DR = outData;		// Load data into transmit data register

}

void UART6_OutStr(char *ch)
{  
	int i;
	for(i=0;ch[i]!='\0';i++)
	{
		UART6_OutChar(ch[i]);
	}
}




void UART6_Init()
{
	RCC_AHB1ENR |= (0x1<<2);
	RCC_APB2ENR |= (0x1<<5);		// Enable clock for USART6

	GPIOC_MODER &= ~(0xF<<12);		// Clear mode bits for PA2 and PA3
	GPIOC_MODER |= (0xA<<12);		// Set PA2 and PA3 to Alternate Function mode
	
	GPIOC_AFRL &= ~(0xFF<<24);		// Clear alternate function bits for PA2 and PA3
	GPIOC_AFRL |= (0x88<<24);		// Select AF7 (USART2) for PA2 and PA3, load 7 into 8 t0 11 and 12 t0 15 bits

	USART6_BRR = 0x8B;				// Set baud rate to 9600 (16 MHz clock)
	USART6_CR1 |= ((0x3<<2) | (0x1<<13));	// Enable transmitter, receiver and USART2
	
}