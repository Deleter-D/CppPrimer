#include "11_Bulk_quote.h"
#include "11_Quote.h"
#include <iostream>
using namespace std;

double print_total(ostream &os, const Quote &item, size_t n);

int main(int argc, char const *argv[]) {
  // 虚函数的调用可能在运行时才被解析
  Quote base("0-201-1", 50);
  print_total(cout, base, 10);
  Bulk_quote derived("0-201-1", 50, 5, .19);
  print_total(cout, derived, 10);

  base = derived;     // 把derived的Quote部分拷贝给base
  base.net_price(20); // 调用Quote::net_price
  // 基类中的虚函数在派生类中隐含地也是一个虚函数
  // 该函数在基类中的形参必须与派生类中的形参严格匹配

  // 如果虚函数使用默认实参，基类和派生类中定义的默认实参最好一致

  // 回避虚函数的机制
  // 强制调用基类中定义的函数版本而不管baseP的动态类型到底是什么
  Bulk_quote *baseP;
  double undiscounted = baseP->Quote::net_price(42);
  // 该调用将在编译时完成解析
  return 0;
}

// final和override说明符
struct B {
  virtual void f1(int) const;
  virtual void f2();
  void f3();
};
struct D1 : B {
  void f1(int) const override; // 正确
  // void f2(int) override;    // 错误：参数列表不匹配
  // void f3() override;       // 错误：f3()是普通函数，不可覆盖
  // void f4() override;       // 错误：f4()在B中不存在
};
struct D2 : B {
  // 从B继承f2()和f3()，覆盖f1(int)
  void f1(int) const final; // 不允许后续的其他类覆盖f1(int)
};
struct D3 : D2 {
  // void f1(int) const; // 错误：D2中声明了final
  void f2(); // 正确，虽然未写override
};

double print_total(ostream &os, const Quote &item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << "#sold: " << n << " total due: " << ret
     << endl;
  return ret;
}