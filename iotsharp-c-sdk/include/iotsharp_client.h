#ifndef IOTSHARP_CLIENT_H
#define IOTSHARP_CLIENT_H
/*********************************************************************************
 * �ļ�����: iotsharp_client.h
 * ��   ��: ��Ǳ�
 * ��   ��:
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define SDK_VERSION "v1.0.0"

#ifndef SDK_PLATFORM
#define SDK_PLATFORM "unknown"
#endif

#define NO_LOG_LEVL         0       //�������־
#define ERROR_LOG_LEVL      1       //���������־
#define INFO_LOG_LEVL       2       //�������ʱ��־�ʹ�����־
#define DEBUG_LOG_LEVL      3       //���������־������ʱ��־�ʹ�����־
#define DATATYPE_LOG_LEVL      3       //���������־������ʱ��־�ʹ�����־
#define DEBUG_LOG_LEVL      3       //���������־������ʱ��־�ʹ�����־

int iotsharp_start(void);
int iotsharp_stop(void);
int  iotsharp_upload_telemetry_for_gateway(char* _devname,char* playload);//����������Ϊ���豸�ϴ�ң�����ݡ�
int  iotsharp_upload_telemetry_to_device(char* playload);//�ϴ�ң������
int  iotsharp_upload_attribute_for_gateway(char* _devname,char* playload);//����������Ϊ���豸�ϴ���������
int  iotsharp_upload_attribute_to_device(char* playload);//�ϴ�����

#endif


