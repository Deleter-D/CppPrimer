#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// 静态成员与类本身关联，而不需要与每个对象关联
// 静态成员存在于任何对象之外，所有对象共享
class Account {
public:
  void calculate() { amount += amount * interestRate; }
  // static函数不包含this指针，所以不能定义为const函数
  static double rate() { return interestRate; }
  static void rate(double);

private:
  std::string owner;
  double amount;
  static double interestRate;
  static double initRate();

  // 静态成员的类内初始化
  // 通常，类的静态成员不该在类的内部初始化
  // 但如果是常量表达式，可以用字面值替换
  static constexpr int period = 30;
  double daily_tbl[period]; // 编译器会将此处的period当作30来用
};

// 一个不带初始值的静态成员的定义
constexpr int
    Account::period; // 若初始值在类的定义内提供，则外部定义不可以指定初始值
// 即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类外部定义一下该成员

// static关键字只出现在类内部的声明语句中
void Account::rate(double newRate) { interestRate = newRate; }

#endif