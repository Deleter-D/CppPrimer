#include "06_Foo2.h"
#include "06_HasPtr.h"
#include "06_StrVec.h"
#include "06_StrVec2.h"
#include <memory>
#include <string>
using namespace std;

// 标准库容器、string和shared_ptr类既支持移动也支持拷贝
// IO类和unique_ptr类可以移动但不能拷贝

// 右值引用
// - 通过&&而不是&来获得右值引用
// - 只能绑定到一个将要销毁的对象

// 左值持久：对象的身份
// 右值短暂：对象的值

struct X {
  int i;    // 内置类型可以移动
  string s; // string定义了自己的移动操作
};
struct hasX {
  X mem; // X有合成的移动操作
};
// Y定义了拷贝构造函数，但未定义移动构造函数
struct Y {
  Y() = default;
  Y(const Y &) = default;
  Y(Y &&) = delete;
};
struct hasY {
  hasY() = default;
  hasY(hasY &&) = default;
  Y mem; // hasY将有一个delete的移动构造函数
};

class Foo {
public:
  Foo() = default;
  Foo(const Foo &) = default;
};

int main(int argc, char const *argv[]) {
  int i = 42;
  int &r = i; // 正确：r引用i
  //   int &&rr = i;     // 错误：不能将一个右值引用绑定到左值上
  //   int &r2 = i * 42; // 错误：i * 42是一个右值
  const int &r3 = i * 42; // 正确：将一个const的引用绑定到一个右值上
  int &&rr2 = i * 42; // 正确：将rr2绑定到乘法的结果上

  // 变量是左值，即使这个变量是右值引用
  // 正确：字面值常量是右值
  int &&rr3 = 42;
  // int &&rr4 = rr3; // 错误：表达式rr3是左值

  // 标准库move函数
  // move告诉编译器，希望像右值一样处理左值
  int &&rr4 = std::move(rr3);

  // 移动构造函数和移动赋值运算符
  // 类似对应的拷贝操作，但它们从给定对象“窃取”资源而不是拷贝资源
  // 见06_StrVec.h
  StrVec strvec1;
  StrVec strvec2 = std::move(strvec1);

  // 合成的移动操作
  // 只有当一个类没有定义任何自己版本的拷贝控制成员
  // 且所有数据成员都能够移动构造或移动赋值时
  // 编译器才会合成移动构造函数或移动赋值运算符
  X x, x2 = std::move(x);       // 使用合成的移动构造函数
  hasX hx, hx2 = std::move(hx); // 使用合成的移动构造函数
  // hasY hy, hy2 = std::move(hy); // 错误：移动构造函数是delete的

  // 移动右值，拷贝左值
  // 移动构造函数、拷贝构造函数同时存在，编译器使用普通的函数匹配规则
  // 赋值运算符的情况也类似

  // 如果没有移动构造函数，右值也将被拷贝
  Foo foo;
  Foo foo2(foo);            // 拷贝构造函数，foo是一个左值
  Foo foo3(std::move(foo)); // 拷贝构造函数，因为未定义移动构造函数

  // 拷贝并交换赋值运算符和移动操作
  HasPtr hp, hp2;
  hp = hp2; // hp2是左值，hp2通过拷贝构造函数将一个副本传入赋值运算符
  hp = std::move(hp2); // 移动构造函数移动hp2

  // 通过移动操作避免对象成员的拷贝造成的额外开销
  // 见06_Message2.h

  // 移动迭代器
  // - 移动迭代器的解引用运算符生成一个右值引用
  // - make_move_iterator函数将一个普通迭代器转换为移动迭代器
  // 见06_StrVec2.h

  // 右值引用和成员函数
  // 见06_StrVec2.h，定义了移动版本的push_back
  StrVec2 strvec21;
  string s = "Hello World!";
  strvec21.push_back(s);      // 拷贝版本
  strvec21.push_back("done"); // 移动版本

  // 右值和左值引用成员函数，引用限定符可以是&或&&
  string str1 = "a value", str2 = "another"; // str1与str2均为左值
  auto n = (str1 + str2).find('a'); // str1 + str2返回一个右值，用右值调用函数
  str1 + str2 = "wow!";             // 对右值进行了赋值
  // 上面两种操作，语法上都是允许的

  // 阻止对一个右值进行赋值
  // 见06_Foo2.h，在赋值运算符后面加上了&限定符
  Foo2 foo20;
  Foo2 foo21, foo22;      // foo21和foo22均为左值
  foo21 = foo22;          // 正确
  foo20.retFoo() = foo22; // 正确
  // foo20.retVal() = foo22; // 错误
  foo21 = foo20.retVal(); // 正确

  // &限定符与const一起使用
  // 见06_Foo2.h，定义了somemem和anothermem函数

  // 重载和引用函数
  // 见06_Foo2.h，定义了两个版本的sorted
  foo20.retFoo().sorted(); // 左值，调用const &版本
  foo20.retVal().sorted(); // 右值，调用&&版本

  // 使用引用限定符需要注意一个细节
  // 见06_Foo2.h，定义了四个版本的sorted2

  return 0;
}
