#include "stm32f401rbt6.h"
#include "lcd.h"
#include "adc.h"
#include "systick.h"

extern int jiffie;
 int temp;

 void KM_mdelay_IT(int x)
 {
	 STK_CTRL |=(0X7);				//LOAD 101 to stk_ctrl to set enable and clksrc(bit2)
	   STK_VAL |=(0X5123);		//load any value to stk_val to clear the register
	 		STK_LOAD |=16000-1;		//load 16000 to stk_load for 100ms
	
	 temp=jiffie+x;
	 while(temp>=jiffie)
	 {
		 ;
	 }
 }
 
  void KM_udelay_IT(int x)
 {
	 	 STK_CTRL |=(0X7);	  //LOAD 101 to stk_ctrl to set enable and clksrc(bit2)
		STK_VAL |=(0X5123);		//load any value to stk_val to clear the register
	 		STK_LOAD |=16-1;			//load 16000 to stk_load for 1us

	 temp=jiffie+x;
	 while(temp>=jiffie)
	 {
		 ;
	 }
 }
 
 
