# Constructors,Destructors, and Assignment Operators


## 了解C++默认编写并调用哪些函数

一个空类当编译器处理过后
就会有一个默认构造函数,一个copy构造函数，一个拷贝赋值函数，和一个析构函数（public 且inline的)
隐式的->当被调用的时候才会被编译器创建出来


### 总结
编译器可以暗自为class创建上述操作符和函数

## 若不想使用编译器自动生成的函数，就该明确拒绝
不想声明某一类编译器自动生成的函数
可以使用Private关键字来对拷贝构造函数和拷贝赋值符函数使得编译器暗自创建其专属版本->friend和member函数还是可以调用private成员
->private 继承(被编译器拒绝访问)

### 总结
为驳回编译器自动提供的机能，可将相应的成员函数声明为private并且不予实现


## 为多态基类声明virtual析构函数
当derived class对象经由一个base class指针被删除，而该base class带着一个non-virtual 析构函数时
实际执行时通常发生的是对象的derived成分没被销毁

但不能无端地都声明为virtual (虚表占内存)
- 心得 当class内至少含有一个virtual函数，才声明为virtual析构函数

任何不带virtual析构函数的class ，包括STL容器（行为不明确，base class的析构函数不会被调用）

### pure class析构
pure virtual 函数导致abstract classes ->不能被实体化的class ->拥有抽象的对象了

### 总结
- 带多态性质的base class应该声明一个virtual 析构函数，如果class 带有任何virtual函数，它就应该拥有一个virtual析构函数

- classes的设计目的如果不是作为base classes使用，或者不具备多态性的，就不该声明为virtual 析构函数

## 别让异常逃离析构函数

## 绝不在构造和析构过程中调用Virtual函数

## 令operator =返回一个reference to *this

## 在operator 中处理“自我赋值”

## 复制对象时勿忘真每一个成分