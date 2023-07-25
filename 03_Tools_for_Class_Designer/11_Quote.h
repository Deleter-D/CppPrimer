#ifndef QUOTE_H
#define QUOTE_H

#include <string>

class Quote {
public:
  Quote() = default;                         // 对成员依次默认初始化
  Quote(const Quote &) = default;            // 对成员依次拷贝
  Quote(Quote &&) = default;                 // 对成员依次拷贝
  Quote &operator=(const Quote &) = default; // 拷贝赋值
  Quote &operator=(Quote &&) = default;      // 移动赋值
  Quote(const std::string &book, double sales_price)
      : bookNo(book), price(sales_price) {}
  std::string isbn() const { return bookNo; }
  // 返回给定数量的书籍销售总额
  // 派生类负责改写并使用不同的版本的算法
  virtual double net_price(std::size_t n) const { return n * price; }
  // 基类通常都应该定义一个虚析构函数
  // 即使该函数不执行任何实际操作也是如此
  virtual ~Quote() = default;

  // 该虚函数返回当前对象的一份动态分配的拷贝
  virtual Quote *clone() const & { return new Quote(*this); }
  virtual Quote *clone() && { return new Quote(std::move(*this)); }

private:
  std::string bookNo;

protected:
  // 派生类需要访问的基类成员一般定义为protected
  double price = 0.0;
};

#endif