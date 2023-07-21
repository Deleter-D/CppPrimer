#ifndef LITERAL_CLASS_H
#define LITERAL_CLASS_H

// 字面值常量类
/* 满足如下条件的类称为字面值类：
   1、数据成员必须都是字面值类型
   2、类必须至少有一个constexpr构造函数
   3、数据成员的类内初始值
    3.1、内置类型：必须是一条常量表达式
    3.2、类类型：使用成员自己的constexpr构造函数
   4、类必须使用析构函数的默认定义*/

// 除了算术类型、引用和指针外，某些类也是字面值类型
class Literal_class {
public:
  // constexpr构造函数必须初始化所有数据成员
  // constexpr构造函数体一般来说应该是空的
  // 因为constexpr函数只能有返回语句，而构造函数不能有返回语句
  constexpr Literal_class(bool b = true) : hw(b), io(b), other(b) {}
  constexpr Literal_class(bool h, bool i, bool o) : hw(h), io(i), other(o) {}

  constexpr bool any() const { return hw || io || other; }

  void set_hw(bool b) { hw = b; }
  void set_io(bool b) { io = b; }
  void set_other(bool b) { other = b; }

private:
  bool hw;    // 非IO错误的硬件错误
  bool io;    // IO错误
  bool other; // 其他错误
};

#endif