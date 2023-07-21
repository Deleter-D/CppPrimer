#ifndef SALES_DATA_2_H
#define SALES_DATA_2_H

#include <iostream>
#include <string>

struct Sales_data {
  // 构造函数
  // C++11要求编译器生成构造函数
  // 此处的default有效是因为手动为内置类型的数据提供了初始值
  Sales_data() = default;
  // 冒号与大括号之间的部分是构造函数的初始化列表
  Sales_data(const std::string &s) : bookNo(s){};
  Sales_data(const std::string &s, unsigned n, double p)
      : bookNo(s), units_sold(n), revenue(p * n){};
  // 在类的外部定义
  Sales_data(std::istream &);

  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
  // 关于Sales_data对象的操作
  // isbn后面加的const表明该函数为常量成员函数，该函数不会修改这个类对象的数据成员
  std::string isbn() const { return bookNo; } // 等价于return this->bookNo;
  // this是一个指针常量，不允许改变指针里的地址，this的类型是(Sales_data *
  // const)
  /* 常量指针：const int *p; 指向常量的指针
     指针常量：int *const p = &a; 指针本身是常量，必须初始化 */
  Sales_data &combine(const Sales_data &);
  double avg_price() const;
};

// 非成员接口函数
// 若非成员函数是类接口的组成部分，则应该与类在同一头文件中声明
Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);

// 类作用域和成员函数
// 在类的外部定义成员函数
// 编译器首先编译成员的声明，然后才轮到成员函数体
double Sales_data::avg_price() const {
  if (units_sold)
    return revenue / units_sold;
  else
    return 0;
}

// 定义一个返回this对象的函数
// 模拟+=
Sales_data &Sales_data::combine(const Sales_data &rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this; // 返回调用该函数的对象
}

// 定义类相关的非成员函数
// IO对象不能拷贝，只能引用
// 需要修改IO对象，不能使用底层const
std::istream &read(std::istream &is, Sales_data &item) {
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;

  return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
  os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "
     << item.avg_price();
  return os;
}

// 模拟+
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
  Sales_data sum = lhs;
  sum.combine(rhs);

  return sum;
}

// 在类的外部定义构造函数
Sales_data::Sales_data(std::istream &is) { read(is, *this); }

#endif