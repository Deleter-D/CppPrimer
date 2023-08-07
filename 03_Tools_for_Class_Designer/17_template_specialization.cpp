#include "17_Sales_data.h"
#include <cstring>
#include <iostream>
#include <type_traits>
#include <unordered_set>
using namespace std;

// 当不能(或不希望)使用模板版本时，可以定义一个特例化版本
// 版本一：比较任意两个类型
template <typename T> int compare(const T &v1, const T &v2) {
  cout << "[Version 1]";
  return v1 < v2 ? -1 : v1 == v2 ? 0 : 1;
}
// 版本二：处理字符串字面常量
template <size_t N, size_t M>
int compare(const char (&)[N], const char (&)[M]) {
  cout << "[Version 2]";
  return N < M ? -1 : N == M ? 0 : 1;
}
// 特例化版本：处理字符数组的指针
// 此处两个const都是底层const
// p1是指向const char*的引用，不会去改变该const char*指针，故为const(右侧的)
// 而char*所指的字符也不会被改变，所以也是const的(左侧的)
template <> int compare(const char *const &p1, const char *const &p2) {
  cout << "[Special Version]";
  return strcmp(p1, p2);
}

// 特例化成员
template <typename T> struct Foo {
  Foo(const T &t = T()) : mem(t) {}
  void Bar() { cout << "[Foo<T>'s Generic Bar]" << endl; }
  T mem;
};
template <>            // 不写类型表明正在特例化一个模板
void Foo<int>::Bar() { // 正在特例化Foo<int>的成员Bar
  cout << "[Foo<int>'s Bar Specialization]" << endl;
}

int main(int argc, char const *argv[]) {
  const char *p1 = "hi", *p2 = "mom";
  // 无法将一个指针转换为数组的引用
  cout << compare(p1, p2) << endl; // 调用版本一
  // 实现特例化版本之前，compare(p1, p2)只能调用版本一
  // 特例化后，字符串指针有了特例化的处理，故匹配特例化版本
  cout << compare("hi", "mom") << endl; // 调用版本二
  // 实现特例化版本之后，对于特例化版本和版本二都能匹配
  // 但特例化版本可以接受char指针或char数组，版本二只能接受char数组
  // 故版本二更特殊，故依然匹配版本二

  // 类模板特例化
  // 见17_Sales_data.h中的hash特例化
  unordered_multiset<Sales_data> SDset;
  // 类模板部分特例化
  // 标准库中的remove_reference
  // 原始的、通用的版本如下
  /*
  template <class T> struct remove_reference{ typedef T type; };
  */
  // 部分特例化版本如下，将用于左值引用和右值引用
  /*
  template <class T> struct remove_reference<T&>{ typedef T type; };
  template <class T> struct remove_reference<T&&>{ typedef T type; };
  */
  // 只能部分特例化类模板，而不能部分特例化函数模板
  int i;
  int &ri = i;
  remove_reference<decltype(42)>::type a;           // 匹配通用版本
  remove_reference<decltype(ri)>::type b;           // 匹配左值版本
  remove_reference<decltype(std::move(i))>::type c; // 匹配右值版本

  // 特例化成员
  // 见上方定义的Foo
  Foo<string> fs; // 实例化Foo<string>::Foo()
  fs.Bar();       // 实例化Foo<string>::Bar()
  Foo<int> fi;    // 实例化Foo<int>::Foo()
  fi.Bar();       // 使用特例化版本的Foo<int>::Bar()
  return 0;
}
