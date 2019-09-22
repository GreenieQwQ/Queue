#ifndef SINGLE_H
#define SINGLE_H

#include "customer.h"
#include "window.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;
#define WINDOWS_NUM 5
#define MAX_CUSTOMER_NUM 2.2 //高峰期的顾客流量
#define PRECISION 100000 //概率计算的精度


class singleQueueManager
{
public:
    static const int windows_num = WINDOWS_NUM;
public:
    singleQueueManager(int t): totalCustomerNumber(0), totalWaitingTime(0), timePassed(0), runnning_time(t)
    {
        // init(); //给队伍预载人数
    }
    void processing();//往下一个时间单位
    void display() const;//打印信息
    bool empty() const; //判断是否还有顾客

protected:
    vector<window> windows{windows_num}; //windows_num个窗口
    queue<customer> customerQueue;//顾客队列
    vector<customer> customerOut; //出队的顾客
    int totalCustomerNumber; //总共入队顾客的人数
    double totalWaitingTime; //顾客等待的时间数的和
    int timePassed; //从开始模拟到现在经过的时间
    int runnning_time; //营业的时间

    int getWaitingTime(const customer&) const;// 计算顾客等待的时间
    void init(); //初始化顾客队列
    void enqueue(); //入队随机人数
    void dequeue(); //给顾客服务
    void addWaitingRecord(const customer&); //增加一条顾客等待时间的记录
    virtual void dispSequence() const; //打印顺序号 用虚函数便于子类重载调用时display不需重写
    virtual void dispCurrentNum() const; // 打印目前等待顾客的人数
    virtual void dispWaitingTime() const; //打印每个顾客可得到服务之前的等待时间单位数
    virtual void dispResult() const; //打印顾客等待平均时间数，每个窗口处理的顾客数
    virtual void dispTime() const; //打印模拟系统运行的时间
    void dispHeader(const string&) const; //打印题头
    void dispData(int, const string&) const; //打印一行int型数据
    void dispData(double, const string&) const; //打印一行double型数据
    void dispWindowsName() const; //打印窗口名
    double factorial(int k) const; //返回k的阶乘
    double distribute(int time) const; //返回对应时间下的先验顾客流量
    double poisson(int k, int lambda) const; //泊松分布对应k的值
};

double singleQueueManager::factorial(int k) const
{
    double result = 1;
    for (int i = 1; i <= k; i++)
    {
        result *= i;
    }
    return result;
}

double singleQueueManager::poisson(int k, int lamda) const
{
    return pow(lamda,k) * exp(-lamda) / factorial(k); //由公式计算
}

double singleQueueManager::distribute(int time) const
{
    double a = (double) 4 * MAX_CUSTOMER_NUM / (runnning_time * runnning_time); //获得近似二次函数的系数
    double result = - a * (time - runnning_time) * time; //根据-ax(x-t)公式计算得到先验流量
    return result;
}

void singleQueueManager::enqueue()
{
    srand(time(NULL));
    int possibility = rand() % PRECISION; 
    //用均匀分布possibility落入的区间模拟概率
    double area = 0; 
    //分布函数 X <= k 的区间
    double lambda = distribute(timePassed);
    //获得对应时间下的先验顾客流量

    for (int i = 0; ; i++)
    {
        area += poisson(i,lambda) * PRECISION; //区间扩张
        if(possibility < area) //用均匀分布的区间模拟概率
        {
            while(i--) //入队i个顾客 并分配编号 
                customerQueue.push(customer(++totalCustomerNumber, timePassed)); //分配编号为加上这个顾客总共入队顾客的人数
            return;
        }
    }
}

void singleQueueManager::init()
{
    int enqueueNum = 10; //初始队列人数
    while(enqueueNum--)
        customerQueue.push(customer(++totalCustomerNumber)); //分配编号为加上这个顾客总共入队顾客的人数
}

void singleQueueManager::display() const
{
    dispSequence();
    dispCurrentNum();
    dispWaitingTime();
    dispResult();
    dispTime();
    cout << endl;
    cout << setfill('=') << setw(windows_num * 6  ) << '=' << endl;
    cout << endl;
}


void singleQueueManager::dispHeader(const string& head) const
{
    cout << endl;
    cout << setfill('=') << setw(windows_num * 6 ) << '=' << endl;
    cout << setfill(' ') << setw(windows_num * 6 - head.size() / 2) << head << endl; //居中打印
    cout << setfill('=') << setw(windows_num * 6 ) << '=' << endl;//打印题头
}

