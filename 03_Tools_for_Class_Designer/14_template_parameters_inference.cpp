#include <fstream>
#include <iostream>
#include <string>
// #include <type_traits>
#include <utility>
#include <vector>
using namespace std;

template <typename T>
T fobj(T, T) // 实参被拷贝
{
  cout << "fobj(T, T)" << endl;
  return T();
}
template <typename T>
T fref(const T &, const T &) // 实参被引用
{
  cout << "fref(const T &, const T &)" << endl;
  return T();
}

template <typename T> int compare(const T &v1, const T &v2) {
  if (v1 < v2)
    return -1;
  if (v2 < v1)
    return 1;
  return 0;
}

// 实参类型可以不同，但必须兼容
template <typename A, typename B>
int flexibleCompare(const A &v1, const B &v2) {
  if (v1 < v2)
    return -1;
  if (v2 < v1)
    return 1;
  return 0;
}

template <typename T> ostream &print(ostream &os, const T &obj) {
  return os << obj << endl;
}

// 指定显式模板实参
// 编译器无法推断T1，它未出现在函数参数列表中
template <typename T1, typename T2, typename T3> T1 sum(T2 v1, T3 v2) {
  return static_cast<T3>(v1 + v2);
}
// 糟糕的设计：用户必须指定所有三个模板参数
// 按从左到右的顺序与对应的模板参数匹配
template <typename T1, typename T2, typename T3>
T3 alternative_sum(T2 v2, T1 v1) {
  return static_cast<T3>(v2 + v1);
}

// 尾置返回类型与类型转换
// 想要通过迭代器指向的数据类型作为返回类型
// 在编译器遇到函数参数列表之前，beg还未出现，并不知道beg是一个It类型的变量
// 故将返回类型尾置，尾置返回允许在参数列表之后声明返回类型
template <typename It> auto fnc(It beg, It end) -> decltype(*beg) {
  return *beg;
}

// 进行类型转换的标准库模板类
template <typename It>
// 为了使用模板参数的类型成员，必须使用typename
auto fnc2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
  return *beg;
}

// 函数指针和实参推断
void func(int (*)(const string &, const string &)) {}
void func(int (*)(const int &, const int &)) {}

// 从左值引用函数参数推断类型
template <typename T> void lf1(T &) {}       // 实参必须是一个左值
template <typename T> void lf2(const T &) {} // 可以接受一个右值

// 从右值引用函数参数推断类型
template <typename T> void rf1(T &&) {}

// 编写接受右值引用参数的模板函数
template <typename T> void rf2(T &&val) {
  // 若传入一个左值引用int &，T会被折叠为左值引用int &
  T t = val;      // t的类型为int &
  t = 42;         // 改变t的同时会改变val
  if (val == t) { // 这样的判断会恒为true
  }
}

// 转发
// flip1是一个不完整的实现，顶层const和引用丢失了
template <typename F, typename T1, typename T2> void flip1(F f, T1 t1, T2 t2) {
  f(t2, t1);
}
// 注意f的第二个参数是引用
void f(int v1, int &v2) { cout << v1 << " " << ++v2 << endl; }

// 定义能保持类型信息的函数参数
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2) {
  f(t2, t1);
}
// 注意g的第一个参数本身就是右值引用
void g(int &&i, int &j) { cout << i << " " << j << endl; }

// 在调用中使用forward保持类型信息
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
  f(forward<T2>(t2), forward<T1>(t1));
}

