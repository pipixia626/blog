# RAII (Resource Acquisition Is Initialization)

资源获取初始化

使用局部对象来管理资源的技术称为资源获取初始化

- 资源 操作系统中有限的东西如内存，网络套接字

- 局部对象 存储在栈的对象，它的生命周期由操作系统来管理的，无需人工介入

RAII的核心思想是将资源或状态与类对象的生命周期绑定，通过C++语言机制，实现资源与状态的安全管理。
## RAII原理

### Preview
资源的使用一般经历三个步骤

1. 获取资源
2. 使用资源
3. 销毁资源

但是资源的消耗往往是程序员经常忘记的一个环节，索引程序界就想如何在程序员中让资源自动销毁-> RAII

利用C++语言局部对象自动销毁的特性来控制资源的生命周期

### 整个RAII过程的四个步骤

1. 设计一个类封装资源
2. 在构造函数中初始化
3. 在析构函数中执行销毁操作
4. 使用时声明一个该对象的类

### RAII使用的技术

#### std::unique_ptr(资源管理方面)
```
std::unique_ptr<int> up1(new int); //ok 直接初始化
std::unique_ptr<int> up2 = new int;  //error 构造函数explicit
std::unique_ptr<int> up3 = up1;  //error 不可以拷贝

```
某一个时刻，只能由一个std::unique_ptr指向的对象，不允许多个std::unique_ptr指向同一个对象，所以std::unique_ptr不支持拷贝和复制，既然std::unique_ptr不支持拷贝和复制

因此只能返回std::unique_ptr&类型的参数

```
//传递引用,不会涉及到拷贝
void func(const std::unique_ptr<int>& up) {
       std::cout << *up << std::endl;
}
```

或者返回std::unique_Ptr类型的对象：
```
std::unique_ptr<int> func() {
     return std::unique_ptr<int>(new int(10));  //右值引用（调用移动构造函数） 或者RVO 也可以满足
}
```

### 状态管理方面
程同步中使用std::unique_lock或std::lock_guard对互斥量std::mutex进行状态管理也是RAII的典型实现，通过这种方式，我们再也不用担心互斥量之间的代码出现异常而造成线程死锁。