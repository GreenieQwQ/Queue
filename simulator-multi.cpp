#include "multi-queue.h"

#define UNIX //Linux版本定义宏
#ifdef UNIX
#include <unistd.h>
#elif defined WINDOWS
#include <windows.h>
#endif

#define RUNNING_TIME 50 //模拟时间

int main()
{
    multiQueueManager m; //构建一个多队列的模拟器
    int time = RUNNING_TIME; //时间设置为模拟时间
    while(time--) //用循环来模拟时间流逝
    {
        m.display(); //打印信息
        m.processing(); //每个时间单位多队列进行模拟
    #ifdef UNIX
        sleep(1);
    #elif defined WINDOWS
        Sleep(1000);
    #endif
    
    if( time != 0) //最后一秒时不清屏便于观察    
        #ifdef UNIX
            system("clear");
        #elif defined WINDOWS
            system("cls");
        #endif    
    }
}