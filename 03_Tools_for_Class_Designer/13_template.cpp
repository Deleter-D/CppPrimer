#include "13_Blob.h"
#include "13_DebugDelete.h"
#include "13_Foo.h"
#include "13_Numbers.h"
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <string.h>
#include <utility>
#include <vector>
using namespace std;

// 模板是C++泛型编程的基础
// 为模板提供足够的信息，就能够生成特定的类或函数

// 定义模板
template <typename T> // 模板参数列表
// T的实际类型在编译时根据compare的使用情况来确定
int compare(const T &v1, const T &v2) {
  if (v1 < v2)
    return -1;
  if (v2 < v1)
    return 1;
  return 0;
}

// 类型参数可以用来指定返回类型或函数的参数类型
template <typename T> T foo(T *p) {
  T tmp = *p; // tmp的类型将是指针p指向的类型
  return tmp;
}

// 错误：U之前必须加上class或typename
// template <typename T, U> T calc(const T &, const U &);
// 正确：在目标参数列表中，typename和class没什么不同
template <typename T, class U> T calc(const T &, const U &);

// 可以在模板中定义非类型参数，表示一个值而非一个类型
template <unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
  return strcmp(p1, p2);
}

// inline和constexpr的函数模板
// 正确：inline说明符跟在模板参数列表之后
template <typename T> inline T min(const T &, const T &);
// 错误：inline说明符位置不正确
// inline template <typename T> T min(const T &, const T &);
// constexpr同理

// 编写类型无关的代码
// 即使使用指针也正确的版本
template <typename T> int compare2(const T &v1, const T &v2) {
  if (less<T>()(v1, v2))
    return -1;
  if (less<T>()(v2, v1))
    return 1;
  return 0;
}
// 模板程序应尽量减少对实参类型的要求

// 模板类型别名
template <typename T> using twin = pair<T, T>;
template <typename T> using partNo = pair<T, unsigned>;

// 默认模板实参
template <typename T, typename F = less<T>>
int compare3(const T &v1, const T &v2, F f = F()) {
  if (f(v1, v2))
    return -1;
  if (f(v2, v1))
    return 1;
  return 0;
}
bool Shorter(const string &s1, const string &s2) {
  return s1.size() < s2.size();
}

