# 用户界面

系统和用户之间进行信息交流的媒介，实现信息的内部形式与人类可以接收形式之间的转换
## 用户界面框架



### MVC

- 控制器(Controller):处理用户输入
1. 接收并响应外部动作
2. 每个外部动作作为一个独立事件
3. 使用队列处理外部动作(先进先出)
4. 基于事件分配处理函数

- 视图(View):显示用户界面和图像
- 模型(Model):保存数据和代码
通过controler的控制去操作model层的数据，并且返回给view层展示


MVC缺点：
1. View和Model之间还存在依赖关系，Controller很重很复杂，view和model层是相互可知的，这两层之间存在耦合，开发，测试，维护都需要花大量的精力

2. 在Android中Activity即是View又是Controller，所以会很复杂。
xml作为view层，控制能力实在太弱了，你想去动态的改变一个页面的背景，或者动态的隐藏/显示一个按钮，这些都没办法在xml中做，只能把代码写在activity中，造成了activity既是controller层，又是view层的这样一个窘境。大家回想一下自己写的代码，如果是一个逻辑很复杂的页面，activity或者fragment是不是动辄上千行呢？这样不仅写起来麻烦，维护起来更是噩梦。
### MVP

P:presenter：主持者，Presenter通过View接收用户的输入，然后在Model的帮助下处理用户的数据并将结果传回View,
### MVVM

model:数据部分
View:界面展示部分
Viewmodel：一个连接数据模型和界面展示的桥梁

## 界面布局

