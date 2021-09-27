//合成复用原则

#include <iostream>
#include <vector>
using namespace std;

//继承和组合，优先使用组合 针对具体类不使用继承

class AbstractCar
{
public:
    virtual void run() = 0;
};

class BMW : public ::AbstractCar
{
    virtual void run()
    {
        cout << "BMW is running" << endl;
    }
};

class mercesbench : public ::AbstractCar
{
public:
    virtual void run()
    {
        cout << "bench is running" << endl;
    }
};

class Person
{
public:
    ~Person(){
        if(this->car!=nullptr){
            delete this->car;
        }
    }
    void setCar(AbstractCar *car)
    {
        this->car = car;
    }

    void BMW(){
        this->car->run();
    }
    void mercesbench(){
        this->car->run();
    }
public:
AbstractCar* car;
};

void test01(){
    Person* p=new Person;
    p->setCar(new BMW);
    p->BMW();

    p->setCar(new mercesbench);
    p->mercesbench();
    delete p;
}