#include <iostream>
using namespace std;

// 枚举类型将一组整型常量组织在一起
// 不限定作用域：enum
// 限定作用域：enum class(struct)

// 限定作用域的枚举类型
enum class open_modes { input, output, append };
// 不限定作用域的枚举类型
enum color { red, yellow, green };
// 未命名的、不限定作用域的枚举类型
enum { floatPrec = 6, doublePrec = 10, double_doublePrec = 10 };

// 错误：与上面的color重复定义了枚举成员
// enum stoplight { red, yellow, green };
// 正确：枚举成员被隐藏了
enum class peppers { red, yellow, green };

enum intTypes {
  charTyp = 8,
  shortTyp = 16,
  intTyp = 16,
  longTyp = 32,
  long_longTyp = 64
};

enum intValues : unsigned long long {
  charTyp = 255,
  shortTyp = 65535,
  intTyp = 65535,
  longTyp = 4294967295UL,
  long_longTyp = 18446744073709551615ULL
};

enum Tokens { INLINE = 128, VIRTUAL = 129 };
void ff(Tokens) {}
void ff(int) {}

void newf(unsigned char) {}
void newf(int) {}

int main(int argc, char const *argv[]) {
  // 限定作用域的枚举类型，在作用域外是不可访问的
  color eyes = green;
  // 错误：peppers的枚举成员不再有效作用域中
  // color::green在有效作用域中，但类型错误
  // peppers p = green;
  color hair = color::red;   // 正确
  peppers p2 = peppers::red; // 正确：显式使用peppers的成员

  // 默认情况下，枚举值从0开始，依次加1
  // 也可以指定值，指定值时可以重复，见上方定义的intTypes

  // 和类一样，枚举也定义新的类型
  // color red1 = 1; // 错误
  int i = color::red; // 正确：不限定作用域的枚举类型的枚举成员隐式转换成int
  // int j = peppers::red; // 错误：限定作用域的枚举类型不会隐式转换

  // 指定enum的大小
  // 默认情况下限定作用域的enum成员类型是int
  // 不限定作用域的enum成员没有默认类型
  // 不同编译器的情况会有所不同，但潜在的类型是足够大的
  // 可以手动指定成员类型，见上方定义的intValues

  // 形参匹配与枚举类型
  // 见上方定义的Tokens
  Tokens curTok = INLINE;
  ff(128);    // 精确匹配ff(int)
  ff(INLINE); // 精确匹配ff(Tokens)
  ff(curTok); // 精确匹配ff(Tokens)

  // 可以将一个不限定作用域的枚举类型的对象或枚举成员传给整型形参
  unsigned char uc = VIRTUAL;
  newf(VIRTUAL); // 调用newf(int)
  newf(uc);      // 调用newf(unsigned char)
  // 不管Tokens的潜在类型是什么，它的对象和枚举成员都将提升成int
  return 0;
}