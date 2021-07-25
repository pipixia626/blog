# 右值引用和std::move

## 什么是左值，右值

左值可以取地址，位于等会左边/ 右值没法取地址，位于等号右边

` int a=5;`

- a可以通过&取地址，位于等号左边，
- 5位于等号右边，没法通过&取地址

```
struct A {
    A(int a = 0) {
        a_ = a;
    }
 
    int a_;
};
 
A a = A();
```
- 同样的，a可以通过&取地址，位于等号左边
- A()是个临时值，没法通过&取地址，位于等号右边，所以是个右值

thus 有地址的变量就是左值，没有地址的字面值、临时值就是右值

## 左值引用、右值引用

引用本质是别名，通过引用修改变量的值，传参时引用额可以避免拷贝，其实现原理和指针类似，存放引用对象的地址

### 值的分类
- 左值
- 将亡值
- 右值
### 左值引用
能指向左值，不能指向右值的就是左值引用

```
int a = 5;
int &ref_a = a; // 左值引用指向左值，编译通过
int &ref_a = 5; // 左值引用指向了右值，会编译失败
```
**const 左值引用** const左值引用不会修改指向值，因此可以指向右值，这也是为什么要使用const &作为函数参数的原因之一

`void push_back (const value_type& val); `

### 右值引用

```
int &&ref_a_right = 5; // ok
 
int a = 5;
int &&ref_a_left = a; // 编译不过，右值引用不可以指向左值
 
ref_a_right = 6; // 右值引用的用途：可以修改右值
```

#### 特点
- 通过右值引用的声明，右值又重获新生，其生命周期和右值引用类型变量的生命周期一样长，只要该变量还活着，该右值临时量将会一直存活下去

```
```
#### 右值引用解决的问题
- 临时对象非必要的昂贵拷贝操作

避免临时对象的拷贝构造和析构
- 模板函数中如何按照参数的实际类型进行转发
它是未定的引用类型（universal references），如果被一个左值初始化，它就是一个左值；如果它被一个右值初始化，它就是一个右值，它是左值还是右值取决于它的初始化
#### 右值引用可以指向左值吗
使用std::move 把左值强制转换为右值，让右值引用可以指向左值，类似于一个类型转换

## std::move
广泛地用于在STL和自定义类中实现移动语义，避免拷贝，从而提高程序性能

### 深拷贝和浅拷贝
c++类的拷贝又两种：深拷贝和浅拷贝
当出现类的等号赋值时，会调用拷贝函数

#### 浅拷贝和深拷贝的区别

- 未定义显示拷贝构造函数的情况下，系统会调用默认的拷贝函数 -即为浅拷贝，能够完成成员的一一复制。当数据成员中没有指针时，浅拷贝是可行的；但当数据成员有指针时，如果采用简单的浅拷贝，则两类中的两个指针将指向同一个地址，当对象快结束时，会调用两次析构函数，而导致指针悬挂现象，此时就必须采用深拷贝

- 深拷贝和浅拷贝的区别就在于深拷贝会在堆内存中另外申请空间存储数据，从而解决了指针悬挂的问题
