#include "stm32f401rbt6.h"
#include "uart.h"
#include "lcd.h"
#include "systick.h"
#include "lcd.h"
#include "esp8266.h"
#include "adc.h"

int adc_raw,adc_done;
int jiffie,temp2,flag,temp2,flag1,init,config;
int main()
{
	
	KM_LCD_Init();
	UART6_Init();
	Adc_Init();
	init=Wifi_Init();
	if(!init)
	{
	config=wifi_configuration();
		if(!config)
		{
			wifi_operation();
		}
	}
	}



void ADC_IRQHandler(void)
{
	
	adc_raw = ADC_DR;			// Read ADC conversion result
  //ADC_SR &= ~(0x1<<1);			// Clear EOC flag (not required on STM32F401, reading ADC_DR clears it)
	    adc_done = 1;
}

 void SysTick_Handler(void)
{
	jiffie++;
}