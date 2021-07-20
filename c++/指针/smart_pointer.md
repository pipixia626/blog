# 智能指针
unique_ptr、shared_ptr、weak_ptr三种智能指针

## 智能指针的由来
从C++98开始便推出了auto_ptr，对裸指针进行封装，让程序员无需手动释放指针指向的内存区域，在auto_ptr生命周期结束时自动释放，然而，由于auto_ptr在转移指针所有权后会产生野指针，导致程序运行时crash

```
auto_ptr<int> p1(new int(10));
auto_ptr<int> p2 = p1; //转移控制权
*p1 += 10; //crash，p1为空指针，可以用p1->get判空做保护
```

## unique_ptr的使用

对于同一块内存只能有一个持有者，而且不允许赋值操作
屏蔽掉上面讲到的auto_ptr的控制权转换的问题，其后的控制权转移问题可以调用move方法，转移控制权之后，再访问裸指针，也会产生crash


```
unique_ptr<int> ip(new int(5));
//auto up2=up //编译错误
auto up2 = move(up);
cout << *up << endl; //crash，up已经失效，无法访问其裸指针
```

### 创建动态数组


- 静态数组，在编译的时候决定了数组大小
int arr[10];

- 通过指针创建在堆上的数组，可在运行时动态指定数组大小，但需要手动释放内存

int *arr=new int[10];

- 通过std::vector容器创建动态数组，无需手动释放数组内存
std::vector<int> arr[10];

- 通过unique_ptr创建动态数组，也无需手动释放，比vector更轻量化

unique_ptr<int []>arr(new int [10]);

<strong>不管是vector还是unique_ptr，虽然可以帮我们自动释放数组内存，但如果数组的元素是复杂数据类型，我们还需要在其析构函数中正确释放内存才可以</strong>

## shared_ptr
采用引用计数，实现对同一块的内存可以有多个引用，在最后一个引用被释放时，指向的内存才释放

###  attention

- 构造shared_ptr的方法，如下示例代码所示，我们尽量使用shared_ptr构造函数或者make_shared的方式创建shared_ptr，禁止使用裸指针赋值的方式，这样会shared_ptr难于管理指针的生命周期。

```
// 使用裸指针赋值构造，不推荐，裸指针被释放后，shared_ptr就野了，不能完全控制裸指针的生命周期，失去了智能指针价值
int *p = new int(10);
shared_ptr<int>sp = p;
delete p; // sp将成为野指针，使用sp将crash
// 将裸指针作为匿名指针传入构造函数，一般做法，让shared_ptr接管裸指针的生命周期，更安全
shared_ptr<int>sp1(new int(10));
// 使用make_shared，推荐做法，更符合工厂模式，可以连代码中的所有new，更高效；方法的参数是用来初始化模板类
shared_ptr<int>sp2 = make_shared<int>(10);

```

- 禁止使用指向shared_ptr的裸指针，也就是智能指针的指针，这听起来就很奇怪，但开发中我们还需要注意，使用shared_ptr的指针指向一个shared_ptr时，引用计数并不会加一，操作shared_ptr的指针很容易就发生野指针异常。

```
shared_ptr<int>sp = make_shared<int>(10);
cout << sp.use_count() << endl; //输出1
shared_ptr<int> *sp1 = &sp;
cout << (*sp1).use_count() << endl; //输出依然是1
(*sp1).reset(); //sp成为野指针
cout << *sp << endl; //crash

```

- 传染性
一个对外的接口中使用了shared_ptr，那么所有使用这个接口的地方全都要改为使用shared_ptr，否则shared_ptr无法覆盖到对象整个生命周期，就成了摆设。
### 创建动态数组
不推荐，太麻烦了，需要指定析构方法外（因为默认的是T的析构函数而不是T[]）数据类型也得是shared_ptr<T>
最好使用unique_ptr

### 实现多态
析构函数就不需要定义为虚函数了

```
class A {
public:
~A() {
cout << "dealloc A" << endl;
}
};
class B : public A {
public:
~B() {
cout << "dealloc B" << endl;
}
};
int main(int argc, const char * argv[]) {
A *a = new B();
delete a; //只打印dealloc A
shared_ptr<A>spa = make_shared<B>(); //析构spa是会先打印dealloc B，再打印dealloc A
return 0;
}

```

### 循环引用问题
A中引用B，B中引用A，spa和spb的强引用计数永远大于等于1，所以直到程序退出前都不会被退出，这种情况有时候在正常的业务逻辑中是不可避免的，而解决循环引用的方法最有效就是改用weak_ptr

```
class A {
public:
shared_ptr<B> b;
};
class B {
public:
shared_ptr<A> a;
};
int main(int argc, const char * argv[]) {
shared_ptr<A> spa = make_shared<A>();
shared_ptr<B> spb = make_shared<B>();
spa->b = spb;
spb->a = spa;
return 0;
} //main函数退出后，spa和spb强引用计数依然为1，无法释放

```

## weak_ptr

我们一个类A里面只是想引用一下另外一个类B的对象，类B对象的创建不在类A，因此类A也无需管理类B对象的释放，这个时候weak_ptr就应运而生了，使用shared_ptr赋值给一个weak_ptr不会增加强引用计数（strong_count），取而代之的是增加一个弱引用计数（weak_count），而弱引用计数不会影响到指针的生命周期，这就解开了循环引用

## 智能指针原理
通过栈上的一个对象来管理一个堆上的对象，
在shared_ptr/unique_ptr的析构函数中判断当前裸指针的引用计数情况来决定是否释放裸指针

