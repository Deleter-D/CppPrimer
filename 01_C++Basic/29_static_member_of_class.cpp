using namespace std;
#include "29_Account.h"
#include <iostream>

int main() {
  double r;
  r = Account::rate(); // 使用作用域运算符访问静态成员
  // 虽然不属于某个对象，但可以通过对象访问
  Account ac1;
  Account *ac2 = &ac1;
  // 调用静态成员函数rate的等价形式
  r = ac1.rate();
  r = ac2->rate();
}