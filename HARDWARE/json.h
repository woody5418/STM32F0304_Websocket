#ifndef __JSON_H_
#define __JSON_H_

//JSON У�麯��
char json_check(char *str);
//JSON ��ȡ��ֵ����
char json_get_value(char *json, char *json_key, char *json_value);
//JSON ��ֵ�ԱȺ���
char json_check_value(char *str1, char *str2);

void send_data_user(char *id,char *cmd,float adcx) ;
#endif


