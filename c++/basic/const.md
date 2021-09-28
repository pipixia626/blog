# const
是一个关键字
表示被这个关键字修饰的对象不可修改

## const 和指针
一个有六种形式
const int p; ->常量整数

从右往左读，遇到p替换成 p is a，遇到*替换成point to 
const int *p;  ->p is a point to int const ->p是一个指向整型常量的指针
int const *p;-> p is a point to const int ->和上面一样

int *const p;-> p is a const point to int->p是一个常量指针，指向整型

const int *const p; ->常量指针常量

int const *const p;->常量指针常量


### 顶层const和底层const
https://zhuanlan.zhihu.com/p/161560391

const int*p 常量指针 ->指向常量的指针 ->底层
int *const p;指针常量 ->指针是一个常量 ->顶层

## const 和成员函数

const放在返回值类型前面修饰返回值为常量，放在函数后面修饰该函数为常量函数。
在类中将成员函数修饰为const，const修饰this指针指向的对象，这也就保证调用这个const成员函数的对象在内部不会被改变
表明在该函数体内，不能修改对象的数据成员而且不能调用非const函数。
为什么不能调用非const函数？因为非const函数可能修改数据成员，const成员函数是不能修改数据成员的，
所以在const成员函数内只能调用const函数
众所周知，在相同参数及相同名字的情况下，const是可以构成函数重载的，但const成员函数不能更改任何非静态成员变量

const对象默认调用const成员函数，非const对象默认调用非const成员函数；

若非const对象想调用const成员函数，则需显式转化，如(const Student&)obj.getAge();

若const对象想调用非const成员函数，同理const_cast<Student&>(constObj).getAge();(注意：constObj要加括号)