#ifndef SMALLINT_H
#define SMALLINT_H

#include <cstddef>
#include <stdexcept>

class SmallInt {
public:
  SmallInt(int i = 0) : val(i) {
    if (i < 0 || i > 255)
      throw std::out_of_range("Bad SmallInt value");
  }
  // 不能声明返回类型，形参列表必须为空
  operator int() const { return val; }
  // operator int(SmallInt &);             // 错误：不是成员函数
  // int operator int() const;             // 错误：指定了返回类型
  // operator int(int = 0) const;          // 错误：参数列表不为空
  // operator int *() const { return 42; } // 错误：42不是一个指针

private:
  std::size_t val;
};

#endif