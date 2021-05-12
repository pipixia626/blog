# 线程

## 背景

提高并发执行的效率
实体直接可以并发地执行
实体之间共享地址空间

进程当中的一条执行流程
## 定义
A thread is a basic unit of CPU utilization

## 结构

Thread ID
pragram counter
a register set
stack

和其他线程共享 code section,data section,和其他OS resourece(open files ,signals)

## 从两个方面理解进程

资源组合角度：进程把一组相关的资源组合起来构成一个资源平台（环境）,包括地址空间（代码段，数据段）
打开的文件等各种资源
运行角度：进程=线程+资源平台

## 线程和进程的比较
进程是资源分配单位，线程是CPU分配单位<br>
进程拥有一个完整的资源平台，而线程只独享必不可少的资源（寄存器，栈）<br>
线程同样具有就绪，阻塞，执行的三种状态，同样具有状态之间的转换<br>
线程能减少并发执行的时间和空间开销<br>
线程=轻量级进程<br>

<strong>高响应度</strong>

user threads和kernel threads映射关系（操作系统不支持但又想用多线程）->映射
[n:1]
[1:1]
[n:m]

## 线程池
相对于创建线程请求解决服务更轻快地提高，效率高，设定线程的数目的上限

