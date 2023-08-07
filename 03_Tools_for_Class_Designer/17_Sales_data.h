#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>

// 前置声明 hash 特化
namespace std {
template <class T> class hash;
}

class Sales_data {

  friend class std::hash<Sales_data>;

public:
  Sales_data() = default;
  Sales_data(const Sales_data &) = default;
  Sales_data(const std::string &s) : bookNo(s) {}
  Sales_data(const std::string &s, unsigned n, double p)
      : bookNo(s), units_sold(n), revenue(p) {}
  std::string isbn() const { return bookNo; }
  ~Sales_data() = default;
  Sales_data &operator=(std::initializer_list<std::string> il);
  Sales_data &operator+=(const Sales_data &rhs);
  Sales_data &operator++();
  Sales_data &operator--();
  Sales_data &operator++(int);
  Sales_data &operator--(int);

public:
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
  double avg_price() const { return units_sold ? revenue / units_sold : 0; }
};

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
  return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^
         hash<double>()(s.revenue);
}
} // namespace std

std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
  os << std::setw(12) << "ISBN" << std::setw(12) << "Sold" << std::setw(12)
     << "Revenue" << std::setw(12) << "Avg Price" << std::endl;
  os << std::setw(12) << item.isbn() << std::setw(12) << item.units_sold
     << std::setw(12) << item.revenue << std::setw(12) << item.avg_price();
  return os;
}

std::istream &operator>>(std::istream &is, Sales_data &item) {
  double price;
  is >> item.bookNo >> item.units_sold >> price;
  if (is)
    item.revenue = item.units_sold * price;
  else
    item = Sales_data();
  return is;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
  Sales_data sum = lhs;
  sum += rhs;
  return sum;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
  return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold &&
         lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
  return !(lhs == rhs);
}

Sales_data &Sales_data::operator=(std::initializer_list<std::string> il) {
  bookNo = *il.begin();
  units_sold = std::stoi(*(il.begin() + 1));
  revenue = std::stod(*(il.begin() + 2));
  return *this;
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

Sales_data &Sales_data::operator++() {
  ++units_sold;
  return *this;
}

Sales_data &Sales_data::operator--() {
  --units_sold;
  return *this;
}

Sales_data &Sales_data::operator++(int) {
  units_sold++;
  return *this;
}

Sales_data &Sales_data::operator--(int) {
  units_sold--;
  return *this;
}

#endif