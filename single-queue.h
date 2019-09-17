#ifndef SINGLE_H
#define SINGLE_H

#include "Queue.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
using namespace std;
#define WINDOWS_NUM 5
#define MAX_RAND 15

class singleQueueManager
{
public:
    static const int windows_num = WINDOWS_NUM;
    static const int max_rand = MAX_RAND;
public:
    singleQueueManager(): totalDealedCustomerNumber(0)
    {
        enqueue();//入队随机人数
    }
    void processing();//往下一个时间单位
    void display() const;//打印信息    

private:
    vector<window> windows[windows_num]; //windows_num个窗口
    queue<customer> customerQueue;//顾客队列
    int totalDealedCustomerNumber; //总共服务顾客的人数
    void enqueue(); //入队随机人数 
    void dispSequence() const; //打印顺序号
    void dispCurrentNum() const; // 打印目前等待顾客的人数
    void dispWaitingTime() const; //打印每个顾客可得到服务之前的等待时间单位数
    void dispResult() const; //打印顾客等待平均时间数，每个窗口处理的顾客数
};

void singleQueueManager::enqueue()
{
    srand(time(NULL));
    int enqueueNum = rand() % MAX_RAND + 1;
    while(enqueueNum--) //入队enqueueNum个顾客 并分配编号
        customerQueue.push(customer(++totalDealedCustomerNumber));
}

void singleQueueManager::display() const
{
    dispSequence();
    dispCurrentNum();
    dispWaitingTime();
    dispResult();
}

#endif