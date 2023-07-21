#ifndef SMALLINT3_H
#define SMALLINT3_H

#include <cstddef>
#include <stdexcept>

class SmallInt3 {
  // 非成员函数
  friend SmallInt3 operator+(const SmallInt3 &lhs, const SmallInt3 &rhs) {
    SmallInt3 si;
    si.val = lhs.val + rhs.val;
    return si;
  }

public:
  SmallInt3(int i = 0) : val(i) {}
  operator int() const { return val; }

private:
  std::size_t val;
};

#endif