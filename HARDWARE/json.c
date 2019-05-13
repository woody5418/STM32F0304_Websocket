#include "json.h"
#include "string.h"
#include "USART1.h"

/***************************************
 name:       JSON У�麯��
 input:      �ַ���
 output:     �Ϸ�JAON ����1 ���Ϸ�JSON ����0
 description:
 ***************************************/
char json_check(char *str)
{
    //�����ַ����ȱ���
    char str_length;
    //�����ַ�����
    str_length = strlen(str);
    //ͨ����β�������ж��Ƿ�ΪJSON
    if (str[0] == '{' && str[str_length - 1] == '}')
    {
        //����ַ���Ϊ�Ϸ�JSON ����1
        return 1;
    }
    else
    {
        //����ַ���Ϊ�Ϸ�JSON ����0
        return 0;
    }
}

/***************************************
 name:       JSON ��ȡ��ֵ����
 input:      JSON�ַ��� Ҫ��ȡ�ļ��� ��ȡ��ֵ���ַ���
 output:     �����ȡ�ɹ�����1 ��ȡʧ�ܷ���0
 description:
 ***************************************/
char json_get_value(char *json, char *json_key, char *json_value)
{
    //���������ʼ��λ��
    char *json_key_start;
    //�������������λ��
    char *json_key_end;
    //�����������
    char json_key_length;
    //�����ֵ��ʼ��λ��
    char *json_value_start;
    //�����ֵ������λ��
    char *json_value_end;
    //�����ֵ����
    char json_value_length;
    //��ȡ������ʼ��λ��
    json_key_start = strstr(json, json_key);
    //��ȡ�����ĳ���
    json_key_length = strlen(json_key);
    //��ȡ����������λ��
    json_key_end = json_key_start + json_key_length;

    if (json_key_start != 0 && *(json_key_start - 1) == '\"'
            && *(json_key_end) == '\"' && *(json_key_end + 1) == ':'
            && *(json_key_end + 2) == '\"')
    {
        //��ȡ��ֵ��ʼ��λ��
        json_value_start = json_key_end + 3;
        //��ȡ��ֵ������λ��
        json_value_end = strstr(json_value_start, "\"");
        //��ȡ��ֵ�ĳ���
        json_value_length = json_value_end - json_value_start;
        //����ֵ����ָ������
        strncpy(json_value, json_value_start, json_value_length);
        //ָ�����һλ���ַ��������� \0
        json_value[json_value_length] = '\0';
        //�ɹ���ȡ��ֵ ����1
        return 1;
    }
    else
    {
        json_value[0] = '\0';
        //ʧ�ܻ�ȡ��ֵ ����0
        return 0;
    }
}

/***************************************
 name:       JSON ��ֵ�ԱȺ���
 input:      JSON ��ֵ Ҫƥ����ַ�
 output:     ���ƥ��ɹ�����1 ʧ�ܷ���0
 description:
 ***************************************/
char json_check_value(char *str1, char *str2)
{
    if (strcmp(str1, str2) == 0)
    {
        //ƥ��ɹ�����1
        return 1;
    }
    else
    {
        //ƥ��ɹ�����0
        return 0;
    }
}

/*
  ������id ΪLocal MAC
        cmd Ϊ����
		 adcxΪADCֵ
  */
void send_data_user(char *id,char *cmd,float adcx)
{
    printf("{\"id\":%s,\"to\":\"user\",\"cmd\":\"%s\",\"adc\":\"%f\"}\r\n",id,cmd,adcx);
}


