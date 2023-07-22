#include <iostream>
using namespace std;

class Pal;

class Base {
  friend class Pal;

public:
  void pub_mem() {}
  std::size_t size() const { return n; }

protected:
  int prot_mem;
  std::size_t n;

private:
  char priv_mem;
};

class Sneaky : public Base {
  friend void clobber(Sneaky &); // 能访问Sneaky::prot_mem
  friend void clobber(Base &);   // 不能访问Base::prot_mem
  int j;
};

// 派生类友元对于一个基类对象中的protected成员没有任何访问特权
void clobber(Sneaky &s) { s.j = s.prot_mem = 0; } // 正确
// void clobber(Base &b) { b.prot_mem = 0; }      // 错误

// 某个类对其继承来的成员的访问权限受到两个因素的影响
// - 在基类中该成员的访问说明符
// - 在派生类的派生列表中的访问说明符
struct Pub_Derv : public Base {
  int f() { return prot_mem; } // 正确
  // int g() { return priv_mem; } // 错误
};
struct Priv_Derv : private Base { // private不影响派生类的访问权限
  int f1() const { return prot_mem; }
};

struct Derived_from_Public : public Pub_Derv {
  int use_base() { return prot_mem; } // 仍然是protected的
};

struct Derived_from_Private : public Priv_Derv {
  // int use_base() { return prot_mem; } // 错误
};

int main(int argc, char const *argv[]) {
  // 派生类访问说明符的目的是控制派生类用户对于基类成员的访问权限
  Pub_Derv d1;
  Priv_Derv d2;
  d1.pub_mem();
  // d2.pub_mem(); // 错误：pub_mem在派生类中是private的
  return 0;
}

// Pal能够访问Base的成员，这种访问包括了Base对象内嵌在其他派生类对象中的情况
class Pal {
public:
  int f(Base b) { return b.prot_mem; } // 正确
  // int f2(Sneaky s) { return s.j; }  // 错误：Pal不是Sneaky的友元
  // 对基类的访问权限由基类本身控制
  // 即使对于派生类的基类部分也是如此
  int f3(Sneaky s) { return s.prot_mem; } // 正确，虽然看起来奇怪
};

// 友元关系不能继承
class D2 : public Pal {
public:
  // int mem(Base b) { return b.prot_mem; } // 错误：友元关系不能继承
};

// 通过使用using改变个别成员的可访问性
// 派生类只能为那些它可以访问的名字提供using声明
class Derived : private Base { // private继承
public:
  // 保持对象size相关的成员的访问级别
  using Base::size; // size()被保留为public权限

protected:
  using Base::n; // n被保留为protected权限
};

// 默认的继承保护级别
// class Base {};
// struct D1 : Base {}; // 默认public继承
// class D2 : Base {};  // 默认private继承