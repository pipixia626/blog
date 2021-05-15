# new和malloc区别


## 申请的内存所在位置
new 操作符从自由存储区上为对象分配内存空间<br>
而malloc函数从堆上动态分配内存。<br>
自由存储区是C++基于new操作符的一个抽象概念，凡是通过new操作符进行内存申请，该内存即为自由存储区
而堆是操作系统的术语，是操作系统所维护的一块特殊内存，用于程序的内存动态分配


### 自由存储区能否是堆

问题等价与new是否能在堆上动态分配内存，这取决于operator new 的实现细节
自由存储区不仅可以是堆，还可以是静态存储区，看operator new在哪里为对象分配内存

## 返回类型安全性

new内存分配成功返回的是对象类型的指针,类型严格与对象匹配，无须进行类型转换，是符合类型安全性的操作符<br>
而malloc内存分配成功返回的是void*，需要通过强制类型转换将Void*指针转换成需要的类型

## 内存分配失败时的返回值
new在申请空间失败后返回的是错误码bad_alloc<br>
malloc在申请空间失败后会返回NULL<br>

## 是否需要指定内存大小
使用new时，编译器会根据类型信息自行计算，而malloc需要显示地指定所需内存的尺寸

```
class A{...}
A * ptr = new A;
A * ptr = (A *)malloc(sizeof(A)); //需要显式指定所需内存大小sizeof(A); 
```
## 是否调用构造函数/析构函数
使用new操作符来分配对象内存时会经历三个步骤：

1：调用operator new 函数（对于数组是operator new[]）分配一块足够大的，原始的，未命名的内存空间以便存储特定类型的对象。
2：编译器运行相应的构造函数以构造对象，并为其传入初值。
3：对象构造完成后，返回一个指向该对象的指针。
使用delete操作符来释放对象内存时会经历两个步骤：

1：调用对象的析构函数。
2：编译器调用operator delete(或operator delete[])函数释放内存空间。

## 对数组的处理
c++提供了new[],delete[]来处理数组类型<br>
`	A * ptr = new A[10];//分配10个A对象`<
`delete [] ptr;`

malloc需要手动自定数组大小<br>
`int * ptr = (int *) malloc( sizeof(int)* 10 );//分配一个10个int元素的数组`
## new和malloc是否可以互相调用
operator new /operator delete的实现可以基于malloc，而malloc的实现不可以去调用new

## 是否可以被重载
opeartor new /operator delete可以被重载。标准库是定义了operator new函数和operator delete函数的8个重载版本：
```
//这些版本可能抛出异常
void * operator new(size_t);
void * operator new[](size_t);
void * operator delete (void * )noexcept;
void * operator delete[](void *0）noexcept;
//这些版本承诺不抛出异常
void * operator new(size_t ,nothrow_t&) noexcept;
void * operator new[](size_t, nothrow_t& );
void * operator delete (void *,nothrow_t& )noexcept;
void * operator delete[](void *0,nothrow_t& ）noexcept;
```
## 能否直观地重新分配内存
使用malloc分配的内存后，如果在使用过程中发现内存不足，
可以使用realloc函数进行内存重新分配实现内存的扩充。
realloc先判断当前的指针所指内存是否有足够的连续空间，
如果有，原地扩大可分配的内存地址，并且返回原来的地址指针；如果空间不够，先按照新指定的大小分配空间
，将原有数据从头到尾拷贝到新分配的内存区域，而后释放原来的内存区域。

## 客户处理内存分配不足
在operator new 抛出异常以反映一个未活得满足的需求之前，它会先调用一个用户指定的错误处理函数
new-hander.
```namespace std
{
    typedef void (*new_handler)();
}
```
指向了一个没有参数没有返回值的函数,即为错误处理函数。为了指定错误处理函数，
客户需要调用set_new_handler，这是一个声明于的一个标准库函数:
```
namespace std
{
    new_handler set_new_handler(new_handler p ) throw();
}
```

# 总结
|  特征   | new/delete  | malloc/fress |
|  ----  | ----  | ----  |
| 分配内存的位置 | 自由存储区 | 堆 |
| 内存分配成功的返回值 | 完整类型指针 | void* |
| 内存分配失败的返回值 | bad_mollc | NULL |
| 分配内存大小 | 由编译器根据类型计算得出 | 显示指定大小 |
| 处理数组 | new[] | 需要用户计算数组的大小后进行分配 |
| 已分配的内存的扩充 | 无法直观地处理 | realloc |
| 是否相互调用 | 可以，看具体的opreator new/delete 实现 | 不可调用new |
| 分配内存时内存不足 | 客户能够指定处理函数或重新制定分配器 | 无法通过用户代码进行处理|
| 函数重载 | 允许 | 不允许 |
| 构造函数与析构函数 | 调用 | 不调用 |


