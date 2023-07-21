#ifndef FOO2_H
#define FOO2_H

#include <algorithm>
#include <vector>

class Foo2 {
public:
  Foo2() = default;
  Foo2 &operator=(const Foo2 &) &; // 只能向可修改的左值赋值
  ~Foo2() = default;
  Foo2 &retFoo(); // 返回一个引用，是左值
  Foo2 retVal();  // 返回一个值，是右值

  // 正确
  Foo2 somemem() const &;
  // 错误：const限定符必须在前
  // Foo2 anothermem() & const;

  // &&限定本对象是右值
  Foo2 sorted() &&;
  // const &限定本对象是左值，且为const
  Foo2 sorted() const &;

  // 若一个成员函数有引用限定符
  // 则具有相同参数列表的所有版本都必须有引用限定符
  Foo2 sorted2() &&;
  // Foo2 sorted2() const; // 错误：必须加上引用限定符
  using Comp = bool(const int &, const int &);
  Foo2 sorted2(Comp *);       // 正确：参数列表不同
  Foo2 sorted2(Comp *) const; // 正确：两个版本都没有引用限定符

private:
  std::vector<int> data;
};

Foo2 &Foo2::operator=(const Foo2 &rhs) & { return *this; }

Foo2 &Foo2::retFoo() { return *this; }
Foo2 Foo2::retVal() { return *this; }

// 本对象为右值，因此可以原址排序
Foo2 Foo2::sorted() && {
  std::sort(data.begin(), data.end());
  return *this;
}

// 本对象是一个const或是一个左值，不能对其进行原址排序
Foo2 Foo2::sorted() const & {
  Foo2 ret(*this);                             // 拷贝一个副本
  std::sort(ret.data.begin(), ret.data.end()); // 排序副本
  return ret;
}

#endif