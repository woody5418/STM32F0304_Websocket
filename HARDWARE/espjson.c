#include "espjson.h"
#include "USART1.h"
#include "string.h"


uint8_t Flag_Start = 0;   //特殊接收方式
char *STATMAC = ""; //存储的mac地址
uint8_t mess[15]; //校验数组
uint8_t MAC_CACHE[19]; // mac地址存储

void Receive_Message_airkiss_callback(void)
{
    int air_length = 2;
    uint8_t t;

    if (USART_RX_STA & 0x8000)
    {
        for (t = 0; t < 15; t++)
        {
            mess[t] = USART_RX_BUF[t];
        }
        USART_Cmd(USART1, DISABLE);
        Clean_Buffer(25);
        USART_RX_STA = 0;
        flag_0D = flag_0A = 0;
        // 不相等air_length = 0xFFFFFFE4
        air_length = strcmp("WIFI CONNECTED", (char *) mess);
        if (air_length == 0xFFFFFFDE)
            Return_OK = 7;
        else
        {
            air_length = strcmp("WIFI DISCONNECT", (char *) mess);
            if (air_length == 0xFFFFFFDE)
                Return_OK = 8;
            else
            {
                air_length = strcmp("WIFI GOT IP", (char *) mess);
                if (air_length == 0xFFFFFFDE)
                    Return_OK = 9;
                else
                {
                    //0xFFFFFFDE
                    air_length = strcmp("smartconfig con", (char *) mess);
                    if (air_length == 0xFFFFFFDE)
                        Return_OK = 10;
                    else
                        Return_OK = 6;
                }
            }
        }
        for (t = 0; t < 15; t++)
        {
            if (mess[t] != 0)
            {
                mess[t] = 0;
            }
            else
                continue;
        }
        USART_Cmd(USART1, ENABLE);
    }
}



void Reveive_Message_callback(void)
{
    uint8_t t;

    if (USART_RX_STA & 0x8000)
    {
        for (t = 0; t < 15; t++)
        {
            mess[t] = USART_RX_BUF[t];
        }
        Clean_Buffer(25);
        USART_RX_STA = 0;
        flag_0D = flag_0A = 0;

        if ((mess[0] == 'O') && (mess[1] == 'K')) Return_OK = 1;
        else if ((mess[0] == 'E') && (mess[1] == 'R') && (mess[2] == 'R')
                 && (mess[3] == 'O') && (mess[4] == 'R')) Return_OK = 2;
        else if ((mess[0] == 'F') && (mess[1] == 'A') && (mess[2] == 'I')
                 && (mess[3] == 'L')) Return_OK = 3;
        else if ((mess[0] == '+') && (mess[1] == 'C') && (mess[2] == 'W')
                 && (mess[3] == 'J') && (mess[4] == 'A')
                 && (mess[5] == 'P')) Return_OK = 4;
        else if ((mess[0] == 0X4E) && (mess[1] == 0X6F) && (mess[2] == 0X20)
                 && (mess[3] == 0X41) && (mess[4] == 0X50)) //No Ap
            Return_OK = 5;
        else
            Return_OK = 6;
        for (t = 0; t < 15; t++)
        {
            if (mess[t] != 0)
            {
                mess[t] = 0;
            }
            else
                continue;
        }
    }
}

void Receive_MAC_Callback(void)
{
    uint8_t t;

    if (USART_RX_STA & 0x8000)
    {
        for (t = 0; t < 19; t++)
        {
            MAC_CACHE[t] = USART_RX_BUF[t + 14];
        }
        Clean_Buffer(35);
        USART_RX_STA = 0;
        flag_0D = flag_0A = 0;
        STATMAC = (char *) MAC_CACHE;
        if (STATMAC)
        {
            Return_OK = 1;
        }
        else
            Return_OK = 2;
    }
}

//接收OK跟其他的信息0D0D00AXX0D0A 或其他
void Receive_OK_Callback(uint8_t res, uint8_t flgd, uint8_t flga)
{
    if ((flag_0D < flgd) || (flag_0A < flga))
    {
        if (res == 0X0D) flag_0D += 1;
        if (res == 0X0A) flag_0A += 1;
    }
    else
    {
        if ((flag_0D == flgd) && (flag_0A == flga))
        {
            if ((USART_RX_STA & 0x8000) == 0)
            {
                if (USART_RX_STA & 0x4000)
                {
                    if (res != 0x0a) USART_RX_STA = 0;
                    else
                    {
                        FLAG_RXD_FH_MODE = 0;
                        USART_RX_STA |= 0x8000;
                    }
                }
                else
                {
                    if (res == 0x0d)
                        USART_RX_STA |= 0x4000;
                    else
                    {
                        USART_RX_BUF[USART_RX_STA & 0X3FFF] = res;
                        USART_RX_STA++;
                        if (USART_RX_STA > (USART_REC_LEN - 1))
                            USART_RX_STA =0;
                    }
                }
            }
        }
        else
        {
            Return_OK = 0;
            flag_0A = flag_0D = 0;
            FLAG_RXD_FH_MODE = 3;
            USART_RX_STA |= 0x8000;
        }
    }
}
//接收以0X0D 0X0A结尾的数据
void Receive_Message(uint8_t res)
{
    if ((USART_RX_STA & 0x8000) == 0)
    {

        if (res == 0x0a) USART_RX_STA |= 0x8000;
        else
        {
            USART_RX_BUF[USART_RX_STA & 0X3FFF] = res;
            USART_RX_STA++;
            if (USART_RX_STA > (USART_REC_LEN - 1)) USART_RX_STA = 0;
        }
    }
}

void Send_Order_RST(void)
{
    printf("AT+RST\r\n");
}
void Send_CLOSE_TCP_UDP(void)
{
    printf("AT+CIPCLOSE\r\n");
}
void Send_WiFi_Mode(uint8_t number)
{
    printf("AT+CWMODE_DEF=%d\r\n", number);
}
void Send_Break_Connect_AP(void)
{
    printf("AT+CWQAP\r\n");
}
void Send_Search_Local_MAC(void)
{
    printf("AT+CIFSR\r\n");
}
void Send_Search_Connect_AP(void)
{
    printf("AT+CWJAP?\r\n");
}
void Send_Passthrough(uint8_t number)
{
    printf("AT+CIPMODE=%d\r\n", number);
}
void Send_Data_Passthrough(void)
{
    printf("AT+CIPSEND\r\n");
}
void Send_Set_Connect_TCP(void)
{
    printf("AT+CIPSTART=\"TCP\",\"60.205.107.115\",17895\r\n");
}
void Send_Start_Airkiss(uint8_t Number)
{
    printf("AT+CWSTARTSMART=%d\r\n", Number);
}
void Send_Stop_Airkiss(void)
{
    printf("AT+CWSTOPSMART\r\n");
}

void Clean_Buffer(uint8_t num)
{
    uint8_t i;
    for (i = 0; i < num; i++)
    {
        if (USART_RX_BUF[i] != 0)
        {
            USART_RX_BUF[i] = 0;
        }
        else
            continue;
    }
}


