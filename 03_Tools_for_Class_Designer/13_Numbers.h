#ifndef NUMBERS_H
#define NUMBERS_H

// 模板默认实参与类模板
template <class T = int> class Numbers {
public:
  Numbers(T v = 0) : val(v) {}

private:
  T val;
};

#endif