int main(int argc, char const *argv[]) {
  // 编译器通常不是对实参进行类型转换，而是生成一个新的模板实例
  // 将实参传递给带模板类型的函数形参时，能够自动应用的类型转换只有
  // const转换及数组或函数到指针的转换
  string s1("a value");
  const string s2("another value");
  fobj(s1, s2); // 调用fobj(string, string)，const被忽略
  fref(s1, s2); // 调用fref(const string&, const string&)
  // 将s1转换为const是允许的

  int a[10], b[42];
  // 调用f(int*, int*)，数组到指针的转换
  fobj(a, b);
  // 错误：数组类型不匹配，引用时会把数组当作整体，数组大小不一样则会类型不匹配
  // fref(a, b);

  // 使用相同模板参数类型的函数形参
  // compare函数接受两个const T&参数
  long lng = 42l;
  // compare(lng, 1024); // 错误：不能实例化compare(long, int)

  // 定义更灵活的compare
  flexibleCompare(lng, 1024); // 正确

  // 正常类型转换应用于普通函数实参，见上方print定义
  // 若函数参数类型不是模板参数，则对实参进行正常的类型转换
  print(cout, 42); // 实例化print(ostream&, int)
  ofstream fos("14_output.txt");
  print(fos, 10); // 使用print(ostream&, int)，将f转换为ostream&

  // 指定显式模板实参
  // 见上方sum和alternative_sum定义
  int i = 42;
  int l = 1024l;
  // T1是显式指定的，T2和T3是从函数实参类型推断而来的
  auto val = sum<long long>(i, l);
  // 错误
  // auto val2 = alternative_sum<long long>(i, l);
  // 正确：显式指定了所有三个参数
  auto val3 = alternative_sum<long, int, long long>(i, l);

  // 正常类型转换应用于显式指定的实参
  long l2 = 512l;
  // compare(l2, 1024);    // 错误：模板参数不匹配
  compare<long>(l2, 1024); // 正确：实例化compare(long, long)
  compare<int>(l2, 1024);  // 正确：实例化compare(int, int)

  // 尾置返回类型与类型转换
  // 见上方定义的fnc
  vector<int> vi = {1, 2, 3, 4, 5};
  vector<string> vs = {"hi", "bye"};
  auto &vi_res = fnc(vi.begin(), vi.end()); // 返回int&
  auto &vs_res = fnc(vs.begin(), vs.end()); // 返回string&

  // 进行类型转换的标准库模板类
  // 见上方定义的fnc2与下表

  // 函数指针和实参推断
  // pf1指向实例int compare(const int&, const int&)
  // 编译器使用指针的类型来推断模板实例
  int (*pf1)(const int &, const int &) = compare;
  // 见上方定义的两个版本的func
  // func(compare);   // 错误：编译器无法推断使用哪个版本的compare实例
  // 正确：显式指定compare的实例化版本
  func(compare<int>); // 传递compare(const int&, const int&)

  // 从左值引用函数参数推断类型
  // 见上方定义的lf1和lf2
  int i2 = 42;
  const int ci = 42;
  // 对lf1的调用使用实参所引用的类型作为模板的参数类型
  lf1(i2); // T为int
  lf1(ci); // T为const int
  // lf1(5);  // 错误：传递给一个&参数的实参必须是一个左值

  // lf2中的参数是const &，实参中的const是无关的
  lf2(i2); // T是int
  lf2(ci); // T是int
  lf2(5);  // T是int，一个const &参数可以绑定到一个右值

  // 从右值引用函数参数推断类型
  // 见上方定义的rf1
  rf1(42); // 实参是int类型的右值，T是int

  // 引用折叠和右值引用参数
  // 通常不能将一个右值引用绑定到一个左值上
  // 左值传递给函数的右值引用参数(模板类型参数)
  // 编译器将推断模板类型参数为实参的左值引用类型
  // - X& &、X& &&、X&& &都将折叠为类型X&
  // - X&& &&将折叠为X&&
  // 引用折叠只能应用于简介创建的引用的引用，如类型别名或模板参数
  rf1(i2); // 实参是左值，T是int &
  rf1(ci); // 实参是左值，T是const int&

  // 编写接受右值引用参数的模板函数
  // 见上方定义的rf2，这是一个有问题的函数
  // 正确的定义方式参考标准库的move函数
  // move告诉编译器，希望将一个左值像右值一样操作
  // 源码中，从一个左值static_cast到一个右值引用是允许的
  string str1("hi"), str2;
  // 正确：从一个右值移动数据
  str2 = move(string("bye!")); // 实例化string&& move(string&&)
  // 正确：但在赋值后，str1的值不确定
  str2 = move(str1); // 实例化string&& move(string&)
  // 具体过程如下：
  // - 推断出T为string&
  // - remove_reference用string&进行实例化
  // - remove_reference<string&>的type成员是string
  // - move的返回类型仍然是string&&
  // - move的函数参数t实例化为string& &&，后折叠为string&

  // 转发
  // 见上方定义的f和flip1
  int i3 = 1024;
  f(42, i3); // 直接调用f，由于第二个参数是引用，故会改变i3的值
  cout << i3 << endl;
  int i4 = 1024;
  flip1(f, i4, 42); // i4的值不会被改变
  cout << i4 << endl;
  // flip1被实例化为void flip1(void(*f)(int, int&), int t1, int t2)
  // 此时t1是i4的一个拷贝，而不是引用，将这个拷贝再传入f时，自然不会改变i4
  // 这就导致封装后的flip1与f的本意不同了

  // 定义能保持类型信息的函数参数
  // 见上方定义的g和flip2
  int i5 = 1024, i6 = 42;
  flip2(f, i5, 42); // f会改变j
  // 实例化为void flip2(void(*fcn)(int, int&),int& t1, int&& t2)
  cout << i5 << endl;
  // flip2(g, i6, 42); // 错误：不能从一个左值初始化int&&
  // 因为右值表达式是一个左值，此时t2是一个右值引用
  // 在使用t2这个右值引用初始化g的第一个形参时
  // 相当于用右值引用表达式初始化一个右值引用，即用左值初始化右值引用
  // 此处不是在模板中，故不会发生引用折叠

  // 在调用中使用forward保持类型信息
  // 见上方定义的flip
  // forward<T>的返回类型是T&&
  // 当用于一个指向目标参数类型的右值引用函数参数(T&&)时
  // forward会保持参数类型的所有细节
  flip(g, i6, 44);
  // i6将以int&传递给g，44将以int&&传递给g

  return 0;
}

/*
                            标准类型转换模板
    —————————————————————————————————————————————————————————————————
    对Mod<T>, 其中Mod为   | 若T为                   | 则Mod<T>::type为
    —————————————————————————————————————————————————————————————————
    remove_reference     | X& / X&&                | X
                         | other                   | T
    —————————————————————————————————————————————————————————————————
    add_const            | X& / const X / function | T
                         | other                   | const T
    —————————————————————————————————————————————————————————————————
    add_lvalue_reference | X&                      | T
                         | X&&                     | X&
                         | other                   | T&
    —————————————————————————————————————————————————————————————————
    add_rvalue_reference | X& / X&&                | T
                         | other                   | T&&
    —————————————————————————————————————————————————————————————————
    remove_pointer       | X*                      | X
                         | other                   | T
    —————————————————————————————————————————————————————————————————
    add_pointer          | X& / X&&                | X*
                         | other                   | T*
    —————————————————————————————————————————————————————————————————
    make_signed          | unsigned X              | X
                         | other                   | T
    —————————————————————————————————————————————————————————————————
    make_unsigned        | 带符号类型               | unsigned X
                         | other                   | T
    —————————————————————————————————————————————————————————————————
    remove_extent        | X[n]                    | X
                         | other                   | T
    —————————————————————————————————————————————————————————————————
    remove_all_extents   | X[n1][n2]...            | X
                         | other                   | T
    —————————————————————————————————————————————————————————————————
*/