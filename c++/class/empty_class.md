# 空类

## 空类的默认成员
只是声明一个空类，不做任何事情的话，编译器会自动生成
一个默认构造函数
一个拷贝默认构造函数
一个默认拷贝赋值函数
一个默认析构函数
一个取址运算符
一个const 取址运算符
这些函数有在第一次被调用的时候，编译器才会创建

所有这些函数都是inline和public

```
class Empty
{
public:
Empty(); // 缺省构造函数//
Empty( const Empty& ); // 拷贝构造函数//
~Empty(); // 析构函数//
Empty& operator=( const Empty& ); // 赋值运算符//
Empty* operator&(); // 取址运算符
const Empty* operator&() const; // 取址运算符 const
};

```
 
## 空类的大小

```
#include<iostream.h>

class a {};
class b{};
class c:public a{
	virtual void fun()=0;
};
class d:public b,public c{};
int main()
{
	 cout<<"sizeof(a)"<<sizeof(a)<<endl;
	 cout<<"sizeof(b)"<<sizeof(b)<<endl;
	 cout<<"sizeof(c)"<<sizeof(c)<<endl;
	 cout<<"sizeof(d)"<<sizeof(d)<<endl;
	 return  0;
 }
```
结果：

sizeof(a)=1

sizeof(b)=1

sizeof(c)=4  ：32位里面有->4 ，64位-》8

sizeof(d)=8 ：内存对齐
### 内置类型的大小

大多数内置类型都具有实现定义的大小。 下表列出了 Microsoft c + + 中内置类型所需的存储量。 特别是， long 即使在64位操作系统上，也是4个字节。

bool, char, char8_t, unsigned char, signed char, __int8	1 个字节

char16_t, __int16, short, unsigned short, wchar_t, __wchar_t	2 个字节

char32_t, float, __int32, int, unsigned int, long, unsigned long	4 个字节

double, __int64, long double, long long, unsigned long long	8 字节

### 类的大小
1：为类的非静态成员数据的类型之和

２．有编译器额外加入的成员变量的大小，用来支持语言的某些特性（如：指向虚函数的指针）

３．为了优化存取效率，进行的边缘调整

４　与类中的构造函数，析构函数以及其他的成员函数无关
