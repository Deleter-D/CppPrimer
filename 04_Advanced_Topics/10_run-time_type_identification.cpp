#include <iostream>
using namespace std;

// 运行时类型识别RTTI
//  - typeid运算符，用于返回表达式的类型
//  - dynamic_cast运算符，用于将基类的指针或引用安全地转换成派生类的指针或引用

struct Base {
  // 在可能的情况下，最好定义虚函数而非直接接管类型管理的重任
  virtual ~Base(){};
};

struct Derived : public Base {};

void cast_to_ref(const Base &b) {
  try {
    const Derived &d = dynamic_cast<const Derived &>(b);
  } catch (bad_cast) {
    cout << "Called function with an object that is not a Derived" << endl;
  }
}

class BaseClass {
  friend bool operator==(const BaseClass &, const BaseClass &);

public:
protected:
  virtual bool equal(const BaseClass &) const;
  int data;
};
class DerivedClass : public BaseClass {
public:
protected:
  bool equal(const BaseClass &) const;
};
bool BaseClass::equal(const BaseClass &rhs) const {
  return this->data == rhs.data;
}
bool DerivedClass::equal(const BaseClass &rhs) const {
  // 此处清楚两个类型是相等的，故转换过程不会抛出异常
  auto r = dynamic_cast<const DerivedClass &>(rhs);
  if (r.data == this->data)
    return true;
  else
    return false;
}
bool operator==(const BaseClass &lhs, const BaseClass &rhs) {
  return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

int main(int argc, char const *argv[]) {
  Base *bp;
  bp = new Derived; // bp实际指向派生类对象
  // 在条件部分执行dynamic_cast可以确保类型转换和结果检查在同一表达式中完成
  if (Derived *dp = dynamic_cast<Derived *>(bp)) {
    puts("Use the Derived object to which dp points");
  } else {
    puts("Use the Base object to which bp points");
  }

  // 改写成使用引用类型
  // 此时就不可以作为条件语句了
  // 见上方定义的cast_to_ref
  bp = new Base;
  cast_to_ref(*bp);

  // 使用typeid运算符
  Derived *dp2 = new Derived;
  Base *bp2 = dp2; // 两个指针都指向Derived对象
  // 运行时比较两个对象的类型
  if (typeid(*bp2) == typeid(*dp2))
    cout << "bp2 and dp2 have the same type" << endl;
  // 运行时检查类型是否是某种给定类型
  if (typeid(*bp2) == typeid(Derived))
    cout << "bp2 is a Derived" << endl;
  // 下面的检查永远是失败的：bp2的类型是指向Base的指针
  if (typeid(bp2) == typeid(Derived)) {
  }
  // 当typeid作用于指针(而非对象)时，返回的结果是该指针的静态编译时类型

  // 虚函数的坏处
  // - 虚函数的基类版本和派生类版本必须具有相同的形参类型

  // 使用RTTI
  // 详见上面定义的BaseClass中的重载==运算符

  // type_info类创建对象的唯一途径是使用typeid运算符
  int arr[10];
  Derived d;
  Base *p = &d;
  cout << typeid(42).name() << ",\n"
       << typeid(arr).name() << ",\n"
       << typeid(string).name() << ",\n"
       << typeid(p).name() << ",\n"
       << typeid(*p).name() << endl;

  return 0;
}

/*
                               type_info类的操作
    —————————————————————————————————————————————————————————————————————————
    t1 == t2      | 如果type info对象t1和t2表示同种类型，返回true，否则返回false
    t1 != t2      | 如果type info对象t1和t2表示不同类型，返回true，否则返回false
    t.name()      | 返回一个C风格字符串，表示类型名字的可打印形式
                  | 类型名字的生成方式因系统而异
    t1.before(t2) | 返回一个bool值，表示t1是否位于t2之前
                  | before所采用的顺序关系是依赖于编译器的
    —————————————————————————————————————————————————————————————————————————
*/