int main(int argc, char const *argv[]) {
  // 实例化函数模板
  // 实例化出int compare(const int&, const int&)
  cout << compare(1, 0) << endl; // T为int

  // 实例化出int compare(const vector<int>&, const vector<int>&)
  vector<int> vec1{1, 2, 3}, vec2{4, 5, 6};
  cout << compare(vec1, vec2) << endl; // T为vector<int>
  // 编译器生成的版本通常被称为模板的实例

  // 实例化出int compare(const char (&p)[3], const char (&p2)[4])
  cout << compare("hi", "mom") << endl;

  // 模板类
  // 实例化模板类
  Blob<int> ia;
  Blob<int> ia2 = {0, 1, 2, 3, 4};

  // 类模板成员函数的实例化
  // 实例化Blob<int>和接受initializer_list<int>的构造函数
  Blob<int> squares = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // 实例化Blob<int>::size() const
  for (size_t i = 0; i != squares.size(); ++i)
    squares[i] = i * i; // 实例化Blob<int>::operator[](size_t)
  // 若一个成员函数未被调用，则它不会被实例化
  // 默认情况下，对于一个实例化了的类模板，其成员只有在使用时才被实例化

  // 在类代码内简化模板类名的使用
  // 见13_BlobPtr.h

  // 类模板和友元
  // 见13_Blob.h
  Blob<char> ca; // BlobPtr<char>和operator==<char>都是本对象的友元
  Blob<int> ia3; // BlobPtr<int>和operator==<int>都是本对象的友元

  Blob<int> inta{1, 2, 3, 4};
  Blob<int> inta2{1, 2, 3, 4};
  cout << (inta == inta2 ? "true" : "false") << endl;

  // 通用和特性的模板友好关系
  // 见下方定义的Pal、C、C2等类

  // 令模板自己的类型参数成为友元
  // 见下方定义的Bar类

  // 模板类型别名
  // 别名定义见上方
  twin<string> authors;
  twin<int> win_loss;
  twin<double> area;
  // 可以固定一个或多个模板参数
  partNo<string> book;

  // 类模板的static成员
  // 见13_Foo.h
  // 实例化static成员Foo<string>::ctr和Foo<string>::count
  Foo<string> fs;
  // 三个对象共享相同的Foo<int>::ctr和Foo<int>::count成员
  Foo<int> fi, fi2, fi3;

  // 类模板的每个实例都有一个独有的static对象
  // 将static数据成员定义成模板，见13_Foo.h

  Foo<int> fi4;                // 实例化Foo<int>类的static数据成员ctr
  auto ct = Foo<int>::count(); // 实例化Foo<int>::count()
  ct = fi4.count();            // 使用Foo<int>::count()
  // ct = Foo::count(); // 错误：无法判断使用哪个版本实例的count()

  // 模板参数
  // 见下方定义

  // 与函数参数相同，声明中的模板参数的名称不必与定义中的相同
  // 见下方定义

  // 使用类的类型成员
  // 见13_Foo.h的get_value()

  // 默认模板实参
  // 见上方compare3()与Shorter()定义
  cout << compare3(0, 42) << endl;                          // 使用less<int>
  cout << compare3<string>("hi", "world", Shorter) << endl; // 使用自定义比较器

  // 模板默认实参与类模板
  // 见13_Numbers.h
  Numbers<long double> lots_of_precision;
  Numbers<> average_precision; // 空<>表示使用默认类型

  // 一个类可以包含本身是模板的成员函数：成员模板(不能是虚函数)
  // 普通类的成员模板，见13_DebugDelete.h
  double *dp = new double;
  DebugDelete d; // 可以像delete表达式一样使用的对象
  d(dp);         // 调用DebugDelete::operator()(double*)释放p
  int *ip = new int;
  DebugDelete()(ip); // 在一个临时DebugDelete对象上调用operator(int*)
  // 销毁p指向的对象
  // 实例化DebugDelete::operator()<int>(int *)
  unique_ptr<int, DebugDelete> p(new int, DebugDelete());
  // 销毁sp指向的对象
  // 实例化DebugDelete::operator()<string>(string*)
  unique_ptr<string, DebugDelete> sp(new string, DebugDelete());

  // 类模板的成员模板
  // 见13_Blob.h中接受两个迭代器的构造函数定义
  vector<int> vec3{0, 1, 2, 3, 4, 5};
  Blob<int> itb(vec3.begin() + 1, vec3.end() - 1);
  for (int i = 0; i < itb.size(); ++i)
    cout << itb[i] << " ";
  cout << endl;

  // 实例化与成员模板
  int iarr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<long> lvec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  list<const char *> words = {"now", "is", "the", "time"};
  // 实例化Blob<int>类及其接受两个int*参数的构造函数
  Blob<int> b1(begin(iarr), end(iarr));
  // 实例化Blob<int>类及其接受两个vector<long>::iterator参数的构造函数
  Blob<int> b2(lvec.begin(), lvec.end());
  // 实例化Blob<string>及其接受两个list<const char*>::iterator参数的构造函数
  Blob<string> b3(words.begin(), words.end());

  // 通过显式实例化避免相同的实例出现在多个对象文件中
  // 使用extern模板声明时，它不会在本文件中生成实例化代码
  // 将一个实例化声明为extern就表示承诺在程序其他位置有该实例化的一个非extern声明
  // 对于一个给定的实例化版本，可以有多个extern声明，但只能有一个定义

  // 效率与灵活性
  // unique_ptr与shared_ptr定义如下
  // template<class T, class Deleter = std::default_delete<T>> class unique_ptr;
  // template<class T> class shared_ptr;
  // 对于shared_ptr，其析构函数必须包含类似如下语句
  // del?del(p):delete p; // del是一个成员，运行时需要跳转到del的地址
  // 而对于unique_ptr
  // del(p) // 编译时就可以确定类型，无运行时额外开销
  // shared_ptr更注重灵活性，而unique_ptr没有这样的灵活性需求，故更注重效率

  return 0;
}

// 前置声明，在将目标的一个特定实例声明为友元时要用到
template <typename T> class Pal;
// C是普通类
class C {
  // 用类C实例化的Pal是C的一个友元
  friend class Pal<C>;
  // Pal2的所有实例都是C的友元，这种情况无需前置声明
  template <typename T> friend class Pal2;
};
// C2是模板类
template <typename T> class C2 {
  // C2的每个实例将相同类型实例化的Pal声明为友元
  friend class Pal<T>; // Pal的模板声明必须在作用域之内
  // Pal2的所有实例都是C2的每个实例的友元，不需要前置声明
  template <typename X> friend class Pal2;
  // Pal3是非模板类，它是C2所有实例的友元
  friend class Pal3; // 不需要Pal3的前置声明
};
// 为了让所有实例成为友元，友元声明中必须使用与模板本身不同的模板参数

// 令模板自己的类型参数成为友元
template <typename T> class Bar {
  friend T;
};

// 模板参数
typedef double A;
// 当模板参数中出现与外部类型别名相同的情况时，外部的类型别名将被隐藏
template <typename A, typename B> void f(A a, B b) {
  A tmp = a; // tmp的类型为A类型，而非double
  // double B;  // 错误：重声明模板参数B
}
// 错误：非法重用模板参数名V
// template <typename V, typename V> void f(V a, V b) {}

// 与函数参数相同，声明中的模板参数的名称不必与定义中的相同
// 三个calc都指向相同的函数模板
template <typename T> T calc(const T &, const T &);                 // 声明
template <typename U> U calc(const U &, const U &);                 // 声明
template <typename Type> Type calc(const Type &a, const Type &b) {} // 定义
