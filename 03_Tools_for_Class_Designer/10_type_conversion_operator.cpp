#include "10_SmallInt.h"
#include "10_SmallInt2.h"
#include "10_SmallInt3.h"
#include <iostream>
using namespace std;

// 类型转换运算符是特殊成员函数
// 它负责将一个类类型的值转换成其他类型
// 一般形式为：operator type() const;

struct B;
struct A {
  A() = default;
  A(const B &) {} // 把一个B转换成A
};
struct B {
  operator A() const {} // 也是把一个B转换成A
};
A f(const A &) {}

struct C {
  C(int = 0) {} // 最好不要创建两个转换源都是算术类型的类型转换
  C(double) {}
  operator int() const {} // 最后不要创建两个转换对象都是算术类型的类型转换
  operator double() const {}
};
void f2(long double) {}

struct D {
  D(int) {}
};
struct E {
  E(int) {}
};
void manip(const D &) {}
void manip(const E &) {}

struct F {
  F(double) {}
};
void manip2(const D &) {}
void manip2(const F &) {}

int main(int argc, char const *argv[]) {
  SmallInt si;
  si = 4; // 首先将4隐式转换成SmallInt，然后调用SmallInt::operator=
  si + 3; // 首先将si隐式转换成int，然后执行整数的加法

  // 内置类型转换将double实参转成int
  SmallInt si2 = 3.14; // 调用SmallInt(int)构造函数
  // SmallInt的类型转换运算符将si转换成int
  si + 3.14; // 内置类型转换将所得的int继续转换成double

  // 类型转换运算符可能产生意外结果
  // 假设某行代码写错成了cin << 42;
  // 当istream含有向bool的类中转换时
  // 若发生隐式转换，此处cin将被转换为bool值(0或1)
  // 进而<<运算符将被认为是左移运算符，最终被左移42位
  // 故实际中cin必须显式地转换为bool值，或作为条件时才当作bool值

  // 为了防止转换产生的异常，C++11引入了显式类型转换运算符
  SmallInt2 si3 = 3; // 正确：SmallInt2的构造函数不是explict的
  // si3 + 3; // 错误：此处需要隐式的类型转换，但类的运算符是explict的
  static_cast<int>(si3) + 3; // 正确：显式地请求类型转换

  // 上述情况也有例外
  // 如果表达式被用作条件，编译器会自动应用显式类型转换(它被隐式的执行)
  // - if、while及do语句的条件部分
  // - for语句头的条件表达式
  // - !、||、&&的运算对象
  // - ? :运算符的条件表达式
  // 这里转换的目标一般为bool类型

  // 避免有二义性的转换
  B b;
  // A a = f(b); // 二义性错误：无法判断是f(B::operator A())还是f(A::A(constB&))
  A a1 = f(b.operator A()); // 正确
  A a2 = f(A(b));           // 正确

  // 二义性：转换目标为内置类型的多重类型转换
  C c;
  // 二义性错误：无法判断是f2(C::operator int())还是f2(C::operator double())
  // f2(c);
  long lg;
  // 二义性错误：无法判断是C::C(int)还是C::C(double)
  // C c2(lg);
  short s = 42;
  // 把short提升成int优于把short转换成double
  C c3(s); // 使用C::C(int)

  // 重载函数与转换构造函数
  // manip(10);    // 二义性错误
  manip(D(10)); // 正确：调用manip(const C&)
  // 需要使用构造函数或强制类型转换，通常意味着程序设计的不足

  // 重载函数与用户定义的类型转换
  // 二义性错误：两个不同的用户定义的类型转换都能用于此处
  // manip2(10); // 无法判断D(10)还是F(double(10))
  // 调用重载函数时，如果自定义的类型转换可以匹配，则认为这些类型转换一样好

  // 函数匹配与重载运算符
  SmallInt3 si4, si5;
  SmallInt3 si6 = si4 + si5; // 使用重载的operator+
  // 二义性错误：无法判断将si6转换为int后用内置+还是将0转换为SmallInt3后使用重载的operator+
  // int i = si6 + 0;
  return 0;
}