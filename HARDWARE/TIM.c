#include "TIM.h"
#include "LED.h"
#include "json.h"
#include "espjson.h"
#include "apps.h"
#include "ADC1.h"


uint16_t tim3_times = 0;  //传入参数
uint16_t tims = 0;   //tim函数计数变量
uint8_t FLAG_delay_s = 0;
uint8_t FLAG_led_status=0;
uint8_t Start_Tim3_Config = 0;
static uint8_t delay_times = 0;
static uint8_t control_led_status=0;
float adcx;


void TIM3_Configuration_set(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //     TIM_Period = 1000 是1S
    TIM_TimeBaseStructure.TIM_Period = 50;  // 自动重装载寄存器周期的值(计数值)
    TIM_TimeBaseStructure.TIM_Prescaler = (8000 - 1);	//时钟预分频数
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;			//向上计数模式
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);			        // 清除溢出中断标志
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
        if (Start_Tim3_Config == 1)
        {
            if (tims >= (uint16_t) (tim3_times * 20)) //3S
            {
                tims = 0;
                Start_Tim3_Config = 0;
            }
            tims++;
        }
        else
        {
            if (FLAG_delay_s == 1)
            {
                delay_times++;
                if (delay_times == 100)
                {
                    delay_times = 0;
                    if (FLAG_APPS_CJSON_SEND == 1)
                    {
                        adcx = (float)(RegularConvData_Tab[0])*3.3/4096;//小数点后6位 3.299194
                        send_data_user(STATMAC, "on",adcx);
                    }
                    else
                    {
                        adcx = (float)(RegularConvData_Tab[0])*3.3/4096;//小数点后6位 3.299194
                        send_data_user(STATMAC, "off",adcx);
                    }
                }
            }
        }
        if(FLAG_led_status == 1)
        {
            if(control_led_status == 0)
            {
                control_led_status = 1;
                GPIO_SetBits(GPIOB, GPIO_Pin_1);  //亮
            }
            else
            {
                control_led_status = 0;
                GPIO_ResetBits(GPIOB, GPIO_Pin_1);  //0红灯灭
            }
        }
    }

}

void Start_Count(uint16_t times)
{
    Start_Tim3_Config = 1;
    tims = 0;
    tim3_times = times;
    TIM_Cmd(TIM3, ENABLE);
}

void Stop_Count(void)
{
    Start_Tim3_Config = 0;
    tims = 0;
    TIM_Cmd(TIM3, DISABLE);
}



