# new 和delete


## preview 
c++内存管理是通过new和delete运算符实现的，
来探究一下new和delete背后的样子

## 实现原理

### 内置类型
如果申请的是内置类型的空间,new 和malloc,delete和free基本是类似的

#### new 和new[]
new/delete请求和释放单个元素的空间
new[]和delete申请的是连续空间
而且new在申请空间失败时会抛出异常，malloc则会返回null


### 自定义类型
new的原理
1：调用operator new 函数申请空间
2：在申请的空间上执行构造函数，完成对象的构造

delete 的原理
在对象所处在的内存空间上执行析构函数，完成对象中资源的清理工作

new T[]的原理
1:调用operator new[]函数，在实际调用operator new 函数完成N个对象空间的申请
2:每个对象执行其对应的构造函数


delete[] 的原理
1：在释放的空间上执行N次析构函数，完成N个对象资源的清理
2：调用operator delete[]释放空间，实际在operator delet[]中调用operator delete 释放空间

### opeartor new() operator delete()

new 和delete是用户进行动态内存申请和释放的操作符
operator new 和opeator ddelete是系统提供的全局函数

new/delete在底层调用operator new 全局函数来申请和释放空间


```
/*
operator new :该函数实际通过malloc来申请空间，当malloc申请空间成功时直接返回；申请空间失败执行空间不足应对措施

*/
void *__CRTDECL operator new(size_t size) _THROW1(_STD bad_alloc)
{
 // try to allocate size bytes
 void *p;
 while ((p = malloc(size)) == 0)
 if (_callnewh(size) == 0)
 {
 // report no memory
 // 如果申请内存失败了，这里会抛出bad_alloc 类型异常
 static const std::bad_alloc nomem;
 _RAISE(nomem);
 }
 return (p);
}

/*
operator delete: 该函数最终是通过free来释放空间的
*/
void operator delete(void *pUserData)
{
 _CrtMemBlockHeader * pHead;
 RTCCALLBACK(_RTC_Free_hook, (pUserData, 0));
 if (pUserData == NULL)
 return;

_mlock(_HEAP_LOCK); /* block other threads */
 __TRY
 /* get a pointer to memory block header */
 pHead = pHdr(pUserData);
 /* verify block type */
 _ASSERTE(_BLOCK_TYPE_IS_VALID(pHead->nBlockUse));
 _free_dbg( pUserData, pHead->nBlockUse );
 __FINALLY
 _munlock(_HEAP_LOCK); /* release other threads */
 __END_TRY_FINALLY
 return;
}

/*
free的实现
*/
#define free(p) _free_dbg(p, _NORMAL_BLOCK)

```
### new 和delete重载
某些应用程序对内存分配有特殊的需求，因此我们无法将标准内存管理机制直接应用于这些程序。需要自定义内存分配的细节
从而需要重载new 运算符和delete运算符以控制内存分配的过程


#### new 表达式的工作机理

当我们使用一条new 表达式时:

```
string*str=new string("a string);//分配并初始化一个string对象

string*arr=new string[10];//分配10个默认初始化的string对象
```

参考上述代码

执行步骤：
- new表达式调用一个名为operatr new(或者operator new [])的标准库,该函数分配一个足够大的，原始的，未命名的内存空间以便存储特定类型的对象

- 编译器运行相应的构造函数以构造这些对象，并且为其传入初始值

- 对象被分配了空间并构造完成，返回一个对象的指针

 当我们使用一条delete表达式删除一个动态分配的对象时：

 ```
 delete str;//销毁*str，然后释放str指向的内存空间
 delete [] arr;//销毁数组中的元素，然后释放对应的内存空间
 ```
执行步骤类似


####  分析
应用程序可以在全局作用域中定义operator new 和operator delete 函数，也可以将它们定义为成员函数，当编译器发现一条new表达式或delete表达式后，将在程序中查找可供调用的operator函数，根据表达式里面的参数类型来查找

- 如果被分配(释放)的对象是类类型，则编译器首先在类及其基类的作用域查找，如果此时该类含有operator new 成员或者operator delete成员，相应的表达式将调用这些成果

- 否则，编译器则在全局作用域查找匹配的函数->使用标准库定义的版本

可以使用作用域运算符令其忽略定义在类中的函数
:: new /delete

#### 标准库定义的重载版本

- 可能会抛出异常

```
void* operator new(size_t); // 分配一个对象
void* operator new[] (size_t); // 分配一个数组
void* operator delete(void*) noexcept; // 释放一个对象
void* operator delete[] (void*) noexcept; //释放一个数组
```

- 不会抛出异常

```
void* operator new(size_t, nothrow_t&) noexcept;
void* operator new[](size_t, nothrow_t&) noexcept;
void* operator delete(void*, nothrow_t&) noexcept;
void* operator delete[] (void*, nothrow_t&) noexcept;

```

##### nothrow_t和noexcept

nothrow_t是定义在new头文件中的一个struct，这个类型中不包含任何成员
new 头文件还定义了一个名为nothrow的const对象，用户可以通过这个对象请求new的非抛出版本

当重载这些运算符时，必须使用noexcept异常说明符指定其不抛出异常


#### 注意事项和例子

重载必须位于全局作用域或者类作用域，它们是隐式静态的


