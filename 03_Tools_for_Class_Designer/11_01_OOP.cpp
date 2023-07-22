#include <iostream>
#include <string>
using namespace std;

// OOP核心思想
// - 数据抽象：接口与实现分离
// - 继承：定义相似的类，并对其相似关系建模
// - 动态绑定：忽略相似类的区别，以统一的方式使用它们

// 通过继承(inheritance)联系在一起的类构成一种层次关系
// - 基类(base class)：定义共同拥有的成员
// - 派生类(derived class)：定义特有的成员
// - 虚函数(virtual function)：基类希望派生类各自定义自己合适的版本

class Quote {
public:
  std::string isbn() const { return "9-99999-999"; }
  virtual double net_price(std::size_t n) const { return n * 42.42; }
};

// 派生类必须通过使用类派生列表明确指出基类
// 派生列表即下方的public Quote
class Bulk_quote : public Quote {
public:
  // override表明要重写基类的行为
  double net_price(std::size_t n) const override { return n * 24.24; }
};

// 动态绑定(dynamic binding)能用同一段代码分别处理派生类和基类行为
double print_total(ostream &os, const Quote &item, size_t n) {
  // 根据传入item形参的对象类型调用Quote::net_price或Bulk_quote::net_price
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() // 调用Quote::isbn
     << "#sold: " << n << " total due: " << ret << endl;
  return ret;
}

int main(int argc, char const *argv[]) {
  Quote basic;
  Bulk_quote bulk;
  print_total(cout, basic, 20);
  print_total(cout, bulk, 20);
  // 使用基类的引用或指针调用一个虚函数时将发生动态绑定
  // 也叫运行时绑定(run-time binding)
  return 0;
}