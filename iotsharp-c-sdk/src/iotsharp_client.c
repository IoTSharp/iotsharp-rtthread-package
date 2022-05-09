#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <rtthread.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME    "iotsharp"
#define DBG_LEVEL           DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>

#include "paho_mqtt.h"

#define MQTT_URI                PKG_USING_IOTSHARP_DEVICE_SERVER
#define MQTT_USERNAME           PKG_USING_IOTSHARP_DEVICE_NAME
#define MQTT_PASSWORD           PKG_USING_IOTSHARP_DEVICE_TOKEN

#define MQTT_WILLMSG            "Goodbye!"

/* define MQTT client context */
static MQTTClient client;
static int is_started = 0;

 void mqtt_sub_callback(MQTTClient *c, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt sub callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
}


 void mqtt_sub_default_callback(MQTTClient *c, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt sub default callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
}

static void mqtt_connect_callback(MQTTClient *c)
{
    LOG_D("inter mqtt_connect_callback!");

}
static void mqtt_new_sub_callback(MQTTClient *client, MessageData *msg_data)
{
    *((char *)msg_data->message->payload + msg_data->message->payloadlen) = '\0';
    LOG_D("mqtt new subscribe callback: %.*s %.*s",
               msg_data->topicName->lenstring.len,
               msg_data->topicName->lenstring.data,
               msg_data->message->payloadlen,
               (char *)msg_data->message->payload);
}

static void mqtt_online_callback(MQTTClient *c)
{
    LOG_D("inter mqtt_online_callback!");
    char _rpc_topic[200] = { 0 };
    char _attup_topic[200] = { 0 };
    sprintf(_rpc_topic, "devices/"PKG_USING_IOTSHARP_DEVICE_NAME"/rpc/request/+/+");
    sprintf(_attup_topic, "devices/"PKG_USING_IOTSHARP_DEVICE_NAME"/attributes/update/");
    paho_mqtt_subscribe(&client, QOS1, _rpc_topic, mqtt_new_sub_callback);
    paho_mqtt_subscribe(&client, QOS1, _rpc_topic, mqtt_new_sub_callback);

}

static void mqtt_offline_callback(MQTTClient *c)
{
    LOG_D("inter mqtt_offline_callback!");
    char _rpc_topic[200] = { 0 };
    char _attup_topic[200] = { 0 };
    sprintf(_rpc_topic, "devices/"PKG_USING_IOTSHARP_DEVICE_NAME"/rpc/request/+/+");
    sprintf(_attup_topic, "devices/"PKG_USING_IOTSHARP_DEVICE_NAME"/attributes/update/");
    paho_mqtt_unsubscribe(&client,   _rpc_topic);
    paho_mqtt_unsubscribe(&client,   _rpc_topic);
}

int iotsharp_start(void)
{
    /* init condata param by using MQTTPacket_connectData_initializer */
    MQTTPacket_connectData condata = MQTTPacket_connectData_initializer;
    static char cid[20] = { 0 };


    if (is_started)
    {
        LOG_E("mqtt client is already connected.");
        return -1;
    }
    /* config MQTT context param */
    {
        client.isconnected = 0;
        client.uri = MQTT_URI;

        /* generate the random client ID */
        rt_snprintf(cid, sizeof(cid), "iotsharp%d", rt_tick_get());
        /* config connect param */
        memcpy(&client.condata, &condata, sizeof(condata));
        client.condata.clientID.cstring = cid;
        client.condata.keepAliveInterval = 30;
        client.condata.cleansession = 1;
        client.condata.username.cstring = MQTT_USERNAME;
        client.condata.password.cstring = MQTT_PASSWORD;

        /* config MQTT will param. */
        client.condata.willFlag = 1;
        client.condata.will.qos = 1;
        client.condata.will.retained = 0;
        client.condata.will.topicName.cstring = "/device/me/disconnect";
        client.condata.will.message.cstring = MQTT_WILLMSG;

        /* malloc buffer. */
        client.buf_size = client.readbuf_size = 1024;
        client.buf = rt_calloc(1, client.buf_size);
        client.readbuf = rt_calloc(1, client.readbuf_size);
        if (!(client.buf && client.readbuf))
        {
            LOG_E("no memory for MQTT client buffer!");
            return -1;
        }

        /* set event callback function */
        client.connect_callback = mqtt_connect_callback;
        client.online_callback = mqtt_online_callback;
        client.offline_callback = mqtt_offline_callback;

        /* set subscribe table and event callback */
      //  client.messageHandlers[0].topicFilter = rt_strdup(MQTT_SUBTOPIC);
       //client.messageHandlers[0].callback = mqtt_sub_callback;
       // client.messageHandlers[0].qos = QOS1;

        /* set default subscribe event callback */
        client.defaultMessageHandler = mqtt_sub_default_callback;
    }

    /* run mqtt client */
    paho_mqtt_start(&client);
    is_started = 1;

    return 0;
}

 int iotsahrp_stop(void)
{
    is_started = 0;

    return paho_mqtt_stop(&client);
}


 static int mqtt_publish_for_gateway(char* subdevicename, int datatype, char *playload)
{
      char _telemetry_topic[200] = { 0 };
      char attributes_topic[200] = { 0 };
     sprintf(_telemetry_topic, "devices/%s/telemetry",subdevicename);
     sprintf(attributes_topic, "devices/%s/attributes",subdevicename);
    if (is_started == 0)
    {
        LOG_E("mqtt client is not connected.");
        return -1;
    }

    if (datatype == 1)
    {
        paho_mqtt_publish(&client, QOS1, _telemetry_topic, playload);
    }
    else if (datatype== 2)
    {
        paho_mqtt_publish(&client, QOS1, attributes_topic, playload);
    }
    else
    {
        rt_kprintf("publish message to specified datatype.\n");
        return -1;
    }
    return 0;
}
 int  iotsharp_upload_telemetry_for_gateway(char* _devname,char* playload)
 {
    return  mqtt_publish_for_gateway(_devname,1,playload);
 }
 int  iotsharp_upload_telemetry_to_device(char* playload)
 {
    return  mqtt_publish_for_gateway("me",1,playload);
 }
int  iotsharp_upload_attribute_for_gateway(char* _devname,char* playload)
{
   return  mqtt_publish_for_gateway(_devname,2,playload);
}
int  iotsharp_upload_attribute_to_device(char* playload)
{
   return  mqtt_publish_for_gateway("me",2,playload);
}



#ifdef FINSH_USING_MSH


#endif /* FINSH_USING_MSH */

