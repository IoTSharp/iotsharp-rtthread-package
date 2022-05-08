Import('RTT_ROOT')
from building import *

# get current directory
cwd = GetCurrentDir()

# The set of source files associated with this SConscript file.
src = []
path = []

src += Glob('iotsharp-c-sdk/src/*.c')


path += [cwd + '/iotsharp-c-sdk/include']
path += [cwd + '/iotsharp-c-sdk/src']


if GetDepend(['PKG_USING_IOTSHARP_EXAMPLES']):
	src += Glob('samples/*.c')
	
 
	
group = DefineGroup('iotsharp-c-sdk', src, depend = [''], CPPPATH = path)

Return('group')
