# kotlin基础
## Kotlin相比于java的优势
语法更加简洁，高级，安全，杜绝了空指针异常
100%兼容Java,Kotlin可以直接调用使用Java编写的代码，也可以无缝使用java第三方的开源库
## 工作原理

### java虚拟机工作机制
java代码经编译后生成class文件，即java字节码(Byte Code),JVM为解释器，解释class文件为二进制数据后再执行


Kotlin具备自己的编译器，可将Kotlin代码编译成同样规格的class文件

JVM不关心class文件的来源，只要符号规格即能识别


## 基础

1. 变量

2. 函数

3. 逻辑控制 

- if 有返回值

- when

- for-in循环语句

4. 类与对象

- 继承 open

- 接口 interface

- 数据类

- 单例类 (object) 类似于java静态方法调用方式

5. Lambda编程

6. 空指针检查

- 默认所有的参数和变量都不为空
需在编译时期处理所有的空指针异常。

- 判空辅助 ?. /?:

