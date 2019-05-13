#ifndef __JSON_H_
#define __JSON_H_

//JSON 校验函数
char json_check(char *str);
//JSON 获取键值函数
char json_get_value(char *json, char *json_key, char *json_value);
//JSON 键值对比函数
char json_check_value(char *str1, char *str2);

void send_data_user(char *id,char *cmd,float adcx) ;
#endif


