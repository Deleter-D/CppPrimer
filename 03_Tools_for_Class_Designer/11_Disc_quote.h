#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H

#include "11_Quote.h"
#include <utility>

class Disc_quote : public Quote {
public:
  Disc_quote() = default;
  Disc_quote(const std::string &book, double price, std::size_t qty,
             double disc)
      : Quote(book, price), quantity(qty), discount(disc) {}
  // 在函数声明后加上 = 0 可定义为纯虚函数
  double net_price(std::size_t) const = 0;

  std::pair<std::size_t, double> discount_policy() const {
    return {quantity, discount};
  }

protected:
  std::size_t quantity = 0;
  double discount = 0.0;
};

#endif