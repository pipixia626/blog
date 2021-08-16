# 资源管理
资源包括
内存，文件描述器，互斥锁，图形界面中的字型和笔刷，数据库连接
网络socket
## 以对象管理资源
- 获得资源后立刻放进管理对象
以对象管理资源的概念常被称为"资源取得时间便是初始化时机"

- 管理对象运用析构函数保证资源被释放

### 总结
1. 为防止资源泄露，使用RAII对象，它们在构造函数中获取资源并在析构函数中释放资源
2. 两个常被使用的RAII classes 分别是trl""shared_ptr 和auto_ptr，前者通常是较佳选择，因为其copy行为比较直观，使用auto_ptr，复制动作会使它)被复制物指向null

## 在资源类中小心copying行为
当一个RAII对象被复制时，会发生什么?
- 禁止复制 ，许多时候允许RAII对象被复制并不合理
将cpy操作声明为private
- 对底层资源祭出"引用计数法“,有时候希望保有资源，直到它的最后一个使用者（某对象）被销毁，者种情况下被复制，增加引用计数

trl::shared_ptr允许指定所谓的"删除器(deleter)"那是一个函数或函数对象，当引用次数为时被调用

### 总结
1. 复制RAII对象必须一并复制它管理的资源，所有资源的copy行为决定RAII对象的copying行为
2. 普通而常见的RAII class copying行为是抑制copying，施行引用计数法以及其它方法

## 在资源管理类中提供对原始资源的访问
对于shared_ptr ->get成员函数用来指向显示转换(返回智能指针内部的原始指针)

trl::shared_ptr和auto_ptr也重载了指针取值操作符，允许隐式转换至底部原始指针

### 总结
1. API往往要求访问原始资源，所以每一个RAII class应该提供一个取得其所算了之资源的办法
2. 对原始资源的访问可能经由显示转换或隐式转换，显示转换比较安全，隐式转换对客户比较方便
## 成对使用new和delete时要采取相同形式
一个对象和一个对象数组结构不同，数组可能还有一个记录形式
使用new 一个对象数组，delete一个对象时，可能会出现并未持有它正忙着销毁的那种类型的对象

->对喜欢使用typdef 的人很重要 ->要匹配好
### 总结
1. 如果你在new表达式中使用[] ，必须相应地使用delete[]
同理不使用[] ，则delete不使用[]
## 以独立语句将newed对象置入智能指针
在资源被创建和资源被转换为资源管理对象两个时间点之间有可能产生异常干扰(编译器不得在它们之间任意选择执行次序)

### 总结
以独立语句将newed对象存储(置入)智能指针内，如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄露