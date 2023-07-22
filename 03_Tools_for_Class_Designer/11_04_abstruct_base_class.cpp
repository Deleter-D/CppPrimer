#include "11_Bulk_quote.h"
#include "11_Disc_quote.h"
#include <iostream>
using namespace std;

// 抽象基类

int main(int argc, char const *argv[]) {
  // 纯虚函数
  // 见11_Disc_quote.h
  // 可以为纯虚函数提供定义，但必须定义在类的外部

  // 含有(或未经覆盖直接继承)纯虚函数的类是抽象基类
  // 不能创建抽象基类的对象
  // Disc_quote discounted; // 错误
  Bulk_quote bulk; // 正确

  // 派生类构造函数只初始化它的直接基类
  // 见11_Bulk_quote2.h
  return 0;
}
