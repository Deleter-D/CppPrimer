#ifndef SMALLINT2_H
#define SMALLINT2_H

#include <cstddef>
#include <stdexcept>

class SmallInt2 {
public:
  SmallInt2(int i = 0) : val(i) {
    if (i < 0 || i > 255)
      throw std::out_of_range("Bad SmallInt value");
  }
  // 声明为explict的
  explicit operator int() const { return val; }

private:
  std::size_t val;
};

#endif