
#ifndef __ADC1_H
#define __ADC1_H

#include "stm32f0xx.h"

#define ADC1_DR_Address                0x40012440



void ADC1_Init(void);
uint16_t ADC_GetValue(void);

#endif



