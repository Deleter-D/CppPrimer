using namespace std;
#include "06_Sales_data.h"
#include <iostream>
#include <stdexcept>

// 传统方式处理问题
int test1(Sales_data data1, Sales_data data2) {

  if (data1.bookNo == data2.bookNo) {
    cout << data1.revenue + data2.revenue << endl;
    return 0;
  } else {
    cerr << "Data must refer to same bookNo." << endl;
    return -1;
  }
}

// throw表达式处理异常
int test2(Sales_data data1, Sales_data data2) {
  // throw表达式：异常检测部分使用throw表达式来表示它遇到了无法解决的问题
  if (data1.bookNo != data2.bookNo)
    // 抛出一个异常，终止当前函数，并把控制器交给异常处理代码
    throw runtime_error("Data must refer to same bookNo.");
  // runtime_error是标准库异常类型的一种，定义在stdexcept头文件中
  cout << data1.revenue + data2.revenue << endl;
  return 0;
}

void test3(Sales_data data1, Sales_data data2) {
  while (true) {
    // try语句块：异常处理部分使用try语句块处理，可以有多个catch
    try {
      if (data1.bookNo != data2.bookNo)
        throw runtime_error("Data must refer to same bookNo.");
      cout << data1.revenue + data2.revenue << endl;
    } catch (runtime_error err) {
      cout << err.what() << "\nTry again? Enter y or n" << endl;
      char c;
      cin >> c;
      if (!cin || c == 'n')
        break;
    }
  }
}

int main() {
  Sales_data data1, data2;
  data1.bookNo = "0001";
  data2.bookNo = "0002";
  // test1(data1, data2);
  // test2(data1, data2);
  test3(data1, data2);
}

/*  异常类：throw表达式和相关的catch子句之间传递异常的具体信息，分别定义在4个头文件中
    exception头文件：最通用的异常类exception，只报告异常的发生，不提供额外信息
    stdexcept头文件：定义了几种常用的异常类
    new头文件：bad_alloc异常类，分配内存时的异常
    type_info头文件：bad_cast异常类，类型转换时的异常*/

/*                     stdexcept头文件定义的异常类
    ————————————————————————————————————————————————————————————————
    exception         |  最常见的问题
    runtime_error     |  只有在运行时才能检测出的问题
    range_error       |  运行时错误：生成的结果超出了有意义的值域范围
    overflow_error    |  运行时错误：计算上溢
    underflow_error   |  运行时错误：计算下溢
    logic_error       |  程序逻辑错误
    domain_error      |  逻辑错误：参数对应的结果值不存在
    invalid_argument  |  逻辑错误：无效参数
    length_error      |  逻辑错误：试图创建一个超出该类型最大长度的对象
    out_of_range      |  逻辑错误：使用一个超出有效范围的值
    ————————————————————————————————————————————————————————————————
*/