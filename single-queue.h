#ifndef SINGLE_H
#define SINGLE_H

#include "Queue.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define WINDOWS_NUM 5
#define MAX_RAND 20

class singleQueueManager
{
public:
    static const int windows_num = WINDOWS_NUM;
    static const int max_rand = MAX_RAND;
public:
    singleQueueManager(): totalCustomerNumber(0)
    {
        enqueue();//入队随机人数
    }
    void processing();//往下一个时间单位
    void display() const;//打印信息

private:
    vector<window> windows{windows_num}; //windows_num个窗口
    queue<customer> customerQueue;//顾客队列
    vector<customer> customerOut; //服务完毕的顾客
    int totalCustomerNumber; //总共入队顾客的人数
    int totalWaitingTime; //顾客等待的时间数的和
    void enqueue(); //入队随机人数
    void addWaitingRecord(const customer&); //增加一条顾客等待时间的记录
    void dispSequence() const; //打印顺序号
    void dispCurrentNum() const; // 打印目前等待顾客的人数
    void dispWaitingTime() const; //打印每个顾客可得到服务之前的等待时间单位数
    void dispResult() const; //打印顾客等待平均时间数，每个窗口处理的顾客数
    void dispHeader(const string&) const; //打印题头
    void dispData(int, const string&) const; //打印数据（一行）
};

void singleQueueManager::enqueue()
{
    srand(time(NULL));
    int enqueueNum = rand() % MAX_RAND + 1;
    while(enqueueNum--) //入队enqueueNum个顾客 并分配编号
        customerQueue.push(customer(++totalCustomerNumber)); //分配编号为加上这个顾客总共入队顾客的人数
}

void singleQueueManager::display() const
{
    dispSequence();
    dispCurrentNum();
    dispWaitingTime();
    dispResult();
    cout << setfill('=') << setw(windows_num * 4 ) << '=' << endl;
}


void singleQueueManager::dispHeader(const string& head) const
{
    cout << setfill('=') << setw(windows_num * 4 ) << '=' << endl;
    cout << setfill(' ') << setw(windows_num * 2 + head.size() / 2) << head << endl; //居中打印
    cout << setfill('=') << setw(windows_num * 4 ) << '=' << endl;//打印题头
}

void singleQueueManager::dispData(int data, const string& str) const
{
    cout << setfill(' ') << setw(windows_num * 2) 
    << data << str  <<endl;
}

void singleQueueManager::dispSequence() const
{
    dispHeader("窗口正在办理的顾客顺序号");
    
    for( int i = 0; i < windows_num; ++i)
        cout << setfill(' ') << setw(4) << ('A' + i); //打印窗口名
    cout << endl;

    for( int i = 0; i < windows_num; ++i)
    {
        if(!windows[i].empty())//若正在服务
            cout << setw(4) << windows[i].getId(); //打印正在服务的对象 
        else
            cout << setw(4) << "Free"; //打印空闲
    }

}

void singleQueueManager::dispCurrentNum() const
{
    dispHeader("目前等待顾客人数");

    dispData(customerQueue.size(), "men");
}

void singleQueueManager::dispWaitingTime() const
{
    dispHeader("每个顾客得到服务前的等待时间单位数");
    cout << setfill(' ') << setw(10) << "Customer" << setw(10) << "Time" << endl;  
    
    if(customerOut.size() == 0)//还未有人出队
        cout << setfill('-') << setw(10) << "No data" << setw(10) << '-' << endl;
    
    for(int i = 0; i < customerOut.size(); i++)
        cout << setw(10) << customerOut[i].getId() 
        << setw(10) << customerOut[i].getWaitingTime() << endl;   //打印记录
}

void singleQueueManager::dispResult() const
{
    dispHeader("顾客等待平均时间数");
    dispData((double)totalWaitingTime/ customerOut.size(), "second");
    dispHeader("每个窗口处理顾客数"); 
    for( int i = 0; i < windows_num; ++i)
        cout << setfill(' ') << setw(4) << ('A' + i); //打印窗口名
    cout << endl; 
    for( int i = 0; i < windows_num; ++i)
        cout << setw(4) << windows[i].getNumber(); //打印处理数 
}

void singleQueueManager::processing()
{
    //enqueue();

    for (int i = 0; i < windows_num; i++)
    {
        if(windows[i].empty())//若窗口为空
        {
            if(!customerQueue.empty())//若顾客队列仍有人排队 将队头顾客安排
            {
                windows[i].loadCustomer(customerQueue.front());
                customerOut.push_back(customerQueue.front()); //此顾客属于服务完毕的顾客
                totalWaitingTime += customerQueue.front().getWaitingTime(); //总共等待时间增加
                customerQueue.pop();//此顾客出队
            }
        }

        windows[i].dealing();
    }
    
}

#endif