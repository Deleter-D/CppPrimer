#include "08_Sales_data.h"
#include "08_StrBlob.h"
#include "08_StrBlobPtr.h"
#include "08_StrVec3.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  // 输入输出运算符必须是非成员函数
  // 重载输出运算符<<
  Sales_data data("9-99999-999", 0, 0);
  cout << data << endl;
  // 重载输入运算符>>
  // 输入运算符必须处理输入可能失败的情况，输出运算符则不需要
  //   Sales_data data2;
  //   cin >> data2;
  //   cout << data2 << endl;

  // 重载算术和关系运算符
  // 通常情况下，把算术和关系运算符定义成非成员函数
  // 如果类同时定义了算术运算符和相关的复合赋值运算符，则通常应使用复合赋值来实现算术运算符
  Sales_data data3("9-99999-999", 2, 88);
  cout << data + data3 << endl;
  // 如果类包含==，则当且仅当<的定义和==产生的结果一致时才定义<运算符
  cout << (data == data3 ? "true" : "false") << endl;
  cout << (data != data3 ? "true" : "false") << endl;

  // 重载赋值运算符
  // 赋值运算符都必须定义为成员函数
  Sales_data data4;
  data4 = {"9-99999-999", "1", "32"};
  cout << data4 << endl;
  // 复合赋值运算符通常情况下也应该定义为类的成员函数
  Sales_data data5("9-99999-999", 3, 120);
  data5 += data3;
  cout << data5 << endl;

  // 重载下标运算符
  // 下标运算符必须是成员函数
  StrVec3 strvec30;
  strvec30.push_back("hello");
  const StrVec3 cstrvec30 = strvec30;
  strvec30[0] = "world";
  // cstrvec30[0] = "world"; // 错误

  // 重载递增和递减运算符
  // 应该定义前置和后置版本,通常被定义为类的成员
  ++data5;
  --data5;
  // 后置版本为了区分,接受一个额外的(不被使用)int类型参数
  // 编译器会为该形参提供一个值为0的实参
  data5++; // 本质上是data5.operator++(0);
  data5--; // 本质上是data5.operator--(0);

  // 重载成员访问运算符
  // 解引用运算符(*)和箭头运算符(->)
  // 箭头运算符必须是类的成员函数,解引用运算符通常也是类的成员函数
  StrBlob a1 = {"hi", "bye", "now"};
  StrBlobPtr p(a1);            // p指向a1中的vector
  *p = "okey";                 // 给a1的首元素赋值
  cout << p->size() << endl;   // 输出4,是a1首元素的大小
  cout << (*p).size() << endl; // 等价于p->size()
  // 对箭头运算符返回值的限定(永远不能丢弃成员访问的含义)
  // 根据类型不同,point->mem分别等价于
  // (*point).mem;            // point是一个内置的指针类型
  // point.operator->()->mem; // point是类的一个对象

  return 0;
}