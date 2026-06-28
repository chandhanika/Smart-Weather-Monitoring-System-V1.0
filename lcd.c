#include "stm32f401rbt6.h"
#include "lcd.h"



void Delay(int n)
{
	volatile int i;
	for(i=0;i<1600*n;i++);
}


void GPIOB_Init(void)
{
	RCC_AHB1ENR |= (0x1<<1);					// Enable clock for GPIO Port B
	
	GPIOB_MODER &= 0xFFFCF000;				// Clear mode bits for PB0-PB8
	GPIOB_MODER |= 0x00010555;
	GPIOB_ODR |=(0xFFFFFEC0);
}


void write_high_nibble(unsigned char data)
{
	GPIOB_ODR &= ~(0xF);   						// Clear PB0-PB3 (LCD data pins D4-D7)
	GPIOB_ODR |= (data>>0x4); 				// Extract higher nibble and place it on PB0-PB3
	GPIOB_ODR |= (0x1<<8);						// Set EN (Enable) pin high to latch data into LCD
	Delay(20);												
	GPIOB_ODR &= ~(0x1<<8);						// Set EN pin low, completing the enable pulse
}


void write_low_nibble( unsigned char data )
{
	GPIOB_ODR &= ~(0xF);							  // Clear PB0-PB3 (LCD data pins D4-D7)
	GPIOB_ODR |= (data&(0x0F));					// Extract lower nibble and place it on PB0-PB3
	GPIOB_ODR |= (0x1<<8);							// Set EN (Enable) pin high to latch data into LCD
	Delay(20);
	GPIOB_ODR &= ~(0x1<<8);							// Set EN pin low, completing the enable pulse
}

void KM_LCD_Write_Cmd( unsigned char data)
{
	GPIOB_ODR &= ~(0x1<<4);				 // Set RS = 0 to select command Register
	write_high_nibble(data);
	write_low_nibble(data);
}

void KM_LCD_Write_Data( unsigned char data)
{
	GPIOB_ODR |= (0x1<<4);				 // Set RS = 1 to select Data Register
	write_high_nibble(data);
	write_low_nibble(data);
}

void KM_LCD_Write_Str(char *str)			// Function to display a complete string on the LCD
{
	int i=0;
	while(str[i] != '\0')   						// Loop until the null terminator ('\0') is reached
	{
		KM_LCD_Write_Data(str[i]);  			// Send the current character to the LCD data register
		i++;															// Move to the next character in the string

	}
}


void KM_LCD_Init(void)
{
GPIOB_Init();
Delay(20);
KM_LCD_Write_Cmd(0x33);
Delay(1);
KM_LCD_Write_Cmd(0x32);
KM_LCD_Write_Cmd(0x0C);
KM_LCD_Write_Cmd(0x01);
//KM_LCD_Write_Cmd(0x0);

}

