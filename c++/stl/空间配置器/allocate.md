# allocator

## 概念
  C++的STL中定义了很多容器，容器的第二个模板参数通常为allocator类型，于是想对这一类型做个透彻的了解，看看到底是怎么回事。标准库中allocator类定义在头文件memory中，用于帮助将内存分配和对象的构造分离开来。它分配的内存是原始的、未构造的。和vector等一样，allocator也是一个模板类，为了定义一个allocator对象，我们需指明这个allocator可以分配的对象类型，这样allocator好根据给定的对象类型来确定合适的内存空间大小和对齐位置，


## 两个伴随算法

uninitialized_copy(b,e,b2)       从迭代器b和e指出的输入范围中拷贝元素到迭代器b2指定的未构造的原始内存中，b2指向的内存必须足够大，能容纳输入序列中元素的拷贝。

uninitialized_copy_n(b,n,b2)   从迭代器b指向的元素开始，拷贝n个元素到b2开始的内存中



uninitialized_fill(b,e,t)               在迭代器b和e指定的原始内存范围中创建对象，对象的值均为t的拷贝

uninitalized_fiil_n(b,n,t)             在迭代器b指向的内存地址开始创建n个对象，b必须指向足够大的未构造的原始内存，能够容乃给定数量的对象


## 实例

