#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iomanip>
#include <iostream>
#include <list>
#include <string>

class Sales_data {
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
  // 前置版本
  Sales_data &operator++();
  Sales_data &operator--();
  // 后置版本
  Sales_data &operator++(int);
  Sales_data &operator--(int);

public:
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
  double avg_price() const { return units_sold ? revenue / units_sold : 0; }
};

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
  if (is) // 检查输入是否成功
    item.revenue = item.units_sold * price;
  else
    item = Sales_data(); // 输入失败则默认初始化
  return is;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
  Sales_data sum = lhs; // 把lhs的数据成员拷贝给sum
  sum += rhs;           // 把rhs加到sum中
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