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
析构函数吐出异常会因为过早结束程序或发生不明确行为的风险，因此需要把异常交给来自析构函数以外的某个函数

当的确有异常抛出时，这时候析构函数就该吞下该异常或结束程序，客户就没有立场抱怨，毕竟条目有机会第一手处理问题

### 总结
- 析构函数绝对不要吐出异常，如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下或结束程序

- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么class应该提供一个普通函数(而非析构函数)中执行该操作



## 绝不在构造和析构过程中调用Virtual函数
(与Java 个C#不同)
- 不在构造中使用:
1. base 调用virtual函数时下降至derived class ->调用成对象内部尚未初始化的成分

2. 在derived class对象的base class 构造期间
对象的类型是base class而不是derived class ，不只virtual 函数会被编译器解析至base class，若使用运行期类型信息，也会把对象视为base class 类型

- 不在析构中调用：
1. 一旦derived class 析构函数开始执行，对象内的derived class 成员变量便呈现未定义值，所以C++视它们仿佛不存在
2. 进入base class析构函数后对象就成为一个base class对象

### 总结
在构造和析构期间不要调用virtual函数1因为这类调用从不下降至derived class

## 令operator =返回一个reference to *this
为了实现连锁赋值，赋值操作符必须返回一个reference指向操作符的左侧实参 
同时适用于所有赋值相关运算(随众)

### 总结
令赋值操作符返回一个reference to *this

## 在operator 中处理“自我赋值”
潜在的自我赋值不一定看得出来

证同测试->让Operator =具备"异常安全性"
### 总结
- 确保当对象自我赋值时operator=有良好行为，其中技术包括比较"来源对象"和"目标对象"的地址、精心周到的语句顺序，以及copy-and-swap
- 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确


## 复制对象时勿忘记每一个成分


- 当编写一个copying函数时，确保复制所有loacl成员变量
- 调用所有base classes内的适当的copying函数

### 总结
1. Copying函数应该确保复制"对象内的所有成员变量"及"所有base class成分"
2. 不要尝试以某个copying函数实现另一个copying函数，应该将共同技能放在第三个函数(init )且private的，并且由两个copying函数共同调用