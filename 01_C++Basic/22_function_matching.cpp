using namespace std;
#include "19_Record.h"
#include <iostream>

// 函数匹配
// 寻找最佳匹配，不能具有二义性，若具有二义性，编译器将拒绝请求
void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);

/* 编译器将实参类型到形参类型的转换划分了几个等级：
    1、精确匹配
    2、通过const转换实现的匹配
    3、通过类型提升实现的匹配
    4、通过算术类型转换实现的匹配
    5、通过类类型转换实现的匹配
*/

void ff(int);
void ff(short);

void manip(long);
void manip(float);

Record lookup(Account &);
Record lookup(const Account &);

int main() {
  // 函数f测试
  f(5.6); // 调用void f(double, double)
  // f(42, 2, 56); // 错误：具有二义性

  // 函数ff测试
  // char转换为int是类型提升，等级3
  // char转换为short是算术类型转换，等级4
  ff('a'); // 故char提升成int，调用ff(int);

  // 函数manip测试
  // 所有算术类型转换的级别都一样
  // manip(3.14); // 错误：具有二义性

  // 函数lookup测试
  const Account a;
  Account b;
  lookup(a); // 调用lookup(const Account &)
  lookup(b); // 调用lookup(Account &)
}
