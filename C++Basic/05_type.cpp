#include <iostream>

// 传统的定义类型别名的方式
typedef double wages;   // wages是double的同义词
typedef wages base, *p; // base是double的同义词，p是double*的同义词
// C++11规定了一种新的方法
using wages = double;

// 这种类型别名将char*作为了基本类型
// 若将本名简单拼接，则基本类型就变成了char，*称为了声明符的一部分，这是错误的理解方式
typedef char *pstring;
const pstring cstr = 0; // cstr是指向char型变量的常量指针
const pstring *ps;      // ps是一个指针，所指的对象是指向char型变量的常量指针
// 在这种情况下，不应该将别名简单替换为本名理解
const char *cstr = 0; // 这是对const pstring cstr的错误理解，这将cstr理解为指向char型常量的指针

// auto类型说明符
int val1 = 1, val2 = 2;
auto item = val1 + val2; // 由val1和val2相加的结果推断出item的类型
// 使用auto在一条语句中声明多个变量时，所有变量只能有一个基本数据类型
auto i = 0, *p = &i;
// auto sz = 0, pi = 3.14; //这种是错误的，两个变量类型不同

int i = 0, &r = i;
auto a = r; // 此时a为int型
// auto一般会忽略顶层const，保留底层const
const int ci = i, &cr = ci;
auto b = ci;            // b是int型，ci的顶层const被忽略，auto推演为int
auto c = cr;            // c是int型，cr是ci的别名，而ci本身是顶层const，auto推演为int
auto d = &i;            // d是int型指针，auto推演为int
auto e = &ci;           // e是指向int型常量的指针，底层const没有被忽略，auto推演为const int
const auto f = ci;      // f是const int，auto的推演类型为int
auto &g = ci;           // g是int型常量引用，绑定到ci，底层const没有被忽略，auto推演为const int
const auto &h = 42;     // h是int型常量，要绑定字面值必须显式声明const，若写为auto &h = 42则会报错
auto k = ci, &l = i;    // k是int型，l是int型引用，auto推演为int
auto &m = ci, *p = &ci; // m是int型常量的引用，p是指向int型常量的指针，auto推演为const int
// auto &n = i, *p2 = &ci;
// 上述语句n是int型引用，p2是指向int型常量的指针，类型不同，故错误

// decltype类型说明符
int func() { return 1; }
decltype(func()) sum = 1; // sum的类型就是函数func()的返回值类型

const int ci = 0, &cj = ci;
decltype(ci) x = 0; // x的类型是const int
decltype(ci) y = x; // y的类型是const int &，注意此时的y是引用，故必须初始化

int i = 42, *p = &i, &r = i;
decltype(r + 0) b; // 加法的结果是int，故b是未初始化的int型变量
decltype(*p) c;    // p由*解引用后得到的类型是int&而非int，故c必须初始化
// decltype((variable))的结果永远是引用
// decltype(variable)的结果只有当variable本身是引用时才是引用
decltype((i)) d; // d是int&，必须初始化
decltype(i) e;   // e是一个未初始化的int型变量