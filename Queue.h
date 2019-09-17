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
    void setTime(int t)
    { _time = t; }
    int getTime() const
    { return _time; }
    void setId(int _id)
    { id = _id; }
    int getId() const
    { return id; }
private:
    int _time; //等待时间
    int id; //顺序号
};

customer::customer(): id(NID)
{
    srand(time(NULL)); 
    setTime(rand() % upperTime + 1); // 在1-upperTime内随机分配时间
}

class window
{
public:
    window();
    void loadCustomer(customer); //服务一个新的顾客并将等待时间设置为此顾客的服务时间；
    void dealing(); // 窗口等待时间减少一个单位;
    int getId() const
    { return theCustomer.getId(); } //返回服务顾客的顺序号
    bool empty() const
    { return dealingTime == 0; } //判断窗口是否空闲
    bool operator<(const window& rhs) const 
    { return dealingTime < rhs.dealingTime; } //判断两个窗口哪个等待时间更短
private:
    void dealing(int time); // 窗口等待时间减少time个单位;
    customer theCustomer; //处理的顾客
    int dealingTime; //剩余窗口等待时间
};

window::window(): dealingTime(0)
{

}

void window::loadCustomer(customer Customer)
{
    theCustomer = Customer;
    dealingTime = Customer.getTime();
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