using namespace std;
#include "26_Screen.h"
#include "26_Window_mgr.h"
#include <iostream>

int main() {
  Screen my_screen;
  char ch = my_screen.get();
  ch = my_screen.get(0, 0);

  my_screen.move(4, 0).set('#');
  // 若move返回Screen而非Screen&，则执行一个拷贝
  Screen temp = my_screen.move(4, 0);
  temp.set('#'); // 不会改变my_screen的内容

  Screen my_screen2(5, 3, ' ');
  const Screen blank(5, 3, ' ');
  my_screen2.set('#').display(cout); // 调用非常量版本，set返回的是非常量引用
  blank.display(cout);               // 调用常量版本
}