#include "11_Base.h"
#include "11_Bulk_quote.h"
#include "11_Derived.h"
#include "11_Quote.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  // 派生类对象及派生类向基类的类型转换
  Quote item;      // 基类对象
  Bulk_quote bulk; // 派生类对象
  Quote *p = &item;
  p = &bulk;       // 指向bulk的从Quote继承而来的部分
  Quote &r = bulk; // 绑定到bulk的从Quote继承而来的部分
  // 可以把派生类对象的指针用在需要基类指针的地方

  // 派生类必须使用基类的构造函数来初始化继承来的成员
  // 见11_Bulk_quote.h

  // 派生类使用基类的成员：派生类可以访问基类的公有成员和受保护成员
  // 见11_Bulk_quote.h

  // 继承与静态成员
  // 见11_Derived.h

  // 派生类的声明
  // class Bulk_quote : public Quote; // 错误
  // class Bulk_quote;                // 正确

  // 一个类的基类，同时也可以是一个派生类
  // class Base {};
  // class D1 : public Base {};
  // class D2 : public D1 {};

  // final防止继承发生
  // class NoDerived final {};   // 不能作为基类
  // class Last final : Base {}; // Last是final的，不能继承Last
  // class Bad : NoDerived {};   // 错误
  // class Bad2 : Last {};       // 错误

  // 使用基类的引用或指针时，实际上编译器并不清楚所绑定对象的真实类型
  // - 静态类型(static type)：编译时已知
  // - 动态类型(dynamic type)：运行时才可知
  // 见下方print_total定义

  // 不存在从基类向派生类的隐式类型转换
  Quote base;
  // Bulk_quote *bulkP = &base;  // 错误
  // Bulk_quote &bulkRef = base; // 错误

  Bulk_quote bulk2;
  Quote *itemP = &bulk2; // 正确
  // Bulk_quote *bulkP2 = itemP; // 错误：编译器只能通过检验静态类型类推断
  // 上句可以通过dynamic_cast或static_cast进行转换
  Bulk_quote *bulkP3 = dynamic_cast<Bulk_quote *>(itemP);
  Bulk_quote *bulkP4 = static_cast<Bulk_quote *>(itemP);

  // 对象间不存在类型转换
  Bulk_quote bulk3;   // 派生类对象
  Quote item2(bulk3); // 使用Quote::Quote(const Quote&)构造函数
  item2 = bulk3;      // 调用Quote::operator=(const Quote&)
  return 0;
}

double print_total(ostream &os, const Quote &item, size_t n) {

  // item的静态类型为Quote，动态类型依赖于实参
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << "#sold: " << n << " total due: " << ret
     << endl;
  return ret;
}