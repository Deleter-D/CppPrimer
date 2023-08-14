#include "07_data.h"
#include <iostream>
#include <string>

namespace space1 {
class A {};
class B {};
} // namespace space1
namespace space2 {
class B {};
} // namespace space2

int cout = 0;

// 未命名的命名空间
int i;
namespace {
int i;
}
namespace local {
namespace {
int i;
}
} // namespace local

namespace A {
int m, n;
}
void f() {
  using namespace A;
  std::cout << m * n << std::endl;
}
namespace B {
int m = 16, n = 15, o = 23;
}
int o = 0;
void g() {
  using namespace B;
  ++m; // 将B::m设为17
  // ++o;     // 二义性错误：全局和B中都有o
  ++::o;      // 正确：将全局的o设为1
  ++B::o;     // 正确：将B::o设为24
  int n = 97; // 当前局部的n隐藏了B::n
  ++n;        // 将当前局部的n设为98
}

// 友元
namespace friend_space {
class C {
  // 两个友元，在友元声明之外没有其他声明
  // 这些函数隐式地称为命名空间friend_space的成员
  friend void f(const C &) {} // 根据实参相关的查找规则可以被找到
  friend void f2() {}         // 除非另有声明，否则不会被找到
};
} // namespace friend_space

// 重载
namespace print_space {
void print(int) { std::cout << "print_space::print(int)" << std::endl; }
void print(double) { std::cout << "print_space::print(double)" << std::endl; }
} // namespace print_space
void print(const std::string &) {
  std::cout << "print(const std::string &)" << std::endl;
}
int main(int argc, char const *argv[]) {
  // 每个命名空间都是一个作用域
  space1::B b1;
  space2::B b2;

  // 命名空间可以是不连续的
  // 见07_data.h与07_data.cc
  using dataspace::Data;
  Data data1(1, 2), data2(3, 4);
  Data sum(data1 + data2);
  std::cout << sum << std::endl;

  // using与using namespace

  using std::cout; // 相当于声明
  // 此后使用cout指的是标准库的cout而不是上面的int变量
  cout << ::cout << std::endl; // ::cout指的是全局域中的变量
  // 而using namespace是打开整个命名空间
  // 如果打开了std命名空间，则自定义的全局变量cout会和std::cout重名
  // 编译器会报错

  // 未命名的命名空间
  // 变量拥有静态生命周期
  // i = 10; // 二义性：i既出现在全局作用域，又出现在未命名的作用域
  local::i = 42; // 正确：与全局作用域中的i不同
  // 定义在未命名空间中的名字可以直接使用
  // 未命名的命名空间仅在特定的文件内部有效，其作用范围不会横跨多个不同文件

  // 命名空间的别名
  namespace loc = local;
  loc::i = 100;

  // using声明：一次只引入命名空间的一个成员
  // using指示：与声明不同，所有名称都可见
  // 见上方定义的A、B命名空间

  // 实参相关的查找与类类型实参
  std::string s;
  std::cin >> s;
  // 等价于operator>>(std::cin, s);
  // operator>>可以被直接调用，是因为
  // 除了在常规的作用域查找外，还会查找实参类所属的命名空间

  // 友元声明与实参相关的查找
  // 见上方定义的friend_space命名空间
  friend_space::C cobj;
  f(cobj); // 正确：通过在friend_space::C中的友元声明找到friend_space::f
  // f2(); // 错误：friend_space::f2没有被声明

  // 重载与命名空间
  using namespace print_space;
  // 此时通过print可以匹配到三个函数
  // print_space::print(int)
  // print_space::print(double)
  // ::print(const std::string&)
  int ival = 42;
  print("Value: ");
  print(ival);
  return 0;
}
