#include <iostream>
using namespace std;

// 局部类可以定义在某个函数的内部
// 局部类的所有成员都必须完整定义在类的内部

int a, val;
void foo(int val) {
  static int si;
  enum Loc { a = 1024, b };

  struct Bar {  // Bar是foo的局部类
    Loc locVal; // 正确：使用一个局部类型名
    int barVar;

    void fooBar(Loc i = a) { // 正确：默认实参是Loc::a
      // 局部类不能使用函数作用域中的变量
      // barVar = ::val; // 正确：使用一个全局对象
      barVar = si; // 正确：使用一个静态局部对象
      locVal = b;  // 正确：使用一个枚举成员
    }
  };
}

// 可以在局部类的内部再嵌套一个类
// 局部类内的嵌套类也是一个局部类
void foo2() {
  class Bar {
  public:
    class Nested;
  };
  class Bar::Nested {};
}
