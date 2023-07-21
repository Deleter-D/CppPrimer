#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

// 标准库提供了超过100个算法
// 只读算法：读取其输入范围内的元素，而从不改变元素

int main(int argc, char const *argv[]) {
  // 求和算法
  vector<int> vec({1, 2, 3, 4, 5});
  // 对vec中的元素求和，和的初始值为0
  // 第三个参数还决定了返回类型，以及+操作符的使用
  int sum = accumulate(vec.cbegin(), vec.cend(), 0);
  cout << "vec sum: " << sum << endl;

  vector<string> vec2({"hello", "world", "!!!"});
  string sum2 = accumulate(vec2.cbegin(), vec2.cend(), string(""));
  cout << "vec2 sum: " << sum2 << endl;
  // 错误：const char*没有定义运算符+
  // string sum3 = accumulate(vec2.cbegin(), vec2.cend(), "");

  // 判等算法
  vector<string> roster1({"hello", "world", "!!!"});
  list<const char *> roster2({"hello", "world", "!!!"});
  // 接收单一迭代器表示第二个序列的算法，都假设第二个序列至少和第一个序列一样长
  // equal不要求两个序列容器相同，也不要求类型完全相同，只要能够访问即可
  auto flag = equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
  cout << "roster1 and roster2 " << (flag ? "is" : "is not") << " equal."
       << endl;

  return 0;
}