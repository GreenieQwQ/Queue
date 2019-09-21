#ifndef MULTI_H
#define MULTI_H

#include "single-queue.h"

class multiQueueManager: public singleQueueManager
{
public:
    multiQueueManager(int t): singleQueueManager(t) {} //继承单队列
    void processing(); //往下一个时间单位
    bool empty() const;//判断是否仍有顾客
protected:
    vector< queue<customer> > windowsQueue{WINDOWS_NUM};//每个窗口前的队列
    int realSize(int index) const; //返回下标为index的窗口队列的真实长度    
    void enqueue(); //重载入队函数 较之前多了给五个窗口的队伍分配顾客的操作
    void dispCurrentNum() const; // 重载打印目前等待顾客的人数 细化到每个窗口的队伍
};

int multiQueueManager::realSize(int index) const
{
    if(windows[index].empty())
        return windowsQueue[index].size() -1;
    else
        return windowsQueue[index].size();
     //若窗口空闲 则窗口队伍的真实长度减一
}

bool multiQueueManager::empty() const
{
    for (int i = 0; i < windows_num; i++)//判断窗口和其队伍是否有顾客
    {
        if(!windows[i].empty())
            return false;
        if(!windowsQueue[i].empty())
            return false;
    }

    return true;
}

void multiQueueManager::enqueue()
{
    singleQueueManager::enqueue();
    while(!customerQueue.empty())//将总顾客队列的顾客插入五个窗口的最短队列中
    {
        int minIndex = 0;
        for (int i = 1; i < windows_num; i++)
        {
            if(realSize(i) < realSize(minIndex))
                minIndex = i;
        }
        //通过比较法得到最短队列的索引

        windowsQueue[minIndex].push(customerQueue.front());
        customerQueue.pop();
    }
}

void multiQueueManager::dispCurrentNum() const
{
    int totalCount = 0; //目前总共等待人数
    
    dispHeader("目前每个窗口前等待顾客人数");
    dispWindowsName();
    for( int i = 0; i < windows_num; ++i)
    {
        cout << setw(6) << windowsQueue[i].size(); //打印每个窗口前等待的顾客人数
        totalCount +=  windowsQueue[i].size();
    }
    
    dispHeader("目前等待顾客人数");
    dispData(totalCount, "men");
}

void multiQueueManager::processing() //处理方法和single的大致相同 只是总队列换为窗口前队列而已
{
    enqueue();
    for (int i = 0; i < windows_num; i++)
    {
        if(windows[i].empty())//若窗口为空
        {
            if(!windowsQueue[i].empty())//若顾客队列仍有人排队 将队头顾客安排 
            {
                windowsQueue[i].front().setWaitingTime( getWaitingTime( windowsQueue[i].front() ) );
                //顾客出队时将现时间和其入队时间相减即可得到此顾客的等待时间 并将等待时间记录
                windows[i].loadCustomer(windowsQueue[i].front());//安排
                customerOut.push_back(windowsQueue[i].front()); //此顾客属于服务完毕的顾客
                totalWaitingTime += getWaitingTime(windowsQueue[i].front()); //总共等待时间增加
                windowsQueue[i].pop();//此顾客出队
            }
        }
        windows[i].dealing();
    }
    timePassed++;
}

#endif 