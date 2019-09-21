#include "multi-queue.h"

#define UNIX //Linux版本定义宏
#ifdef UNIX
#include <unistd.h>
#elif defined WINDOWS
#include <windows.h>
#endif

#define RUNNING_TIME 40 //默认营业时间

int main()
{
    int time = RUNNING_TIME;
    int tt = 0;
    multiQueueManager m(time); //构建一个单队列的模拟器
    while( (time--) > 0 || !m.empty()) //当经过营业时间且没有顾客时停止循环
    {
        m.display(); //打印信息
        m.processing(); //每个时间单位单队列进行模拟
    
    #ifdef UNIX //系统一秒运行依次
        sleep(1);
    #elif defined WINDOWS
        Sleep(1000);
    #endif
    
    #ifdef UNIX
        system("clear"); //清屏便于观察
    #elif defined WINDOWS
        system("cls");
    #endif    
    tt++;
    } //用循环来模拟时间流逝
    m.display(); //打印最终结果
    cout << tt <<endl;
}