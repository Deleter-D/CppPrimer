#include "11_Bulk_quote2.h"
#include <iostream>
using namespace std;

struct Base;
struct Derived;
class Base2;
class D1;
class D2;

int main(int argc, char const *argv[]) {
  // 若一个名字在派生类的作用域内无法解析
  // 则编译器将继续在外层的基类作用域中寻找该名字的定义
  Bulk_quote2 bulk;
  // 1.在Bulk_quote2中查找isbn()失败
  // 2.在Disc_quote中查找失败
  // 3.在Quote中查找成功
  cout << bulk.isbn() << endl;

  // 静态类型决定了哪些成员是可见的
  // 静态类型指编译器在静态时就知道的类型
  Bulk_quote2 bulk2;
  Bulk_quote2 *bulkP = &bulk2; // 静态类型与动态类型一致
  Quote *itemP = &bulk2;       // 静态类型与动态类型不一致
  bulkP->discount_policy();    // 正确
  // itemP->discount_policy(); // 错误：itemP的类型是Quote*

  // 内层作用域(派生类)的名字隐藏定义在外层作用域(基类)的名字
  // 派生类的成员将隐藏同名的基类成员
  // 见下方定义的Derived
  Base b;
  Derived d;
  b.memfnc();   // 调用Base::memfnc()
  d.memfnc(10); // 调用Derived::memfnc()
  // d.memfnc();    // 错误：被隐藏，无法调用
  d.Base::memfnc(); // 正确

  // 虚函数的作用域
  Base2 bobj;
  D1 d1obj;
  D2 d2obj;
  // bp1、bp2、bp3的静态类型均为Base
  Base2 *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
  // 静态类型与动态类型一致
  bp1->fnc(); // 虚调用：将在运行时调用Base::fnc()
  // 动态类型为D1，但并没有对Base中的fnc进行override
  bp2->fnc(); // 虚调用：将在运行时调用Base::fnc()
  // 动态类型为D2，在D2中对Base::fnc()进行了override
  bp3->fnc(); // 虚调用：将在运行时调用D2::fnc()

  D1 *d1p = &d1obj;
  D2 *d2p = &d2obj;
  // bp2->f2(); // 错误：Base没有名为f2的成员
  d1p->f2(); // 虚调用：将在运行时调用D1::f2()
  d2p->f2(); // 虚调用：将在运行时调用D2::f2()

  Base2 *p1 = &d2obj;
  D1 *p2 = &d2obj;
  D2 *p3 = &d2obj;
  // p1->fnc(42); // 错误：Base中没有一个接受int的fnc
  p2->fnc(42); // 静态绑定，调用D1::fnc(int)
  p3->fnc(42); // 静态绑定，调用D2::fnc(int)

  return 0;
}

struct Base {
  Base() : mem(0) {}
  int memfnc() {}

protected:
  int mem;
};

struct Derived : Base {
  Derived() : mem(0) {}
  // 用i初始化Derived::mem
  // 而Base::mem进行默认初始化
  Derived(int i) : mem(i) {}
  // 返回Derived::mem
  int get_mem() { return mem; }
  // 同名函数不会重载，只会隐藏
  int memfnc(int i) {} // 隐藏基类的memfnc

protected:
  // 隐藏基类中的mem
  int mem;
};

class Base2 {
public:
  virtual int fnc() {}
};
class D1 : public Base2 {
public:
  // 隐藏基类的fnc，该fnc不是虚函数，D1继承了Base2::fnc()的定义
  int fnc(int) {}      // 形参列表与Base2中的fnc不一致
  virtual void f2() {} // 一个新的虚函数，Base2中不存在
};
class D2 : public D1 {
public:
  int fnc(int) {} // 一个非虚函数，隐藏了D1：：fnc(int)
  int fnc() {}    // override了Base2的虚函数fnc()
  void f2() {}    // override了D1的虚函数f2()
};