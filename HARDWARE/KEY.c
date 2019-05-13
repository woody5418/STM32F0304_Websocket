#include "stm32f0xx.h"
#include "delay.h"
#include "key.h"
#include "USART1.h"
#include "espjson.h"

static uint8_t key_num_flag = 0;

void KeyInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* 配置KEY相应引脚PA1*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //GPIO_Pin_1 | GPIO_Pin_2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// 按键PA4 上来输入   按下去3S
void KEY_SCAN(void)
{
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == Bit_RESET) // ==0
    {
        delay_ms(500);
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == Bit_RESET)
        {
            key_num_flag++;
            if(key_num_flag == 6)
            {
                //FLAG_led_status=1;  // 状态灯开始亮
                key_num_flag=0;
                GPIO_SetBits(GPIOB, GPIO_Pin_1); //1红灯1
                GPIO_SetBits( GPIOA, GPIO_Pin_7);
                delay_ms(500);
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);//1红灯1
                GPIO_ResetBits( GPIOA, GPIO_Pin_7);
                //选择Airkiss模式
                Control_Flag_Mode = 2;
                NetNumber=0;
            }
        }
    }
    else
    {
        key_num_flag=0;
    }
}


/*
void apps_airkiss_key_check(void)
{
	static uint8_t KEY_State = 0;
	static uint8_t KEY_TimeCount = 0;
	switch(KEY_State)
	{
		case 0:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == Bit_RESET)
			{
				KEY_State++;
			}
			break;
		case 1:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == Bit_RESET)
			{
				KEY_TimeCount=0;
				KEY_State++;
			}else
			{
				KEY_State=0;
			}
			break;
		case 2:
			if(KEY_TimeCount <= 3*1000/10) //3S
			{
				KEY_TimeCount++;
			}else
			{
				////
			}
			if(GPIO_ReadInputDataBit8(GPIOA, GPIO_Pin_2) == Bit_SET)
			{
				KEY_State++;
			}
			break;
		case 3:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == Bit_SET)
			{
				if(KEY_TimeCount>=100/10)
				{
					if(KEY_TimeCount<2*1000/10)
					{
						////
					}
				}
				KEY_State=0;
			}
			break;
		default:
			break;
	}
}
*/
