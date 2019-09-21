请一定要在Linux环境下运行！！！因为解码方式的原因在Windows环境下中文会显示乱码，且随机函数较Linux版本下有所变化，所以请一定要在Linux环境下运行！！！（虽然模拟程序的源码中将宏由UNIX改为WINDOWS可以在Windows环境下“运行”，但是也仅仅能“运行”而已，这个程序在windows下的“运行”并不能很好地处理数据）

Linux环境下运行方法：
在终端依次输入：

g++ simulator-single.cpp

./a.out

即可开始单队列的模拟；

在终端依次输入：

g++ simulator-multi.cpp

./a.out

即可开始多队列的模拟。

认为时间单位为1s，默认模拟时间为50s，如需修改可以在simulator-single/multi.cpp中宏定义的

#define RUNNING_TIME 50

的参数50改为想要的模拟时间。

Tips:

在windows环境下也可模拟Ubuntu环境，只需在windows商店（开始菜单里有）中搜索wsl下载一个Ubuntu18.04内核（笔者开发时的版本），下载完成后在命令行中（vscode下直接在终端中）运行命令：

wsl

即可切换到linux环境
