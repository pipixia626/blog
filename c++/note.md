# 自实现一个可用检查内存泄露的工具

## 效果
检查正常的new 和delete申请的内存，还可以检测智能指针使用不当引起的内存泄露

## 原理

C++中申请和释放内存使用的是new 和delete关键字：

```
void func(）{

   A* a = new A(）
   delete a;
   A* b =new int[4]
   delete [] b;
   }
```

明确一下需求：如果程序中存在内存泄露，我们的目的是找到这些内存在哪里分配，如果能够具体对应到<br>
代码中中哪一个文件哪一行代码就好了，内存在哪里释放我们没必要检测，只需要检测出内存是在哪里申请就行

### 思路

在申请内存时记录下该内存的地址和代码中申请内存的位置，在内存销毁时删除该地址对应的记录，程序最后统计一下<br>
程序最后统计一下还有哪条记录没有被删除，如果还有没有被删除的记录就代表有内存泄露

## 实现
new 关键字底层是通过operator new来申请内存的：
` void* operator new(std::size_t sz)`

重载这个操作符：
``` 
void* operator new(std::size_t sz ,const char*file,int line);
void* operator new[](std::size_t sz,const char*file,int line);
```

让程序申请申请内存时调用重载的这个函数，就可用记录下内存申请的具体情况

如何让底层程序申请内存时调用重载的这个函数：
在这里可以对new使用宏定义：

`#define new new(_FILE_,_LINE_)`
于是在new A 的时候，底层就会自动调用operator new(std::size_t,const char* file,int line)函数来达到目的

## 问题：
1: 在哪里记录内存申请的信息？如果在operator new 内部又申请了一块内存，用于记录位置，<br>
那新申请的这块内存需要记录吗？岂不是递归调用<br>
2:只有在new宏定义包裹的范围内申请内存才会被记录，某些第三方库或者某些地方没有被new宏定义包裹，怎么检测？<br>

### 哪里存储具体信息
不能套娃，程序会崩溃，可以在每次申请内存时，一次性申请一块稍微大一点的内存，具体信息存储在多余的那块内存

```
   static void* alloc_mem(std::size_t,const char*file,int line,bool is_array){
   assert(line>=0);
   
   sdt::size_t s= size+ALIGEND_LIST_ITEM_SIZE;
   new_ptr_list_t* ptr=(new_ptr_list_t*)malloc(s)
   if(ptr==nullptr){
      std::unique_lock<std::mutex>lock(new_output_lock);
       printf("Out of memory when allocating %lu bytes\n", (unsigned long)size);
        abort();
    }
 
    void* usr_ptr = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;

    if (line) {
        strncpy(ptr->file, file, _DEBUG_NEW_FILENAME_LEN - 1)[_DEBUG_NEW_FILENAME_LEN - 1] = '\0';
    } else {
        ptr->addr = (void*)file;
    }

    ptr->line = line;
    ptr->is_array = is_array;
    ptr->size = size;
    ptr->magic = DEBUG_NEW_MAGIC;
    {
        std::unique_lock<std::mutex> lock(new_ptr_lock);
        ptr->prev = new_ptr_list.prev;
        ptr->next = &new_ptr_list;
        new_ptr_list.prev->next = ptr;
        new_ptr_list.prev = ptr;
    }
    total_mem_alloc += size;
    return usr_ptr;
}
```
new_ptr_list_t结构体定义：
```
struct new_ptr_list_t {
    new_ptr_list_t* next;
    new_ptr_list_t* prev;
    std::size_t size;
    union {
        char file[200];

        void* addr;
    };
    unsigned line;
};

```

### 没有被new宏包裹的地方可以检测的到吗
没有被new宏包裹的地方是会调用operator new(std::size_t sz)函数来申请内存的。<br>
这里operator new函数不只可以重载，还可以重新定义它的实现，而且不会报multi definition的错误哦。因为它是一个weak symbol

## 重定义再使用

```
void* operator new(std::size_t size) { 
    return operator new(size, nullptr, 0); 
}
```

这样有个缺点，就是不能记录内存申请的具体代码位置，只能记录下来是否申请过内存，
不过这也挺好，怎么也比没有任何感知强的多。其实这里不是没有办法，尽管没有了new宏
获取不到具体申请内存的代码位置，但是可以获取到调用栈信息，把调用栈信息存储起来，还是可以定位大体位置。
关于如何获取调用栈信息，大家可以研究下libunwind库看看。

## 释放内存
这里需要重定义operator delete(void* ptr)函数：

```
void operator delete(void* ptr) noexcept { 
    free_pointer(ptr, nullptr, false); 
}
```
free_pointer函数的大体思路就是在链表中找到要对应节点，删除掉，具体定义如下：
```
static void free_pointer(void* usr_ptr, void* addr, bool is_array) {
    if (usr_ptr == nullptr) {
        return;
    }
    new_ptr_list_t* ptr = (new_ptr_list_t*)((char*)usr_ptr - ALIGNED_LIST_ITEM_SIZE);
    {
        std::unique_lock<std::mutex> lock(new_ptr_lock);
        total_mem_alloc -= ptr->size;
        ptr->magic = 0;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
    }
    free(ptr);
}

```
## 如何检测

遍历链表，每次new时候会把这段内存插入链表，delete时候会把这段内存从链表中移出，如果程序最后链表长度不为0，即为有内存泄漏
```
作者：程序喵大人
链接：https://www.zhihu.com/question/29859828/answer/1798470821
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int checkLeaks() {
    int leak_cnt = 0;
    int whitelisted_leak_cnt = 0;
    new_ptr_list_t* ptr = new_ptr_list.next;

    while (ptr != &new_ptr_list) {
        const char* const usr_ptr = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
        printf("Leaked object at %p (size %lu, ", usr_ptr, (unsigned long)ptr->size);
        if (ptr->line != 0) {
            print_position(ptr->file, ptr->line);
        } else {
            print_position(ptr->addr, ptr->line);
        }
        printf(")\n");
        ptr = ptr->next;
        ++leak_cnt;
    }
    return leak_cnt;
}
```

## 其他第三方的工具
如：后续补充

