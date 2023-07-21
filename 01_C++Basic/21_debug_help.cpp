using namespace std;
#include <iostream>
#include <string>
// 调试帮助
// 只在开发过程中使用的代码，发布时屏蔽
// assert预处理宏，定义在cassert头文件中
// #define NDEBUG // 关闭调试状态，必须在cassert头文件上方
#include <cassert>

void print(const string word, string::size_type size);

int main() {
  int x = 0;
  // 若表达式为真，assert什么也不做
  // 若表达式为假，assert输出信息并终止程序的执行
  // assert(x);

  string word = "Hello world!";
  string::size_type size = 100;
  print(word, size);
}

// 除了使用assert之外，可以使用NDEBUG编写自定义的调试代码
void print(const string word, string::size_type size) {
#ifndef NDEBUG
  if (word.size() < size) {
    cerr
        // __FILE__存放文件名的字符串字面值
        << "Error: "
        << __FILE__
        // __func__存放当前函数名称的字符串字面值
        << " : in function "
        << __func__
        // __LINE__存放当前行号的整型字面值
        << " at line " << __LINE__
        << endl
        // __DATE__存放文件编译日期的字符串字面值
        << "    Compiled on "
        << __DATE__
        // __TIME__存放文件编译时间的字符串字面值
        << " at " << __TIME__ << endl
        << "    Word read was \"" << word << "\": Length too short" << endl;
  }
#endif
}