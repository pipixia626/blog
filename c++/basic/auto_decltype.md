# auto
cv属性(const 和volatile)
推导规则:
在不声明为引用或指针时，auto会忽略等号右边的引用类型和cv限定

在声明为引用或者指针时，auto会保留等号右边的引用和cv属性
# decltype
推导规则：
exp是表达式，decltype(exp)和exp类型相同

exp是函数调用，decltype(exp)和函数返回值类型相同

其它情况，若exp是左值，decltype(exp)是exp类型的左值引用

和auto不同
decltype不会像auto一样忽略引用和cv属性，decltype会保留表达式的引用和cv属性