using namespace std;
#include "19_Record.h"
#include <iostream>

// 函数重载：函数名称相同，但形参列表不同
// 定义重载函数
Record lookup(const Account &);
// bool lookup(const Account &); // 错误：无法重载仅按返回类型区分的函数
Record lookup(const Phone &);
Record lookup(const Name &);
Account acct;
Phone phone;
Record r1 = lookup(acct);
Record r2 = lookup(phone);

// const_cast和重载
const string &shorterString(const string &s1, const string &s2) {
  return s1.size() <= s2.size() ? s1 : s2;
}
string &shorterString(string &s1, string &s2) {
  // 将本函数的形参s1、s2加上底层const，即可满足上一个函数的形参要求
  auto &r = shorterString(const_cast<const string &>(s1),
                          const_cast<const string &>(s2));
  // 返回之前再将结果的底层const去掉
  return const_cast<string &>(r);
}

// 重载与作用域
// 一旦在当前作用域中找到了所需的名字，编译器就会忽略掉外层作用域中的同名实体
string read();
void print(const string &);
void print(double);
void fooBar(int ival) {
  bool read = false; // 隐藏了外层的read
  // string s = read(); //
  // 错误：编译器只能找到上面布尔类型的变量read，找不到外层的read函数

  // 在函数中定义函数非常不规范，这里仅作演示说明使用
  void print(int); // 隐藏了外层的print
  // print("Value");  // 错误
  print(ival); // 正确
  print(3.14); // 正确：等价于print(3)
}