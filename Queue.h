#ifndef QUEUE_H
#define QUEUE_H

#include <cstdlib>
#include <ctime>
#define UT 10

class customer
{
public:
    static const int NID = -1; //未分配顺序号时的顺序号
    static const int upperTime = UT; //顾客服务时间的上界UT

public:
    customer();

public:
    void setDealingTime(int t)
    { dealingTime = t; }
    int getDealingTime() const
    { return dealingTime; }
    void increaseWaitingTime()
    { waitingTime++; } //增加等待的时间
    int getWaitingTime() const
    { return waitingTime; }
    void setId(int _id) //分配顺序号
    { id = _id; }
    int getId() const
    { return id; }
private:
    int dealingTime; //所需服务时间
    int waitingTime; //等待的时间
    int id; //顺序号
};

customer::customer(): id(NID), waitingTime(0)
{
    srand(time(NULL)); 
    setDealingTime(rand() % upperTime + 1); // 在1-upperTime内随机分配服务s时间
}

class window
{
public:
    window();
    
public:
    void loadCustomer(customer); //服务一个新的顾客并将等待时间设置为此顾客的服务时间；
    void dealing(); // 窗口等待时间减少一个单位;
    void increaseNumber()
    { dealedNumber++; } //增加服务的人数    
    int getId() const
    { return theCustomer.getId(); } //返回服务顾客的顺序号
    int getNumber() const
    { return dealedNumber; } //返回服务的人数
    bool empty() const
    { return dealingTime == 0; } //判断窗口是否空闲
    bool operator<(const window& rhs) const 
    { return dealingTime < rhs.dealingTime; } //判断两个窗口哪个等待时间更短

private:
    customer theCustomer; //处理的顾客
    int dealingTime; //剩余窗口等待时间
    int dealedNumber; //服务的人数
    void dealing(int time); // 窗口等待时间减少time个单位;    
};

window::window(): dealingTime(0), dealedNumber(0)
{

}

void window::loadCustomer(customer Customer)
{
    theCustomer = Customer;
    dealingTime = Customer.getDealingTime();
    increaseNumber(); //服务人数加1
}

void window::dealing()
{
    if(!empty())
        dealing(1);
}

void window::dealing(int time)
{
    dealingTime -= time; 
}

#endif