#include "stm32f401rbt6.h"
#include "uart.h"
#include "lcd.h"
#include "systick.h"
#include "lcd.h"
#include "esp8266.h"
#include "adc.h"

char buff;
extern int temp2,adc_done;
char FETCH[100],buffer[100];
char buff1[10];
int x;
int KM_UART6_TimeOut(int x)
{
	while(x--)
	{
	if(USART6_SR & RXNE)
	{
		buff = USART6_DR;
		return 0;
	}
	}
	return 1;
}



int Wifi_OK_response()
{
	int i;
	//memset(buffer,'\0',100	);
	for(i=0;i<500;i++)
	{
		if(!(KM_UART6_TimeOut(10000)))
		{
			buffer[i]=buff;
		}

    if(buffer[i]=='K' && buffer[i-1]=='O')
    {
        return 0;
    }
}
	return 1;
}

int wifi_STATUS_Esp8266()
{
	int i;
//	memset(buffer,'\0',1024);
	for(i=0;i<70;i++)
	{
		if(!(KM_UART6_TimeOut(10000)))
		{
			buffer[i]=buff;
		}

		if(buffer[i]=='3' || buffer[i]=='2')
		{
			return 0;
		}
	}
	return 1;
}


int wifi_Done_Esp8266()
{
	int i;
	for(i=0;i<500;i++)
	{
		if(!(KM_UART6_TimeOut(10000)))
		{
			buffer[i]=buff;
		}
		if(buffer[i-3]=='d' || buffer[i-2]=='o' || buffer[i-1]=='n' || buffer[i]=='e')
		{
			return 0;
		}
	}
	return 1;
}

int Wifi_Init()
{
	int i=2;
	while(i)
	{
	UART6_OutStr("AT\r\n");
	if(!(Wifi_OK_response()))
	{
		KM_LCD_Write_Str("Wi-Fi Found");
		KM_mdelay_IT(1000);
		return 0;
	}
	else
	{
		i--;
	}
}
		KM_LCD_Write_Str("Wi-Fi Not Found");
		return 1;
}


int wifi_configuration()
{
		KM_LCD_Write_Cmd(0x01);
		KM_LCD_Write_Cmd(0x80);
		KM_LCD_Write_Str("establishing");
		KM_LCD_Write_Cmd(0xc0);
		KM_LCD_Write_Str("connection...");
		KM_mdelay_IT(1000);

		UART6_OutStr("AT+RST\r\n");
		KM_mdelay_IT(5000);

		UART6_OutStr("AT+CWMODE=3\r\n");
		if(!(Wifi_OK_response()))
		{
			UART6_OutStr("AT+CWJAP?\r\n");
			if(!(Wifi_OK_response()))
			{
			//			memset(buffer,'\0',100);
				UART6_OutStr("AT+CWJAP=\"chikenwing\",\"sl2One29\"\r\n");
				if(!(Wifi_OK_response()))
				{
			//				memset(buffer,'\0',100);
					UART6_OutStr("AT+CIPMUX=0\r\n");
					if(!(Wifi_OK_response()))
					{
						memset(buffer,'\0',100);
						KM_LCD_Write_Cmd(0x01);
						KM_LCD_Write_Cmd(0x80);
						KM_LCD_Write_Str("connection");
						KM_LCD_Write_Cmd(0xc0);
						KM_LCD_Write_Str("established");
						KM_mdelay_IT(1000);
						return 0;
					}
				}
			}
		}

		KM_LCD_Write_Cmd(0x01);	
		KM_LCD_Write_Cmd(0x80);
		KM_LCD_Write_Str("Connection");
		KM_LCD_Write_Cmd(0xc0);
		KM_LCD_Write_Str("Failed");
		return 1;
}
	
	

	
int wifi_operation()
{
	KM_LCD_Write_Cmd(0x01);
	KM_LCD_Write_Cmd(0x80);
	KM_LCD_Write_Str("Transmitting");
	KM_LCD_Write_Cmd(0xc0);
	KM_LCD_Write_Str("data...");
	KM_mdelay_IT(3000);
		UART6_OutStr("AT+CIPSTATUS\r\n");
	//KM_mdelay_IT(500);
		if(!(wifi_STATUS_Esp8266()))
		{
			memset(buffer,'\0',100);
			UART6_OutStr("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n");
			//KM_mdelay_IT(1000);
			if(!(Wifi_OK_response()))
			{
				memset(buffer,'\0',100);
					while(1)
					{
				UART6_OutStr("AT+CIPSEND=37\r\n");
			//	KM_mdelay_IT(1000);

				if(!(Wifi_OK_response()))
				{
					ADC_CR2 |= (0x1<<30);
					while(adc_done == 0){;}
					temp2=Adc_read();
					sprintf(FETCH,"GET /page.php?temp=%d&hum=40&dev=50\r\n",temp2);
					UART6_OutStr(FETCH);
					if(!x)
					{
					if(!(wifi_Done_Esp8266()))
					{
						KM_LCD_Write_Cmd(0x01);
						KM_LCD_Write_Cmd(0x80);
						KM_LCD_Write_Str("Data");
						KM_LCD_Write_Cmd(0xc0);
						KM_LCD_Write_Str("transmitted");
						KM_mdelay_IT(5000);
						x=1;
					//	return 0;
					}
				}
				}
				}
			}
		}
		KM_LCD_Write_Cmd(0x01);
		KM_LCD_Write_Cmd(0x80);
		KM_LCD_Write_Str("Transmission");
		KM_LCD_Write_Cmd(0xc0);
		KM_LCD_Write_Str("failed");
		return 1;
}
	