#ifndef CONSTREF_H
#define CONSTREF_H

class ConstRef {
public:
  ConstRef(int ii);

private:
  int i;
  const int ci;
  int &ri;
};

// 赋值的方式实现构造函数
// 如果成员是const、引用、或某种未提供默认构造函数的类类型，必须通过构造函数初始列表提供初始值
// ConstRef::ConstRef(int ii)
// {
//     i = ii;  // 正确
//     ci = ii; // 错误
//     ri = i;  // 错误：ri没有被初始化
// }

// 正确：显式地初始化引用和const成员
ConstRef::ConstRef(int ii) : i(ii), ci(ii), ri(i) {}

#endif