# 定制new和delete

## 了解 new-handler行为
客户指定的获取内存分配失败的错误处理函数

```
<new>
namespace std {
    typedef void (*new_handler)();
    new_handler set_new_handler(new_handler p)throw;
}
```

一个良好的new-handler函数需要做
- 让更多内存可被使用
一开始执行就分配一大块内存，当new-handler第一次被调用，就将它们释还给程序

- 安装另一个new-handler
当下次被调用时可以做不同的事情

- 卸除new-handler 
将null指针传给set_new-handler ，一旦没有安装任何new-handler operator new 会在内存分配不成功时抛出异常

- 抛出bad_alloc 的异常，这样的异常不会被operator new捕捉，因此会传播到内存所求处

- 不返回 调用abort或exit


C++并不支持class专属之new-handlers，可以自己实现，只需令每一个class提供自己的ser_new_handler和operator new
同时注意和global new-handler替换就好


### 总结
1. set_new_handlder允许客户指定一个函数，在内存分配无法获得满足时被调用

2. 分配失败便返回null行为，这种形式被称为nothorw形式
但因为只会保证在new的时候抛异常，在对类类型的构造函数的时候不会，因此多少有点发育不良

## 了解new 和delete的合理替换时机
为什么会有人想要替换掉编译器提供的operator new或operator delete
-  用来检测运用上的错误
new 和delete使用不合理
- 为了强化效能
碎片问题和速度问题
- 为了收集使用上的统计数据
根据需求如何使用动态内存，分配区块的大小分布，寿命如何
倾向于FIFO、LIFO次序或者运用形态释放随时间改变，不同阶段的执行阶段有不同的分配/归还形态吗？任何时刻所使用的最大动态分配量的高水位是多少

BootS程序库的pool就是这样一个分配器(分配大量小型对象)

### 总结
有许多理由需要自写个new和delete，包括改善效能，对heap运用错误进行调试，收集heap使用信息

## 编写new 和delete时需固守常规

## 写了placement new 也要写placement delete