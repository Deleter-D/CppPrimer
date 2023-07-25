#include "11_Bulk_quote2.h"
#include "11_Quote.h"
#include <iostream>
using namespace std;

// 通过在基类中将析构函数定义成虚函数以确保执行正确的析构函数版本

class B {
public:
  B() {}
  B(const B &) = delete;
};
class D : public B {
  // 未声明任何构造函数
};

class B2 {};
class D2 : public B2 {
public:
  // 默认情况下，基类的默认构造函数初始化对象的基类部分
  // 要想使用拷贝或移动构造函数，必须在构造函数初始化列表中显式调用该构造函数
  D2(const D2 &d) : B2(d) {}
  D2(D2 &&d) : B2(std::move(d)) {}
  // B2::operator=(const B2&)不会自动被调用
  D2 &operator=(const D2 &rhs) {
    B2::operator=(rhs); // 为基类部分赋值
    // 按照过去的方式为派生类的成员赋值
    // 酌情处理自赋值及释放已有资源等情况
    return *this;
  }
  // B2::~B2()将被自动调用执行
  ~D2() {}
};

int main(int argc, char const *argv[]) {
  // 析构函数的属性会被继承，Quote的派生类的析构函数都将是虚函数
  Quote *itemP = new Quote; // 静态类型与动态类型一致
  delete itemP;             // 调用Quote的析构函数
  itemP = new Bulk_quote2;  // 静态类型与动态类型不一致
  delete itemP;             // 调用Bulk_quote2的析构函数

  // 合成拷贝控制与继承
  // - 合成的Bulk_quote默认构造函数运行Disc_quote的默认构造函数，
  //   后者又运行Quote的默认构造函数
  // - Quote的构造函数完成后，继续执行Disc_quote的构造函数
  // - Disc_quote的构造函数完成后，继续执行Bulk_quote的构造函数

  // 派生类中删除的拷贝控制与基类的关系
  // 如果定义了拷贝构造、赋值运算符或析构函数，则编译器不会合成移动构造和移动运算符
  D d; // 正确：D的合成默认构造函数使用B的默认构造函数
  // D d2(d);            // 错误：D的合成拷贝构造函数是被删除的
  // D d3(std::move(d)); // 错误：隐式地使用D的被删除的拷贝构造函数

  // 移动操作与继承
  // 如果定义了一个移动构造函数或移动赋值运算符
  // 则该类的合成拷贝构造函数和拷贝赋值运算符将被定义为删除
  // 见11_Quote.h定义的拷贝和移动的各个操作

  // 派生类的拷贝控制成员
  // 派生类的赋值运算符
  // 派生类的析构函数
  // 见上方B2和D2的定义

  // 构造函数或析构函数调用了某个虚函数
  // 则应该执行与构造函数或析构函数所属类型相对应的虚函数版本

  // 当基类构造函数调用虚函数的派生类版本时
  // 该虚函数可能会访问派生类的成员
  // 然而在执行基类构造函数时，派生类成员尚未初始化

  // 继承的构造函数
  // 见11_Bulk_quote2.h

  return 0;
}
