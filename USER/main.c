/****************************************************************************
*       Copyright (C), 北京四维拓智教育科技有限公司
*
*       WIFI模块
*       V0.1    
*       2017-06-27 
*       Woody
* 		< STM32F030F4P6 >
			FLASH SIZE:16Kbytes
			RAM SIZE:4Kbytes
			Package:TSSOP20 
*****************************************************************************/
#include "stm32f0xx.h"
#include "delay.h"
#include "ADC1.h"
#include "USART1.h"



int main(void)
{
	delay_init();
	ADC1_Init();
	USART1_Init(9600);
	
	while (1)
	{ 
		
		printf("%d\r\n",ADC_GetValue());
		delay_ms(500);
		
	}
}


/*****END OF FILE****/
