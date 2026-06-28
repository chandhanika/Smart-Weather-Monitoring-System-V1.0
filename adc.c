#include "stm32f401rbt6.h"
#include "lcd.h"
#include "adc.h"
#include "systick.h"

extern int adc_raw;
int temp1;

void Adc_Init(void)
	{ 
	RCC_AHB1ENR |= (0x1<<2);		// Enable clock for GPIOC
	RCC_APB2ENR |= (0x1<<8);		// Enable clock for ADC1

	GPIOC_MODER &= ~(0x3);		// Clear mode bits of PC1
	GPIOC_MODER |= (0x3);		// Configure PC1 as Analog mode
	ADC_SQR3 |= 0xA;			// Select ADC input channel
	ADC_CR2 = 1;					// Enable ADC
  //ADC_CR2 |= (0x1<<30);
	ADC_CR1 |= (0x1<<5);			// Enable End Of Conversion (EOC) interrupt
	NVIC_ISER0 |= (0X1<<18);			// Enable ADC interrupt in NVIC
	

}
int Adc_read(void)
{
	return (adc_raw*330)/4096;
	
}
