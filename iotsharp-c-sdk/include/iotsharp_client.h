#ifndef iotsharp_CLIENT_H
#define iotsharp_CLIENT_H
/*********************************************************************************
 * 文件名称: iotsharp_client.h
 * 作   者: 麦壳饼
 * 版   本:
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define SDK_VERSION "v1.0.0"

#ifndef SDK_PLATFORM
#define SDK_PLATFORM "unknown"
#endif

#define NO_LOG_LEVL         0       //不输出日志
#define ERROR_LOG_LEVL      1       //输出错误日志
#define INFO_LOG_LEVL       2       //输出运行时日志和错误日志
#define DEBUG_LOG_LEVL      3       //输出调试日志、运行时日志和错误日志
 
#endif


