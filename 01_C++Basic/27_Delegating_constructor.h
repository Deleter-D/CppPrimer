#ifndef DELEGATING_CONSTRUCTOR_H
#define DELEGATEING_CONSTRUCTOR_H

#include <string>

class Delegating_constructor {
public:
  // 非委托构造函数，使用对应的实参初始化成员
  Delegating_constructor(int ival, double dval, std::string sval)
      : i(ival), d(dval), s(sval) {}
  // 其余构造函数全部委托给另一个构造函数
  // 下列这些函数初始化和函数体都会执行
  Delegating_constructor() : Delegating_constructor(0, 0.0, "") {}
  Delegating_constructor(int ival) : Delegating_constructor(ival, 0.0, "") {}
  Delegating_constructor(int ival, double dval)
      : Delegating_constructor(ival, dval, "") {}

private:
  int i;
  double d;
  std::string s;
};

#endif