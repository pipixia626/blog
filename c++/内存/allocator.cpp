//简单的allocator类
#include <memory>
#include<iostream>
class Allocator
{
private:
    //定义一个节点指针，指向下一个未分配的空间内存，被称为嵌入式指针
    struct node
    {
        struct node *next;
    };

    //表示某个类对应的预先分配空间的大小
    int chunk = 5;

    node *ptr = nullptr;

public:
    void *allocate(size_t size);
    void delocate(void *, size_t);
};

//分配空间，大小为 size * chunck，每次调用allocate将会得到一块内存
void *Allocator::allocate(size_t size)
{
    node *p;
    if (ptr == nullptr)
    { //如果链表为空，则先申请一整块的内存
        p = ptr = (node *)malloc((size)*chunk);
        for (int i = 0; i < chunk - 1; i++)
        {
            p->next = (node *)((char *)p + size); //一个字符的大小为一个字节，相当于将p后移动size个字节
            p = p->next;
        }
        //处理最后一个节点的指针，以防野指针
        p->next = nullptr;
    }
    p = ptr;
    ptr = ptr->next;
    return p;
}

void Allocator::delocate(void *p, size_t size)
{
    //将p放回链表的前端
    ((node *)p)->next = ptr;
    ptr = (node *)p;
}

//a如果一个类重载了operator new 那么它申请原始内存的方式将会被修改
class A
{
public:
    A(int s_) : s(s_) {}
    void print()
    {
        std::cout << "舔狗 id: " << s << std::endl;
    }

private:
    int s;

public:
    static Allocator alloc;
    //重载operator new
    static void *operator new(size_t size)
    {
        std::cout << "舔狗归来" << std::endl;
        return alloc.allocate(size);
    }
    //重载operator delete
    static void operator delete(void *p, size_t size)
    {
        std::cout << "舔狗离开" << std::endl;
        alloc.delocate(p, size);
    }
};
//静态变量初始化
Allocator A::alloc;