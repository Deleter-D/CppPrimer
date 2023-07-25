#ifndef BULK_QUOTE2_H
#define BULK_QUOTE2_H

#include "11_Disc_quote.h"

class Bulk_quote2 : public Disc_quote {
public:
  // 继承Disc_quote的构造函数
  // 下句等价于下方在初始化列表中直接调用Disc_quote的构造函数
  // using Disc_quote::Disc_quote;
  Bulk_quote2() = default;
  Bulk_quote2(const std::string &book, double price, std::size_t qty,
              double disc)
      // 派生类构造函数只初始化它的直接基类
      : Disc_quote(book, price, qty, disc) {}
  double net_price(std::size_t) const override;

  Bulk_quote2 *clone() const & { return new Bulk_quote2(*this); }
  Bulk_quote2 *clone() && { return new Bulk_quote2(std::move(*this)); }
};

double Bulk_quote2::net_price(std::size_t cnt) const {
  if (cnt >= quantity)
    return cnt * (1 - discount) * price;
  else
    return cnt * price;
}

#endif