//产品族：同一产地或者同一厂商，功能不同

//产品等级：功能相同，产地或者厂商不同

#include <iostream>
using namespace std;
//抽象苹果
class AbstractApple
{
public:
    virtual void showName() = 0;
};

//中国苹果
class ChinaApple : public ::AbstractApple
{
public:
    virtual void showName()
    {
        cout << "China apple" << endl;
    }
};
//美国苹果
class AmericaApple : public ::AbstractApple
{
public:
    virtual void showName()
    {
        cout << "America apple" << endl;
    }
};
//日本苹果
class JapenApple : public ::AbstractApple
{
public:
    virtual void showName()
    {
        cout << "Japen apple" << endl;
    }
};

//抽象香蕉
class AbstractBanana
{
public:
    virtual void showName() = 0;
};
//中国香蕉
class ChinaBanana : public ::AbstractBanana
{
public:
    virtual void showName()
    {
        cout << "China Banana" << endl;
    }
};
//美国香蕉
class AmericaBanana : public ::AbstractBanana
{
public:
    virtual void showName()
    {
        cout << "America Banana" << endl;
    }
};
//日本香蕉
class JapenBanana : public ::AbstractBanana
{
public:
    virtual void showName()
    {
        cout << "Japen Banana" << endl;
    }
};

//抽象梨
class AbstractPear
{
public:
    virtual void showName() = 0;
};
//中国香蕉
class ChinaPear : public ::AbstractPear
{
public:
    virtual void showName()
    {
        cout << "China Pear" << endl;
    }
};
//美国香蕉
class AmericaPear : public ::AbstractPear
{
public:
    virtual void showName()
    {
        cout << "America Pear" << endl;
    }
};
//日本香蕉
class JapenPear : public ::AbstractPear
{
public:
    virtual void showName()
    {
        cout << "Japen Pear" << endl;
    }
};

//抽象工厂 针对产品族
class AbstractFactory
{
public:
    virtual AbstractApple *CreateApple() = 0;
    virtual AbstractBanana *CreateBanana() = 0;
    virtual AbstractPear *CreatePear() = 0;
};

//中国工厂
class ChinaFactory : public ::AbstractFactory
{
public:
    virtual AbstractApple *CreateApple()
    {
        return new ChinaApple;
    }
    virtual AbstractBanana *CreateBanana()
    {
        return new ChinaBanana;
    }
    virtual AbstractPear *CreatePear()
    {
        return new ChinaPear;
    }
};
//美国工厂

class AmericaFactory : public ::AbstractFactory
{
public:
    virtual AbstractApple *CreateApple()
    {
        return new AmericaApple;
    }
    virtual AbstractBanana *CreateBanana()
    {
        return new AmericaBanana;
    }
    virtual AbstractPear *CreatePear()
    {
        return new AmericaPear;
    }
};
//日本工厂
class JapenFactory : public ::AbstractFactory
{

public:
    virtual AbstractApple *CreateApple()
    {
        return new JapenApple;
    }
    virtual AbstractBanana *CreateBanana()
    {
        return new JapenBanana;
    }
    virtual AbstractPear *CreatePear()
    {
        return newJapenPear;
    }
};