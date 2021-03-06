# 类型转换

## 隐式转换
由编译器完成，简化代码的书写


### preview

#### 直接初始化

#### 复制初始化

#### 类型构造时的隐式初始化


### 工作原理
#### 标准转换
对内置类型的转化
数组退化成指针，函数转化成函数指针
特定语境下要求的转化，函数类型提升，数值转化，数据类型到Void指针的转化，nullptr到数据类型指针的转化

#### 用户自定义转换
用户能控制的自定义的接口也就两个，转化构造函数和用户定义转换函数

转换构造函数：T（T2）

用户定义转换函数：operator T2()

explict可以修饰
#### 隐式转化序列

### 引发的问题

#### 引用绑定

#### 数组退化

#### 两步转化

## 显示转换

旧式风格类型转换
```
type(expr); // 函数形式的强制类型转换
(type)expr; // C语言风格的强制类型转换

```

现代C++风格

` cast-name<type>(expression)`

type :转换的目标类型

expression:被转换的值

cast-name ：转换的方式 static_cast，dynamic_cast，const_cast和reinterpret_cast四种

### static_cast
能够明确的类型转换都可以使用

但不能换掉底层const，volatile和_unaligned属性
由于不提供运行时的检查，因此叫做static_cast
因此：需要在编写程序时确认转换的安全性

#### 用途

- 类层次结构，父类和子类之间指针和引用的转换;进行向上转换，把子类对象的指针/引用转换为父类的指针/引用

- 用于基本数据类型之间的转换 

### dynamic_cast
在运行时会检查类型转换是否合法，具有一定的安全性，由于运行时的检查，所以会额外消耗一些性能

#### 用途

- 在类层次结构中使用时，向上转换和static_cast没有区别
在向下转换时会检查转换的类型，相比static_cast会更安全



#### 仅适用于指针或引用
在转换发生可能的前提下，dynamic_cast会尝试进行转换，若指针转换失败，则返回空指针，若引用转换失败，则抛出异常

#### 继承中的转换

##### 向上转换
在继承关系中 ，dynamic_cast由子类向父类的转换与static_cast和隐式转换一样，都是非常安全的。
##### 向下转换
类中必须定义虚函数
```
class A { virtual void f(){} };
int main()
{
     A *pA = new A;
     void *pV = dynamic_cast<void *>(pA); 
}
```
##### 菱形继承
```
class A { virtual void f() {}; };
class B :public A { void f() {}; };
class C :public A { void f() {}; };
class D :public B, public C { void f() {}; };

```
B继承A，C继承A。

D继承B和C。

![菱形继承](https://github.com/pipixia626/blog/blob/main/c%2B%2B/image/Inheritance.png)

考虑这样的情况：D对象指针能否安全的转换为A类型指针？

直觉来说是可以的，因为从子类向父类转化，无论如何都是安全的。

但是因为不知道选择哪一条路向上转换，因此会报错
所以需要手动选定一条向上转换的路
```
D *pD = new D;
B *pB = dynamic_cast<B *>(pD);
A *pA = dynamic_cast<A *>(pB);
```

### const_cast
const_cast用于移除类型的const、volatile和__unaligned属性。

常量指针被转换成非常量指针，并且仍然指向原来的对象；常量引用被转换成非常量引用，并且仍然引用原来的对象。
```
const char *pc;
char *p =const_cast<char*>(pc);
```
### reinterpret_cast

非常激进的指针类型转换，在编译期完成，可以转换任何类型的指针，所以极不安全。非极端情况不要使用。











