
#ifndef __USART1_H
#define __USART1_H

#include "stm32f0xx.h"
#include <stdio.h>

#define USART_REC_LEN  	128

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


extern uint16_t USART_RX_STA;       //接收状态标记
extern uint8_t  USART_RX_BUF[USART_REC_LEN];   //缓冲数组，最大接收64字节


void USART1_Init(uint32_t baud);

#endif
