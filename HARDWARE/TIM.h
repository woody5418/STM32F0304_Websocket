#ifndef __TIM_H
#define	__TIM_H

#include "stm32f0xx.h"


extern uint8_t Start_Tim3_Config;
extern uint16_t tim3_times;
extern uint16_t tims;
extern uint8_t FLAG_delay_s;
extern uint8_t FLAG_led_status;


void TIM3_Configuration_set(void);
void Start_Count(uint16_t times);
void Stop_Count(void);
void set_tim2_delay_s(uint16_t times);


#endif
