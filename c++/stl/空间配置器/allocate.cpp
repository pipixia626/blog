#include <memory>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    allocator<string> alloc; //定义了一个可以分配string 的allocaterdioxin

    auto const p = alloc.allocate(3); //分配n个未初始化未构造的空的string内存

    auto q = p;

    auto q = p;                    //q指向最后构造的元素之后的位置
    alloc.construct(q++);          //*q为空字符串
    alloc.construct(q++, 10, 'c'); //*q为cccccccccc
    alloc.construct(q++, "hi");    //*q为hi

    return 0;
}