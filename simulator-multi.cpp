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
    multiQueueManager m;
    int time = RUNNING_TIME;
    while(time--)
    {
        m.display();
        m.processing();
    #ifdef UNIX
        sleep(1);
    #elif defined WINDOWS
        Sleep(1000);
    #endif
    
    if( time != 0) //不清空最后的结果    
        #ifdef UNIX
            system("clear");
        #elif defined WINDOWS
            system("cls");
        #endif    
    }
}