void singleQueueManager::dispData(int data, const string& str) const
{
    cout << setfill(' ') << setw(windows_num * 2 + 1) //打印int型数据的格式
    << data << "   " << str;
}

void singleQueueManager::dispData(double data, const string& str) const //打印double型数据的格式
{
    cout << setfill(' ') << setw(windows_num * 2 + 1) 
    << fixed << setprecision(2) << data << "   " << str;
}

void singleQueueManager::dispWindowsName() const
{
    for( int i = 0; i < windows_num; ++i)
        cout << setfill(' ') << setw(6) << (char)('A' + i); //打印窗口名
    cout << endl;
}

void singleQueueManager::dispSequence() const
{
    dispHeader("窗口正在办理的顾客顺序号"); //打印的为此时间单位结束时的结果
    dispWindowsName(); //打印窗口名

    for( int i = 0; i < windows_num; ++i)
    {
        if(!windows[i].empty())//若正在服务
            cout << setw(6) << windows[i].getId(); //打印正在服务的对象 
        else
            cout << setw(6) << "Free"; //打印空闲
    }

}

void singleQueueManager::dispCurrentNum() const
{
    dispHeader("目前等待顾客人数");

    dispData((int)customerQueue.size(), "men"); //打印的为整型数据
}

int singleQueueManager::getWaitingTime(const customer& c) const
{
    return timePassed - c.getEnqueueTime();
}

void singleQueueManager::dispWaitingTime() const
{
    dispHeader("每个顾客得到服务前的等待时间单位数");
    cout << setfill(' ') << setw(10) << "Customer" << setw(10) << "Time";  
    
    #define colunm 4 //定义打印的列数
    for (int i = 0; i < colunm - 1; i++)
        cout << setfill(' ') << setw(3) << "|" << setw(12) << "Customer" << setw(10) << "Time"; //打印表头
    
    

    if(customerOut.size() == 0)//还未有人出队
    {
        cout << endl;
        cout << setfill('-') << setw(18) << "No data" << setw(12) << '-';
        return;
    }
    
    
    for(int i = 0; i < customerOut.size(); i++)
    {
        cout << endl;
        cout << setw(10) << customerOut[i].getId() 
        << setw(10) << customerOut[i].getWaitingTime();  //打印记录
        
        for (int j = 0; j < colunm - 1; j++)
        {
            if(i != customerOut.size()-1)
            cout << setw(3) << "|" << setw(12) << customerOut[++i].getId() 
            << setw(10) << customerOut[i].getWaitingTime();
        }
    }
        
}

void singleQueueManager::dispResult() const
{
    dispHeader("顾客等待平均时间数");
    if(customerOut.size() == 0) //还未有人出队
        cout  << setfill('-') << setw(18) << "No data" << setw(12) << '-';
    else
        dispData(totalWaitingTime/ customerOut.size(), "seconds"); //打印时间
    
    dispHeader("每个窗口处理顾客数"); 
    dispWindowsName();
    for( int i = 0; i < windows_num; ++i)
        cout << setw(6) << windows[i].getNumber(); //打印处理数 
}

void  singleQueueManager::dispTime() const
{
    dispHeader("模拟系统运行的时间");
    dispData((int)timePassed, "seconds");
}

void singleQueueManager::processing()
{
    if(timePassed <= runnning_time) //若经过的时间小于营业时间
        enqueue(); //入队随机人数
    
    for (int i = 0; i < windows_num; i++)
    {
        if(windows[i].empty())//若窗口为空
        {
            if(!customerQueue.empty())//若顾客队列仍有人排队 将队头顾客安排
            {
                customerQueue.front().setWaitingTime( getWaitingTime( customerQueue.front() ) );
                //顾客出队时将现时间和其入队时间相减即可得到此顾客的等待时间 并将等待时间记录
                windows[i].loadCustomer(customerQueue.front());//安排
                customerOut.push_back(customerQueue.front()); //此顾客属于服务完毕的顾客
                totalWaitingTime += getWaitingTime(customerQueue.front()); //总共等待时间增加
                customerQueue.pop();//此顾客出队
            }
        }
        windows[i].dealing(); //剩余服务时间减一
    }
    timePassed++; //总模拟时间加一    
}

bool singleQueueManager::empty() const
{
    for (int i = 0; i < windows_num; i++)//判断窗口是否有顾客
    {
        if(!windows[i].empty())
            return false;
    }

    return customerQueue.empty(); //若顾客队伍也没有顾客则空
}

#endif