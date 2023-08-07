#ifndef HASH_SPECIALIZATION_H
#define HASH_SPECIALIZATION_H

#include "17_Sales_data.h"
#include <functional>
#include <iostream>

// 打开std命名空间，对hash进行特例化
namespace std {
template <> struct hash<Sales_data> {
  // 用来散列一个无序容器的类型必须要定义以下类型
  typedef size_t result_type;
  typedef Sales_data argument_type; // 默认情况下，此类型需要==运算符
  size_t operator()(const Sales_data &s) const;
  // 该类使用合成的拷贝控制成员和默认构造函数
};
size_t hash<Sales_data>::operator()(const Sales_data &s) const {
  std::cout << "[Special Hash]" << std::endl;
  return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^
         hash<double>()(s.revenue);
}
} // namespace std

#endif