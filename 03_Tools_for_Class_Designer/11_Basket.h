#ifndef BASKET_H
#define BASKET_H

#include "11_Quote.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

double print_total(std::ostream &, const Quote &, std::size_t);

class Basket {
public:
  // Basket使用合成的默认构造函数和拷贝控制成员
  void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
  // 打印每本书的总价和购物篮中所有书的总价
  double total_receipt(std::ostream &) const;

  // 重新定义add_item
  void add_item(const Quote &sale) {
    items.insert(std::shared_ptr<Quote>(sale.clone()));
  }
  void add_item(Quote &&sale) {
    items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
  }

private:
  // 该函数用于比较shared_ptr，multiset成员会用到
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs) {
    return lhs->isbn() < rhs->isbn();
  }
  // multiset保存多个报价，按照compare成员排序
  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

double Basket::total_receipt(std::ostream &os) const {
  double sum = 0.0; // 保存实时计算出的总价
  // iter指向ISBN相同的一批元素中的第一个
  // upper_bound返回一个迭代器，指向这批元素的尾后
  for (auto iter = items.cbegin(); iter != items.cend();
       iter = items.upper_bound(*iter)) {
    sum += print_total(os, **iter, items.count(*iter));
  }
  os << "Total Sale: " << sum << std::endl;
  return sum;
}

double print_total(std::ostream &os, const Quote &quote, std::size_t count) {
  double sum = quote.net_price(count);
  os << std::setw(12) << "ISBN" << std::setw(12) << "Count" << std::setw(12)
     << "Price\n";
  os << std::setw(12) << quote.isbn() << std::setw(12) << count << std::setw(12)
     << sum << "\n";
  return sum;
}

#endif