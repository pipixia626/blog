//让工厂也符合开闭原则，把工厂抽象出去
#include <iostream>
#include <vector>
using namespace std;
//类的个数增加，增加维护成本

//符合开闭原则 简单工厂模式+开闭原则->工厂方法
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

//抽象工厂
class AbstractFruitFactory
{
public:
    virtual AbstractFruit *createFruit() = 0;
};

//苹果工厂
class AppleFactory : public ::AbstractFruitFactory
{
    virtual AbstractFruit *createFruit()
    {
        return new Apple;
    }
};
//香蕉工厂
class BananaFactory : public ::AbstractFruitFactory
{
    virtual AbstractFruit *createFruit()
    {
        return new Banana;
    }
};
//梨工厂
class PearFactory : public ::AbstractFruitFactory
{
    virtual AbstractFruit *createFruit()
    {
        return new Pear;
    }
};

void test01(){
    AbstractFruitFactory*factory=nullptr;
    AbstractFruit* fruit=nullptr;

    //创建一个苹果工厂
    factory=new AppleFactory;
    fruit=factory->createFruit();
    fruit->showName();

    //创建一个香蕉工厂
    factory=new BananaFactory;
    fruit=factory->createFruit();
    fruit->showName();

     //创建一个梨工厂
    factory=new PearFactory;
    fruit=factory->createFruit();
    fruit->showName();
}