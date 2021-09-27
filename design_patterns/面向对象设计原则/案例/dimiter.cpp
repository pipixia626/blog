//迪米特法则案例

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//最少知识原则

//买楼盘的人不需要一一地去看每一个楼盘，需要一个中介来给他信息就好

class AbstactBuilding
{
public:
    virtual void sale() = 0;
    virtual string getQulity()=0;
};
//楼盘A
class BuildingA : public AbstactBuilding
{
public:
    BuildingA()
    {
        qulity = "high";
    }
    virtual void sale()
    {
        cout << "A has been saled" << endl;
    }
    virtual string getQulity(){
        return qulity;
    }
public:
    string qulity;
};
//楼盘B
class BuildingB : public AbstactBuilding
{
public:
    BuildingB()
    {
        qulity = "low";
    }
    virtual void sale()
    {
        cout << "B has been saled" << endl;
    }
     virtual string getQulity(){
        return qulity;
    }
public:
    string qulity;
};

//客户端

// void test01()
// {
//     BuildingA *bulida = new BuildingA;
//     if(bulida->qulity=="high"){
//         bulida->sale();
//     }
//     BuildingB *bulidb = new BuildingB;
//     if(bulida->qulity=="low"){
//         bulida->sale();
//     }
// }

//为了避免客户端直接和楼盘打交道 因此需要一个中介类
class Mediator
{
public:
    Mediator()
    {
        AbstactBuilding *building = new BuildingA;
        vBuliding.emplace_back(building);
        building = new BuildingB;
        vBuliding.emplace_back(building);
    }
    ~Mediator()
    {
        for (vector<AbstactBuilding *>::iterator it = vBuliding.begin(); it != vBuliding.end(); ++it)
        {
            if (*it != nullptr)
            {
                delete *it;
            }
        }
    }

    //对外提供接口
    AbstactBuilding* findBuilding(string qulity){
        for(vector<AbstactBuilding *>::iterator it = vBuliding.begin(); it != vBuliding.end(); ++it){
            if((*it)->getQulity()==qulity){
                return *it;
            }
        }
        return nullptr;
    }

public:
    vector<AbstactBuilding *> vBuliding;
};

//新的客户端

void test02(){
    Mediator*mediator=new Mediator;
    mediator->findBuilding("high");
}