#include "single-queue.h"

#define UNIX //Linux版本定义宏
#ifdef UNIX
#include <unistd.h>
#elif defined WINDOWS
#include <windows.h>
#include
#endif

#define RUNNING_TIME 50

int main()
{
    singleQueueManager m;
    m.display();
    int time = RUNNING_TIME;
    while(time--)
    {
        if(time != RUNNING_TIME)
        m.display();
        m.processing();
    #ifdef UNIX
        sleep(1);
    #elif defined WINDOWS
        Sleep(1000);
    #endif    
        system("clear");
    }
}