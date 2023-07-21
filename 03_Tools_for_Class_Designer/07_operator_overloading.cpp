#include <iostream>
using namespace std;

class Data {
public:
  Data() = default;
  Data(const int i) : num(i) {}
  // 成员函数运算符重载
  Data operator+=(const Data &rhs) {
    this->num += rhs.num;
    return *this;
  }

public:
  int num;
};

// 全局运算符重载
Data operator+(const Data &lhs, const Data &rhs) {
  Data data;
  data.num = lhs.num + rhs.num;
  return data;
}

int main(int argc, char const *argv[]) {
  // 重载运算符是具有特殊名称的函数(无默认参数)
  cout << 1 + 2;
  // 一个运算符函数，它要么是类的成员，要么至少含义一个类类型的参数
  // int operator+(int, int); // 错误：不能为int重定义内置的运算符

  // 对于一个重载的运算符，其优先级和结合律与对于的内置运算符保持一致
  // 调用重载运算符
  Data data1, data2;
  data1 + data2;           // 普通表达式
  operator+(data1, data2); // 等价的函数调用

  data1 += data2;          //  基于“调用”的表达式
  data1.operator+=(data2); // 对成员运算符函数的等价调用

  // 通常情况下，不应该重载逗号、取地址符、逻辑与和逻辑或运算符
  // 重载时使用与内置类型一致的含义

  // 重载运算符可以选择作为成员或非成员函数
  // 若将运算符定义为成员函数，则左侧运算对象必须是运算符所属类的一个对象
  string s = "world";
  string t = s + "!";     // 正确：s.operator+("!");
  string u = "hello" + s; // 假设+是string的成员，则错误
  // 等价于"hello".operator+(s);
  // const char*是一种内置类型，没有成员函数
  // 因为string将+定义成了普通的非成员函数
  // 所以"hello" + s等价于operator+("hello", s);

  // 具有对称性的运算符可以转换任意一端的运算对象，通常应该是普通的非成员函数
  return 0;
}

/*
                    可重载的运算符
    ————————————————————————————————————————————————
    +       -       *       /       %       ^
    &       |       ~       !       ,       =
    <       >       <=      >=      ++      --
    <<      >>      ==      !=      &&      ||
    +=      -=      /=      %=      ^=      &=
    |=      *=      <<=     >>=     []      ()
    ->      ->*     new     new[]   delete  delete[]
    ————————————————————————————————————————————————
                  不允许被重载的运算符
    ————————————————————————————————————————————————
    ::      .*      .       ? :
    ————————————————————————————————————————————————
*/