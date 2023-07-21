#ifndef SIZECOMP_H
#define SIZECOMP_H

#include <string>

class SizeComp {
public:
  // 该形参对应捕获的变量
  SizeComp(size_t n) : sz(n) {}
  // 该调用运算符的返回类型、形参和函数体都与lambda一致
  bool operator()(const std::string &s) const { return s.size() >= sz; }

private:
  size_t sz; // 该数据成员对应通过值捕获的变量
};

#endif