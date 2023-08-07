#include "16_StrVec.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Args是一个模板参数包，rest是一个函数参数包
// Args表示零个或多个模板类型参数
// rest表示零个或多个函数参数
template <typename T, typename... Args>
void foo(const T &t, const Args &...rest) {
  // sizeof...运算符可以得到包中参数的数目
  cout << "Args: " << sizeof...(Args) << " rest: " << sizeof...(rest) << endl;
}

template <typename T> ostream &print(ostream &os, const T &t) {
  return os << t; // 包中最后一个元素之后不打印分隔符
}
template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args &...rest) {
  os << t << ", ";           // 打印第一个实参
  return print(os, rest...); // 递归调用，打印其他实参
}

ostream &print2(ostream &os) { return os; }
template <typename T, typename... Args>
ostream &print2(ostream &os, const T &t, const Args &...rest) {
  if (sizeof...(rest) == 0)
    return os << t << endl;
  else {
    os << t << ", ";
    return print(os, rest...);
  }
}

// template <typename T, typename... Args>
// ostream &print3(ostream &os, const T &t, const Args &...rest) {
//   if constexpr (sizeof...(rest) == 0)
//     return os << t << endl;
//   else {
//     os << t << ", ";
//     return print(os, rest...);
//   }
// }

// 包展开
template <typename T> string debug_rep(const T &t) {
  ostringstream ret;
  ret << t;
  return ret.str();
}
template <typename T> string debug_rep(T *p) {
  ostringstream ret;
  if (p)
    ret << " " << debug_rep(*p);
  else
    ret << " null pointer";
  return ret.str();
}
string debug_rep(const string &s) { return s; }
string debug_rep(char *p) { return debug_rep(string(p)); }
string debug_rep(const char *p) { return debug_rep(string(p)); }

template <typename... Args>
ostream &errorMsg(ostream &os, const Args &...rest) {
  // 等价于print(os, debug_rep(rest1), debug_rep(rest2), ..., debug_rep(restn));
  return print(os, debug_rep(rest)...);
}

int main(int argc, char const *argv[]) {
  // 接受可变数目参数的函数模板或类模板
  // 编译器会推断包中参数的数目
  int i = 0;
  double d = 3.14;
  string s = "hello world";
  foo(i, s, 42, d); // 包中有三个参数
  foo(s, 42, "hi"); // 包中有两个参数
  foo(d, s);        // 包中有一个参数
  foo("hi");        // 空包

  // 编译器会为foo实例化出四个不同的版本
  // void foo(const int&, const string&, const int&, const double&);
  // void foo(const string&, const int&, const char[3]&);
  // void foo(const double&, const string&);
  // void foo(const char[3]&);

  // 编写可变参数的模板函数
  print(cout, i, s, 42) << endl;
  // 此处有一个细节，假设将递归终止条件写进本函数内
  // 而不是利用一个新的模板函数做终止条件，将会是如上方定义的print2的代码
  // 这样看似可行，但编译会出问题
  // 因为编译器要求，即使分支中的语句不被执行，也必须能够通过编译
  // 而当sizeof...(rest) == 0时，此时else分支中被编译的函数将是print(os)
  // 显然这没有匹配的参数列表，故编译不会通过
  // 要想实现上述的递归中止方式，就必须再实现一个只接受os的print函数
  print2(cout, i, s, 42) << endl;
  // 或者使用C++17中的新特性，按条件编译
  // 见上方定义的print3
  // 此时，只有满足分支条件的部分会被编译，从而不会遇到需要编译print(os)的情况
  // print3(cout, i, s, 42) << endl;
  // 注意：该方式需要GCC编译器7以上的版本
  // 但经过尝试，GCC 8.1.0仍然无法正确编译

  // 包展开
  // 见上方定义的errorMsg
  errorMsg(cerr, i, s, 42);

  // 转发参数包
  // 组合使用可变参数模板与forward机制
  // 见16_StrVec.h
  StrVec svec;
  svec.emplace_back(10, 'c'); // 将cccccccccc添加为新的尾元素
  // std::forward<int>(10), std::forward<char>(c)
  string s1("hello"), s2("world");
  svec.emplace_back(s1 + s2); // 使用移动构造函数
  // std::forward<string>(string("helloworld"))

  return 0;
}
