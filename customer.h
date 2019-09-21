#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <cstdlib>
#include <ctime>
#define UT 6

class customer
{
public:
    static const int NID = -1; //未分配顺序号时的顺序号
    static const int upperTime = UT; //顾客服务时间的上界UT
    static int count; //用顾客的人数作为种子
public:
    customer(int _id = NID, int _time = 0);

public:
    void setDealingTime(int t)
    { dealingTime = t; }
    int getDealingTime() const
    { return dealingTime; }
    int getEnqueueTime() const
    { return enqueueTime; }
    void setWaitingTime(int _time)
    { waitingTime = _time; }
    int getWaitingTime() const
    { return waitingTime; }
    void setId(int _id) //分配顺序号
    { id = _id; }
    int getId() const
    { return id; }
private:
    int dealingTime; //所需服务时间
    int enqueueTime; //入队的时间
    int waitingTime; //等待的时间 出队才计算好
    int id; //顺序号
};

int customer::count = 0;

customer::customer(int _id, int _time): id(_id), enqueueTime(_time), waitingTime(0)
{
    count++;
    srand(time(NULL)+count);
    setDealingTime(rand() % upperTime + 2); // 在2-upperTime内随机分配服务时间
}



#endif