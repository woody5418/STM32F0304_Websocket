/********************************************************************
 *@file        adc.h
 *@author      Woody      QQ：2490006131
 *@version     V1.0
 *@date        2016-10-14
 *@brief       ADC 初始化
 *******************************************************************/
#ifndef __ESPJSON_H
#define __ESPJSON_H


#include "stm32f0xx.h"

extern  uint8_t Return_OK;
extern  uint8_t flag_0D;
extern  uint8_t flag_0A;
extern  char *STATMAC;
extern  uint8_t USER_SSID[20];  // 用户的SSID
extern  uint8_t USER_PWD[20];   // 用户的PWD


//// 返回OK...SSID...解析函数
void Receive_MAC_Callback(void);
uint8_t Get_Message_SSID_PWD(void);
uint16_t Get_Message_Local_ip(void);
void Reveive_Message_callback(void);
void Receive_Message_airkiss_callback(void);
//// 基础函数
void Clean_Buffer(uint8_t num);
uint8_t USART_Bubber_To_Comma(uint8_t *mes,uint8_t num);
uint8_t USART_Bubber_SSID_Length(uint8_t *mes,uint8_t num);
void Find_STATION_MAC(char *RX_Buf,char *stamac);
//// RXD 处理
void Receive_FIND_Local_ip(uint8_t res);
void Receive_UDP_Analysis_Data(uint8_t res);
void Receive_OK_Callback(uint8_t res,uint8_t flgd,uint8_t flga);
void Receive_Message_rn(uint8_t res);
void Receive_Message(uint8_t res);
///////////////////////////////////
void Send_Order_RST(void) ;
void Send_Restore(void) ;
void Send_CLOSE_TCP_UDP(void)  ;
void Send_WiFi_Mode(uint8_t number) ;
void Send_Break_Connect_AP(void) ;
void Send_Search_Local_MAC(void) ;
void Send_Search_Connect_AP(void) ;
void Send_Passthrough(uint8_t number)  ;
void Send_Data_Passthrough(void) ;
void Send_Set_Connect_TCP(void) ;
void Send_Start_Airkiss(uint8_t Number);
void Send_Stop_Airkiss(void) ;
void Clean_Buffer(uint8_t num) ;


#endif

