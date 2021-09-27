#include <iostream>
using namespace std;

class A
{
public:
    static A *getInstance()
    {
        return a;
    }

private:
    A()
    {
        a = new A;
    }

private:
    static A *a;
};
A *A::a = nullptr;

//懒汉式 用到的时候才加载到内存
class Singleton_lazy
{

private:
    Singleton_lazy()
    {
        cout << "I am lazy!" << endl;
    }

public:
    static Singleton_lazy *getInstance()
    {
        if (singleton == nullptr)
        {
            singleton = new Singleton_lazy;
        }
        return singleton;
    }

private:
    static Singleton_lazy *singleton;
};
Singleton_lazy *Singleton_lazy::singleton = nullptr;

//饿汉式  先预加载到内存
class Singleton_hungry
{
private:
    Singleton_hungry()
    {
        cout << "I am hungry!" << endl;
    }

public:
    static Singleton_hungry *getInstance()
    {
        return singleton;
    }
//单例释放问题
class Garbo{
    ~Garbo(){
        if(singleton!=nullptr){
            delete singleton;
        }
    }
};
private:
    static Singleton_hungry *singleton;
    static Garbo garbo;
};
Singleton_hungry *Singleton_hungry::singleton = new Singleton_hungry;

void test01()
{
    Singleton_lazy *p1 = Singleton_lazy::getInstance();
    Singleton_lazy *p2 = Singleton_lazy::getInstance();

    if (p1 == p2)
    {
        cout << "两个指针指向同一块指针，是单例" << endl;
    }
    else
    {
        cout << "不是单例" << endl;
    }

    Singleton_hungry *p3 = Singleton_hungry::getInstance();
    Singleton_hungry *p4 = Singleton_hungry::getInstance();

    if (p3 == p4)
    {
        cout << "两个指针指向同一块指针，是单例" << endl;
    }
    else
    {
        cout << "不是单例" << endl;
    }
}



int main()
{
    //实现步骤
    //构造函数私有化
    //静态私有的类的指针变量
    //提供静态对外访问接口，可以让用户获得单例对象

    // cout << "main 函数开始执行" << endl;

    // //I am hungry!
    // //main 函数开始执行
    test01();
    return 0;
}