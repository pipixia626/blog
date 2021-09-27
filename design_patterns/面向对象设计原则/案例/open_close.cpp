//开闭原则案例

#include <iostream>
using namespace std;

//对扩展开放，对修改关闭，增加功能是通过增加功能来实现的，而是修改
//代码

//写一个抽象类 
class AbstractCaculator
{
public:
    virtual int getResult() = 0;
    virtual void getOperatorNumber()=0;
};

//加法计算器类
class PlusCauculator : public AbstractCaculator
{
public:
    int mA;
    int mB;

public:
    void getOperatorNumber(int a, int b)
    {
        this->mA = a;
        this->mB = mB;
    }
    virtual int getResult()
    {
        return mA+mB;
    }
};
//减法计算器类
class SubCauculator : public AbstractCaculator
{
public:
    int mA;
    int mB;

public:
    void getOperatorNumber(int a, int b)
    {
        this->mA = a;
        this->mB = mB;
    }
    virtual int getResult()
    {
        return mA-mB;
    }
};

//乘法计算器类
class MulCauculator : public AbstractCaculator
{
public:
    int mA;
    int mB;

public:
    void getOperatorNumber(int a, int b)
    {
        this->mA = a;
        this->mB = mB;
    }
    virtual int getResult()
    {
        return mA*mB;
    }
};

//除法计算器类
class DivCauculator : public AbstractCaculator
{
public:
    int mA;
    int mB;

public:
    void getOperatorNumber(int a, int b)
    {
        this->mA = a;
        this->mB = mB;
    }
    virtual int getResult()
    {
        return mA/mB;
    }
};

//取模计算器类
class SubCauculator : public AbstractCaculator
{
public:
    int mA;
    int mB;

public:
    void getOperatorNumber(int a, int b)
    {
        this->mA = a;
        this->mB = mB;
    }
    virtual int getResult()
    {
        return mA%mB;
    }
};