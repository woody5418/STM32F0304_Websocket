#include "stm32f0xx.h"
#include "USART1.h"
#include "apps.h"
#include "delay.h"
#include "led.h"
#include "json.h"
#include "espjson.h"

uint8_t Ana_Buffer[USART_REC_LEN];  //转化数组
uint8_t FLAG_APPS_CJSON_SEND = 0;  // 定时器发送cJson控制变量

static uint8_t Legal_cJson = 2;  // 检测JSON
static char json_get_cmd[4] ="";      //给定长度


/*
接收到的数据解析
{"cmd":"on","id":"867068024046301","to":"5c:cf:7f:11:96:0b"}\r\n
{"cmd":"off","id":"867068024046301","5c:cf:7f:11:96:0b"}\r\n
*/// 解析数据
void Analysis_Data(void)
{
    uint8_t len_ana = 0,t = 0;
    if (USART_RX_STA & 0x8000)
    {
        len_ana = USART_RX_STA & 0x3FFF;
        for(t=0; t<len_ana; t++)
        {
            Ana_Buffer[t] = USART_RX_BUF[t];
        }
        Clean_Buffer(USART_REC_LEN);
        USART_RX_STA=0;
        if(json_check((char *)Ana_Buffer) == 1)  Legal_cJson=1;
        else Legal_cJson =0;
    }
    if(Legal_cJson == 1) //合法JSON
    {
        json_get_value((char *)Ana_Buffer,"cmd",json_get_cmd);
        if(json_check_value(json_get_cmd,"on") == 1)
        {
            Legal_cJson=0;
            FLAG_APPS_CJSON_SEND = 1;
            GPIO_SetBits( GPIOA, GPIO_Pin_7);  //亮//LED亮PB1
            *json_get_cmd=0;
        }
        else
        {
            if(json_check_value(json_get_cmd,"off") == 1)
            {
                Legal_cJson=0;
                FLAG_APPS_CJSON_SEND = 0;
                GPIO_ResetBits( GPIOA, GPIO_Pin_7);   // LED 灭PB1
                *json_get_cmd=0;
            }
        }
    }

}

