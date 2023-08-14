#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Animal {
public:
  Animal(){};
  Animal(string name, bool onExhibit) : name(name), onExhibit(onExhibit) {}
  string name;
  bool onExhibit;
  float max_weight() const {}
};
class Endangered {
public:
  Endangered(){};
  Endangered(bool isEndangred) : isEndangred(isEndangred) {}
  static const bool critical = true;
  static const bool notCritical = false;
  bool isEndangred;
  float max_weight() const {}
};
class Bear : public Animal {
public:
  Bear(){};
  Bear(string name, bool onExhibit, string variety)
      : Animal(name, onExhibit), variety(variety) {}
  string variety;
};

// 派生类的派生列表中可以包含多个基类
class Panda : public Bear, public Endangered {
public:
  // 需要同时构造并初始化它的所有基类子对象
  // 且只能初始化它的直接基类
  Panda(string name, bool onExhibit)
      // 显式初始化所有基类
      : Bear(name, onExhibit, "panda"), Endangered(Endangered::critical) {}
  // 隐式使用Bear的默认构造函数初始化Bear子对象
  Panda() : Endangered(Endangered::critical) {}
  float max_weight() const {
    return max(Animal::max_weight(), Endangered::max_weight());
  }
};

// panda对象初始化顺序
// - Animal-->Bear-->Endangered-->Panda
// panda对象析构函数调用顺序
// - Panda-->Endangered-->Bear-->Animal

// 继承的构造函数与多重继承
struct Base1 {
  Base1() = default;
  Base1(const string &) {}
  Base1(shared_ptr<int>) {}
};
struct Base2 {
  Base2() = default;
  Base2(const string &) {}
  Base2(int) {}
};

// 错误：D1试图从两个基类中都继承D1::D1(const string&)
struct D1 : public Base1, public Base2 {
  using Base1::Base1; // 从Base1继承构造函数
  using Base2::Base2; // 从Base2继承构造函数
};

struct D2 : public Base1, public Base2 {
  using Base1::Base1; // 从Base1继承构造函数
  using Base2::Base2; // 从Base2继承构造函数
  // D2必须自定义一个接受string的构造函数
  D2(const string &s) : Base1(s), Base2(s) {}
  D2() = default;
};

// 类型转换与多个基类
void print(const Bear &b) {
  cout << b.name << " is" << (b.onExhibit ? "" : " not")
       << " on exhibit, and it is a " << b.variety << endl;
}
void highlight(const Endangered &) { cout << "highlight" << endl; }
ostream &operator<<(ostream &os, const Animal &a) {
  os << a.name << " is" << (a.onExhibit ? "" : " not") << " on exhibit" << endl;
}

// 虚继承
// 两个类拥有共同的基类
// public与virtual顺序随意
class LittleDog : public virtual Animal {
public:
  LittleDog() = default;
  LittleDog(string name, bool onExhibit) : Animal(name, onExhibit) {}
};
class BigDog : virtual public Animal {
public:
  BigDog() = default;
  BigDog(string name, bool onExhibit) : Animal(name, onExhibit) {}
};
class AkitaDog : public LittleDog, public BigDog {
public:
  AkitaDog() = default;
  AkitaDog(string name, bool onExhibit)
      // 由最底层的类直接初始化共享的基类
      : Animal(name, onExhibit), LittleDog(name, onExhibit),
        BigDog(name, onExhibit) {}
};
void dance(const LittleDog &) {}
void jump(const BigDog &) {}

int main(int argc, char const *argv[]) {
  // D1 d1("hello"); // 错误：D1试图从两个基类中都继承D1::D1(const string&)
  D2 d2("hello");
  Panda ying_yang("ying_yang", false);
  print(ying_yang);          // 把panda对象传递给一个Bear引用
  highlight(ying_yang);      // 把panda对象传递给一个Endangered引用
  cout << ying_yang << endl; // 把panda对象传递给一个Animal引用
  // 对编译器而言，转换到任意一种基类都一样好

  // 多重继承下的类作用域
  // 若Animal和Endangered中都定义了max_weight()
  // 且Panda没有定义该成员，则下面的调用是错误的
  float weight = ying_yang.max_weight();
  // 为了避免二义性错误，需要为派生类也提供一个版本

  // 虚继承
  // 见上方定义的AkitaDog类及其基类
  AkitaDog akita;
  dance(akita); // 把AkitaDog对象当作LittleDog传递
  jump(akita);  // 把AkitaDog对象当作BigDog传递

  // 构造函数与虚继承
  // 虚基类总是先于非虚基类构造，与它们在继承体系中的次序和位置无关
  return 0;
}
