using namespace std;
#include <iostream>
#include <string>
#include "20_Window.h"

// 默认实参
using sz = string::size_type;
// 一旦某个形参被赋予了默认值，它后面的所有形参都必须有默认值
Window screen(sz ht = 24, sz wid = 80, char backgrnd = ' ');

// 多次声明同一个函数也是合法的
Window screen2(sz, sz, char = ' ');
// string screen2(sz, sz, char = '*');     // 错误：重复声明
// 由于存在赋予第三个形参默认值的函数，故下列声明也是正确的
// 若不存在上面的函数声明，只有下面一条声明，则错误
Window screen2(sz = 24, sz = 80, char);

int main()
{
    Window window;
    window = screen();             // 等价于screen(24,80,'')
    window = screen(66);           // 等价于screen(66,80,'')
    window = screen(66, 256);      // 等价于screen(66,256,'')
    window = screen(66, 256, '#'); // 等价于screen(66,256,'#')

    // window = screen(, , '?'); // 错误：只能省略尾部的实参
    window = screen('?'); // 调用screen('?',80,'')

    window = screen2();
}

// 局部变量不能作为默认实参
// 只要表达式的类型能转换成形参所需的类型，就能作为默认实参
sz wd = 80;
char def ='';
sz ht();
Window screen3(sz = ht(), sz = wd, char = def);
Window win = screen3(); // 等价于screen(ht(),80,'')

void func()
{
    def = '*';       // 改变默认实参的值
    sz wd = 100;     // 隐藏了外层定义的wd，但没有改变默认值
    win = screen3(); // 等价于screen3(ht(),80,'*')
}

// 内联函数
// 在每个调用点上“内联的”展开，避免函数调用的开销
// 内联说明只是向编译器发出的一个请求，编译器可以选择忽略这个请求
// 即使不加内联声明，编译器有时也会使用这种方式进行优化
inline const string &shorterString(const string &s1, const string &s2)
{
    return s1.size() <= s2.size() ? s1 : s2;
}
// cout << shroterString(s1, s2) << endl;
// 编译后将展开成下列形式
// cout << (s1.size() <= s2.size() ? s1 : s2) << endl;
// 一般的，内联机制适用于优化规模较小、流程直接、频繁调用的函数

// constexpr函数
// 能用于常量表达式的函数：函数返回类型以及所有的形参都是字面值类型
// 函数体中必须有且只有一条return语句
// constexpr函数被隐式地指定为内联函数
// constexpr函数并不要求返回常量表达式
constexpr int new_sz(){return 42};
constexpr int foo = new_sz();
// 如果arg是常量表达式，则scale(arg)也是常量表达式
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }

int arr[scale(2)]; // 正确：scale(2)是常量表达式
int i = 2;
// int arr2[scale(i)]; // 错误：scale(i)不是常量表达式

// 函数实现
Window
screen(sz ht, sz wid, char backgrnd)
{
    Window window;
    window.height = ht;
    window.width = wid;
    window.background = backgrnd;

    return window;
}

Window screen2(sz ht, sz wid, char backgrnd)
{
    Window window;
    window.height = ht;
    window.width = wid;
    window.background = backgrnd;

    return window;
}

Window screen3(sz ht, sz wid, char backgrnd)
{
    Window window;
    window.height = ht;
    window.width = wid;
    window.background = backgrnd;

    return window;
}