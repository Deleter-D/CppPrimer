#ifndef HASPTR_H
#define HASPTR_H

#include <string>

class HasPtr {
  friend void swap(HasPtr &, HasPtr &);

public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
  HasPtr(const HasPtr &p) : ps(new std::string(*p.ps)), i(p.i) {}
  // 添加移动构造函数
  HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }
  // 该赋值运算符既是移动赋值运算符，也是拷贝赋值运算符
  // 参数既不是左值引用&，也不是右值引用&&
  // 参数传入时可能发生拷贝，也可能发生移动
  // 如果发生拷贝，则该运算符为拷贝赋值运算符，发生移动，则为移动赋值运算符
  HasPtr &operator=(HasPtr);
  ~HasPtr() { delete ps; }

private:
  std::string *ps;
  int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs) {
  using std::swap;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
}

HasPtr &HasPtr::operator=(HasPtr rhs) {
  swap(*this, rhs);
  return *this;
}

#endif