#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

#include "11_Quote.h"

// 派生类经常(但不总是)覆盖它继承的虚函数
class Bulk_quote : public Quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string &, double, std::size_t, double);
  // 覆盖基类的函数版本以实现基于大量购买的折扣政策
  double net_price(std::size_t) const override;

private:
  std::size_t min_qty = 0; // 最低购买量
  double discount = 0.0;   // 折扣
};

// 派生类必须使用基类的构造函数来初始化继承来的成员
Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty,
                       double disc)
    // 首先初始化基类的部分，然后按照声明的顺序依次初始化派生类的成员
    : Quote(book, p), min_qty(qty), discount(disc) {}

// 派生类使用基类的成员：派生类可以访问基类的公有成员和受保护成员
double Bulk_quote::net_price(std::size_t cnt) const {
  if (cnt >= min_qty)
    return cnt * (1 - discount) * price;
  else
    return cnt * price;
}
#endif