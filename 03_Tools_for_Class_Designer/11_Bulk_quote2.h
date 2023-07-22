#ifndef BULK_QUOTE2_H
#define BULK_QUOTE2_H

#include "11_Disc_quote.h"

class Bulk_quote2 : public Disc_quote {
public:
  Bulk_quote2() = default;
  Bulk_quote2(const std::string &book, double price, std::size_t qty,
              double disc)
      // 派生类构造函数只初始化它的直接基类
      : Disc_quote(book, price, qty, disc) {}
  double net_price(std::size_t) const override;
};

double Bulk_quote2::net_price(std::size_t cnt) const {
  if (cnt >= quantity)
    return cnt * (1 - discount) * price;
  else
    return cnt * price;
}

#endif