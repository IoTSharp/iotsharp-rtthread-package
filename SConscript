Import('RTT_ROOT')
from building import *

# get current directory
cwd = GetCurrentDir()

# The set of source files associated with this SConscript file.
src = []
path = []

src += Glob('iotsharp-c-sdk/src/jclient/*.c')
src += Glob('iotsharp-c-sdk/src/sisclient/*.c')
src += Glob('iotsharp-c-sdk/src/mqtt/MQTTClient-C/src/*.c')
src += Glob('iotsharp-c-sdk/src/mqtt/MQTTPacket/src/*.c')
src += Glob('iotsharp-c-sdk/common/*.c')
src += Glob('iotsharp-c-sdk/public/net/tcp/*.c')
src += Glob('iotsharp-c-sdk/platform/os/rt-thread/*.c')

path += [cwd + '/iotsharp-c-sdk/common']
path += [cwd + '/iotsharp-c-sdk/include/jclient']
path += [cwd + '/iotsharp-c-sdk/include/mqtt']
path += [cwd + '/iotsharp-c-sdk/include/sisclient']
path += [cwd + '/iotsharp-c-sdk/platform/os/rt-thread']
path += [cwd + '/iotsharp-c-sdk/src/mqtt/MQTTPacket/src']
path += [cwd + '/iotsharp-c-sdk/public/net/tcp']

if GetDepend(['PKG_USING_IOTSHARP_EXAMPLES']):
	src += Glob('samples/*.c')
	
 
	
group = DefineGroup('iotsharp-c-sdk', src, depend = [''], CPPPATH = path)

Return('group')
