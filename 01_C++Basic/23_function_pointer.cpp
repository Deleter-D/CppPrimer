using namespace std;
#include <iostream>
#include <string>

// 函数指针
bool lengthCompare(const string &, const string &);
// 该函数的类型是bool (const string &, const string &)
// 声明一个可以指向该类型函数的指针，只要用指针替换函数名即可
bool (*pf)(const string &, const string &);

string::size_type sumLength(const string &, const string &);
bool cstringCompare(const char *, const char *);

int main() {
  pf = lengthCompare;  // pf指向名为lengthCompare的函数
  pf = &lengthCompare; // 与上一句等价，取地址符是可选的

  // 可以直接使用函数指针调用该函数，无需提前解引用
  // 下列三种调用方式均等价
  bool b1 = pf("hello", "goodbye");
  bool b2 = (*pf)("hello", "goodbye");
  bool b3 = lengthCompare("hello", "goodbye");

  pf = 0; // 正确：pf不指向任何函数
  // pf = sumLength; // 错误：返回类型不匹配
  // pf = cstringCompare; // 错误：形参类型不匹配
  pf = lengthCompare; // 正确：函数和指针的类型精确匹配
}

// 重载函数的指针
void ff(int *);
void ff(unsigned int);

void (*pf1)(unsigned int) = ff; // pf1指向ff(unsigned int)
// void (*pf2)(int) = ff; //错误：没有任何一个ff与该形参列表匹配
// double (*pf3)(int *) = ff; // 错误：ff和pf3的返回类型不匹配
void (*pf4)(int *) = ff;

// 函数指针形参
// 不能定义函数类型的形参，但是形参可以是指向函数的指针
// 第三个形参是函数类型，它会自动转换成指向函数的指针
void useBigger(const string &s1, const string &s2,
               bool pf(const string &, const string &));
// 等价的定义，显式的将第三个形参定义为函数指针
void useBigger(const string &s1, const string &s2,
               bool (*pf)(const string &, const string &));
void test() {
  string s1, s2;
  // 直接将函数作为实参使用，会自动转换成指针
  useBigger(s1, s2, lengthCompare);
}

// 通过使用类型别名，简化使用函数指针
typedef bool Func(const string &, const string &);
typedef decltype(lengthCompare) Func2; // 与上句类型等价

typedef bool (*FuncP)(const string &, const string &);
typedef decltype(lengthCompare) *FuncP2; // 与上句类型等价

void useBigger(const string &, const string &, Func); // useBigger的等价声明
void useBigger(const string &, const string &, FuncP); // useBigger的等价声明

// 返回指向函数的指针
using F = int(int *, int);      // F是函数类型，不是指针
using FP = int (*)(int *, int); // FP是指针类型

FP f1(int); // 正确：FP是函数指针，f1返回指向函数的指针
// F f1(int); // 错误：F是函数类型，f1不能返回一个函数
F *f1(int); // 正确：显式地指示返回类型是指向函数的指针
// 也可以使用下面的形式直接声明f1
int (*f1(int))(int *, int);
// 还可以使用尾置返回类型的方式
auto f1(int) -> int (*)(int *, int);

// auto和decltype用于函数指针类型
string::size_type smallerLength(const string &, const string &);
string::size_type largerLength(const string &, const string &);
// getFunc根据形参的取值，返回smallerLength或largerLength
// delctype作用于某个函数时，它返回函数类型而非指针类型，因此需要显式的加上*以表明需要返回指针
decltype(smallerLength) *getFunc(const string &);