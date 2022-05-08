# IoTSharp for RTthread Package

## 1 介绍 

IoTSharp 是一个 基于.Net Core 开源的物联网基础平台， 支持 HTTP、MQTT 、CoAp 协议， 属性数据和遥测数据协议简单类型丰富，简单设置即可将数据存储在PostgreSql、MySql、Oracle、SQLServer、Sqlite，是一个用于数据收集、处理、可视化与设备管理的 IoT 平台.

### 1.1 目录结构

| 名称            | 说明 |
| ----            | ---- |
| jiot-c-sdk | sdk源码目录 |
| docs            | 文档目录 |
| samples  | 示例文件目录 |
| LICENSE    | 许可证文件 |
| README.md | 软件包使用说明 |
| SConscript | RT-Thread 默认的构建脚本 |

### 1.2 SDK接口说明

[IoTSharp C SDK 接口文档](https://docs.iotsharp.net/client/c_sdk_api/)

### 1.3 许可证

MIT License 协议许可。

## 2 获取软件包

使用 `iotsharp-c-sdk` 软件包使用 menuconfig 命令打开 Env 配置界面，在 `RT-Thread online packages → IoT - internet of things → IoT Cloud` 中选择 iotsharp-c-sdk 软件包，操作界面如下图所示：

![选中 iotsharp-c-sdk 软件包](https://github.com/IoTSharp/iotsharp-rtthread-package/blob/master/docs/figures/select_iotsharp_c_sdk.png?raw=true)
![配置 iotsharp-c-sdk 软件包](https://github.com/IoTSharp/iotsharp-rtthread-package/blob/master/docs/figures/cibfug_iotsharp_c_sdk.png?raw=true)
选择合适的配置项后，使用 `pkgs --update` 命令下载软件包并添加到工程中即可。