```#include "operator_new.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
 
namespace operator_new_ {
 
// reference: http://zh.cppreference.com/w/cpp/memory/new/operator_new
class New1 {
public:
	New1() = default;
 
	void* operator new(std::size_t sz){
		std::printf("global op new called, size = %zu\n", sz);
		return std::malloc(sz);
	}
 
	void operator delete(void* ptr) /*noexcept*/
	{
		std::puts("global op delete called");
		std::free(ptr);
	}
};
 
struct New2 {
	static void* operator new(std::size_t sz)
	{
		std::cout << "custom new for size " << sz << '\n';
		return ::operator new(sz);
	}
 
	static void* operator new[](std::size_t sz)
	{
		std::cout << "custom new for size " << sz << '\n';
		return ::operator new(sz);
	}
 
	static void operator delete(void* ptr, std::size_t sz)
	{
		std::cout << "custom delete for size " << sz << '\n';
		::operator delete(ptr);
	}
 
	static void operator delete[](void* ptr, std::size_t sz)
	{
		std::cout << "custom delete for size " << sz << '\n';
		::operator delete(ptr);
	}
};
 
struct New3 {
	New3() { throw std::runtime_error(""); }
 
	static void* operator new(std::size_t sz, bool b){
		std::cout << "custom placement new called, b = " << b << '\n';
		return ::operator new(sz);
	}
 
	static void operator delete(void* ptr, bool b)
	{
		std::cout << "custom placement delete called, b = " << b << '\n';
		::operator delete(ptr);
	}
};
 
int test_operator_new_1()
{
	New1* new1 = new New1;
	delete new1;
 
	New2* p1 = new New2;
	delete p1;
	New2* p2 = new New2[10];
	delete[] p2;
 
	try {
		New3* p1 = new (true) New3;
	} catch (const std::exception&) {}
 
 
 
	return 0;
}
 
///
// https://www.geeksforgeeks.org/overloading-new-delete-operator-c/
class student
{
	std::string name;
	int age;
public:
	student()
	{
		std::cout << "Constructor is called\n";
	}
 
	student(std::string name, int age)
	{
		std::cout << "Constructor params is called\n";
		this->name = name;
		this->age = age;
	}
 
	void display()
	{
		std::cout << "Name:" << name << std::endl;
		std::cout << "Age:" << age << std::endl;
	}
 
	void * operator new(size_t size)
	{
		std::cout << "Overloading new operator with size: " << size << std::endl;
		void * p = ::new student();
		//void * p = malloc(size); will also work fine
 
		return p;
	}
 
	void operator delete(void * p)
	{
		std::cout << "Overloading delete operator " << std::endl;
		free(p);
	}
};
 
int test_operator_new_2()
{
	student * p = new student("Yash", 24);
 
	p->display();
	delete p;
 
	return 0;
}
 
 
// reference: http://thispointer.com/overloading-new-and-delete-operators-at-global-and-class-level/
class Dummy
{
public:
	Dummy()
	{
		std::cout << "Dummy :: Constructor" << std::endl;
	}
 
	~Dummy()
	{
		std::cout << "Dummy :: Destructor" << std::endl;
	}
 
	// Overloading CLass specific new operator
	static void* operator new(size_t sz)
	{
		void* m = malloc(sz);
		std::cout << "Dummy :: Operator new" << std::endl;
		return m;
	}
 
	// Overloading CLass specific delete operator
	static void operator delete(void* m)
	{
		std::cout << "Dummy :: Operator delete" << std::endl;
		free(m);
	}
};
 
int test_operator_new_3()
{
	Dummy * dummyPtr = new Dummy;
	delete dummyPtr;
 
	return 0;
}
 
//
// reference: https://msdn.microsoft.com/en-us/library/kftdy56f.aspx
class Blanks
{
public:
	Blanks() { std::cout << "Constructor " << std::endl; }
	void* operator new(size_t stAllocateBlock, char chInit);
};
 
void* Blanks::operator new(size_t stAllocateBlock, char chInit)
{
	std::cout << "size:" << stAllocateBlock << ",chInit:" << chInit << "end" << std::endl;
	void *pvTemp = malloc(stAllocateBlock);
	if (pvTemp != 0)
		memset(pvTemp, chInit, stAllocateBlock);
	return pvTemp;
}
 
int test_operator_new_4()
{
	Blanks *a5 = new(0xa5) Blanks;
	std::cout << (a5 != 0) << std::endl;
 
	return 0;
}
 
 
// reference: http://www.interviewsansar.com/2015/07/15/write-syntax-to-overload-new-and-delete-operator-in-a-class/
class CustomMemory {
private:
	int i; // size of int is 4 byte
public:
	CustomMemory(){
		std::cout << "Constructor" << "\n";
	}
	~CustomMemory(){
		std::cout << "Destructor" << "\n";
	}
 
	//Overloaded new
	void* operator new(size_t objectSize)
	{
		std::cout << "Custom memory allocation" << "\n";
		//Write allocation algorithm here
		return malloc(objectSize);
 
	}
 
	//Overloaded 2 arguments new operator
	void* operator new(size_t objectSize, int x)
	{
		std::cout << "Custom 2 argument memory allocation" << "\n";
		CustomMemory *ptr = (CustomMemory*)malloc(objectSize);
		ptr->i = x;
 
		return ptr;
	}
 
	//Overloaded delete
	void operator delete(void* ptr)
	{
		std::cout << "Custom memory de- allocation" << "\n";
		free(ptr);
	}
 
	void Display()
	{
		std::cout << "Value of i =" << i << "\n";
	}
};
 
int test_operator_new_5()
{
	CustomMemory* obj = new CustomMemory(); // call overloaded new from the class delete obj;
	delete obj; // call overloaded delete
 
	//overloaded 2 argument new
	CustomMemory * ptr = new(5)CustomMemory();
	ptr->Display();
	delete ptr;
 
	return 0;
}
 
} // namespace operator_new_


```