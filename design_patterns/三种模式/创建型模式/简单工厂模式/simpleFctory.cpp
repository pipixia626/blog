//客户端和具体实现类解耦
//对于某些对象创建过程比较复杂的情况，不需要自己创建
//传入参数，让工厂知道应该创建什么类型的对象

//缺点，增加新的对象类型时需要修改源代码，不符合开闭原则，
//这个类的职责过重,如果发生问题就很麻烦，因此不属于23种设计模式

#include <iostream>
#include <vector>
using namespace std;

//抽象水果
class AbstractFruit
{

public:
    virtual void showName() = 0;
};

//apple
class Apple : public ::AbstractFruit
{
public:
    virtual void showName()
    {
        cout << "I am apple" << endl;
    }
};
//banana
class Banana : public ::AbstractFruit
{
public:
    virtual void showName()
    {
        cout << "I am banana" << endl;
    }
};
//pear
class Pear : public ::AbstractFruit
{
public:
    virtual void showName()
    {
        cout << "I am pear" << endl;
    }
};

//水果工厂

class FruitFactory
{
public:
    static AbstractFruit *createFruit(string flag)
    {
        if (flag == "apple")
        {
            return new Apple;
        }
        else if (flag == "banana")
        {
            return new Apple;
        }
        else if (flag == "pear")
        {
            return new Apple;
        }
        else
            return nullptr;
    }
};

void test01()
{
    FruitFactory *Factory = new FruitFactory;
    AbstractFruit *apple = Factory->createFruit("apple");
    apple->showName();
    delete apple;

    AbstractFruit *banana = Factory->createFruit("banana");
    banana->showName();
    delete banana;

    AbstractFruit *pear = Factory->createFruit("pear");
    pear->showName();
    delete pear;
}