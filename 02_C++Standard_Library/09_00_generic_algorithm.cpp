#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>
using namespace std;

// 大多数算法都定义在头文件algorithm中，头文件numeric中也定义了一组算法
// 泛型算法本身不会执行容器的操作，只会运用于迭代器或指针上

int main(int argc, char const *argv[]) {
  int val = 42;
  vector<int> vec({1, 2, 3, 42, 5});
  // 从第一个参数位置开始，至第二个参数(但不包含)之间找val，若存在则返回位置，若不存在则返回第二个参数
  auto result = find(vec.cbegin(), vec.cend(), val);
  cout << "值：" << val << (result == vec.cend() ? "不存在" : "存在") << endl;

  string val2 = "a value";
  list<string> strlist({"hello", "world", "a value", "last"});
  auto result2 = find(strlist.cbegin(), strlist.cend(), val2);
  cout << "字符串：" << val2 << (result2 == strlist.cend() ? "不存在" : "存在")
       << endl;

  // 也可以使用指针查找
  int ia[] = {27, 210, 12, 47, 109, 83};
  int val3 = 83;
  int *result3 = find(begin(ia), end(ia), val3);
  auto result4 = find(ia + 1, ia + 4, val3);
  cout << "值：" << val3 << (result3 == end(ia) ? "不存在" : "存在") << endl;
  cout << "值：" << val3 << (result4 == ia + 4 ? "不存在" : "存在")
       << "于ia[1]到ia[4]之间" << endl;

  return 0;
}
