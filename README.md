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

关于模拟的假设：  
认为时间单位为1s，默认营业时间为50s，如需修改可以在simulator-single/multi.cpp中宏定义的  
#define RUNNING_TIME 40    
将参数40改为想要的营业时间。  

假设在开始服务前无人排队，顾客服务时间服从2-6秒的均匀分布，顾客流量的分析见实验报告。  

每秒屏幕上输出的信息为此时间单位结束时的统计信息，因此窗口显示Free但是还有顾客在排队并不为逻辑错误，表示这个时间单位结束时此窗口刚好处理完上个时间单位仍在处理的顾客。  
强烈推荐将窗口放大一点，便于观察，按F11全屏观看更佳。  
模拟在营业时间后且顾客全部服务完毕的时间停止，按照默认设置模拟时间约为1分钟。

Tips:  
在windows环境下也可模拟Ubuntu环境，只需在windows商店（开始菜单里有）中搜索wsl下载一个Ubuntu18.04内核（笔者开发时使用的版本），下载完成后在命令行中（vscode下直接在终端中）运行命令：    
wsl    
即可切换到linux环境
