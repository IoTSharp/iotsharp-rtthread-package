#include <stdio.h>
#include <time.h>
#include <string.h>
#ifdef PKG_USING_IOTSHARP_SERVER
    #define DEVICE_SERVER           PKG_USING_IOTSHARP_DEVICE_SERVER
#else
    #define DEVICE_SERVER           ""
#endif
 

#ifdef PKG_USING_IOTSHARP_DEVICE_NAME
    #define DEVICE_NAME             PKG_USING_IOTSHARP_DEVICE_NAME
#else
    #define DEVICE_NAME             ""
#endif

#ifdef PKG_USING_IOTSHARP_DEVICE_TOKEN
    #define DEVICE_TOKEN           PKG_USING_IOTSHARP_DEVICE_TOKEN
#else
    #define DEVICE_TOKEN           ""
#endif
 
 

#ifdef PKG_USING_IOTSHARP-C-SDK
#include <finsh.h>

MSH_CMD_EXPORT_ALIAS(start_demo_test, start_demo_test,Example: start_demo_test);
#endif

