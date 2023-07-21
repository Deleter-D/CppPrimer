#ifndef SALES_DATA_3_H
#define SALES_DATA_3_H

#include <iostream>
#include <string>

// class和struct定义类唯一的区别就是默认的访问权限不同
// class的默认访问权限是private
class Sales_data {
  // 友元
  // 允许其他类或函数访问自己的非公有成员
  friend Sales_data add(const Sales_data &, const Sales_data &);
  friend std::ostream &print(std::ostream &, const Sales_data &);
  friend std::istream &read(std::istream &, Sales_data &);

public: // 访问说明符
  Sales_data() = default;
  Sales_data(const std::string &s) : bookNo(s){};
  Sales_data(const std::string &s, unsigned n, double p)
      : bookNo(s), units_sold(n), revenue(p * n){};
  Sales_data(std::istream &);
  std::string isbn() const { return bookNo; }
  Sales_data &combine(const Sales_data &);

private:
  std::string bookNo;
  unsigned units_sold = 0;
  double revenue = 0.0;
  double avg_price() const { return units_sold ? revenue / units_sold : 0; }
};

// 友元的声明仅指定了访问的权限，而非一个通常意义上的函数声明
// 因此必须在友元声明之外，专门对函数进行一次声明
Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);

// 定义
Sales_data::Sales_data(std::istream &is) { read(is, *this); }

Sales_data &Sales_data::combine(const Sales_data &rhs) {
  units_sold += rhs.units_sold;
  revenue += rhs.revenue;
  return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
  Sales_data sum = lhs;
  sum.combine(rhs);

  return sum;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
  os << item.isbn() << " " << item.units_sold << " " << item.revenue << " "
     << item.avg_price();
  return os;
}

std::istream &read(std::istream &is, Sales_data &item) {
  double price = 0;
  is >> item.bookNo >> item.units_sold >> price;
  item.revenue = price * item.units_sold;

  return is;
}

#endif