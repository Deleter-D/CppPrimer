using namespace std;
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// 无返回值函数
void swap(int &v1, int &v2) {
  if (v1 == v2)
    return;
  int temp = v2;
  v2 = v1;
  v1 = temp;
  // 此处无需显式的return语句
}

// 有返回值函数
bool str_subrange(const string &str1, const string &str2) {
  if (str1.size() == str2.size())
    return str1 == str2;
  auto size = (str1.size() < str2.size()) ? str1.size()
                                          : str2.size(); // 取较短的string长度
  for (decltype(size) i = 0; i != size; ++i)
    if (str1[i] != str2[i])
      return false;
  return true;
}

// 值是如何被返回的
string make_plural(size_t ctr, const string &word, const string &ending) {
  // 数量大于1则返回复数形式，否则返回原型
  return (ctr > 1) ? word + ending : word;
  // 返回类型是string对象
  // 此处返回word对象的副本，或一个未命名的临时string对象
}

const string &shorterString(const string &s1, const string &s2) {
  return s1.size() <= s2.size() ? s1 : s2;
  // 返回类型是const string的引用
  // 不管是调用函数还是返回结果，都不会真正拷贝string对象
}

// 不要返回局部对象的引用或指针
const string &manip() {
  string ret;
  if (!ret.empty()) {
    // TODO
    return ret; // 错误：返回局部对象的引用
  } else {
    // TODO
    return "Empty"; // 错误：“Empty”是一个局部临时变量
  }
}

// 返回类类型的函数和调用运算符
string s1, s2;
// 函数调用和点操作符优先级一样，服从左结合律
auto sz = shorterString(s1, s2).size();

// 引用返回左值
char &get_val(string &str, string::size_type ix) { return str[ix]; }
// 测试get_val
// int main()
// {
//     string s("a value");
//     cout << s << endl;
//     get_val(s, 0) = 'A'; // 若返回类型是常量引用，则不可以给调用的结果赋值
//     cout << s << endl;
//     return 0;
// }

// 列表初始化返回值，C++11以后允许
vector<string> process() {
  string expected = "expected";
  string actual = "actual";
  if (expected.empty())
    return {};
  else if (expected == actual)
    return {"functionX", "okey"};
  else
    return {"functionX", expected, actual};
  // 注意：如果列表中是内置类型，则只能返回一种类型的值，且返回的值不能发生窄化转换
}

// 主函数main的返回值
// 在必要时候编译器会为main加上return 0;
int main() {
  bool some_failure = true;
  if (some_failure)
    return EXIT_FAILURE; // 定义在cstdlib头文件中
  else
    return EXIT_SUCCESS; // 定义在cstdlib头文件中
}

// 递归
// main函数不能调用自己
int factorial(int val) // 计算阶乘
{
  if (val > 1)
    return factorial(val - 1) * val;

  return 1;
}

// 返回数组指针
// 数组不能拷贝，所以函数不能直接返回数组
// 方式1
using arrT = int[10]; // 等价于typedef int arrT[10];
arrT *func(int i); // func返回一个指向含有10个整数的数组的指针
// 方式2
/* func2(int i)            表示调用func2函数需要一个int型的实参
   (*func2(int i)) 表示可以对函数调用的结果执行解引用操作，即返回的是指针
   (*func2(int i))[10]     表示解引用func的调用将得到一个大小为10的数组
   int (*func2(int i))[10] 表示数组中的元素是int类型 */
int (*func2(int i))[10];
// 方式3
// C++11开始支持使用尾置返回类型
// ->符号开始，在本应出现类型的地方使用auto
auto func3(int i) -> int (*)[10];
// 方式4
// 当我们知道函数返回的数组将指向哪个数组时，可以使用decltype
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
decltype(odd) *
arrPtr(int i) // decltype并不负责将数组类型转换成对应的指针，故需要加一个*
{
  return (i % 2) ? &odd : &even;
}
