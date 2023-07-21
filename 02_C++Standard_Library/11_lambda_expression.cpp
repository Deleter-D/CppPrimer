#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void elimDups(vector<string> &words);
void biggies(vector<string> &words, vector<string>::size_type sz);
void func1();
void func2();
void biggies2(vector<string> &words, vector<string>::size_type sz,
              ostream &os = cout, char = 'c');
void func3();
void func4();

int main(int argc, char const *argv[]) {
  // lambda表达式是一个可调用的代码单元，一个未命名的内联函数
  // [capture list] (parameter list) -> return type { function body }

  // 省略了参数列表和返回类型的lambda表达式
  // f为可调用对象，使用()运算符调用
  auto f = [] { return 42; };
  f();

  vector<string> words = {"the",  "quick", "red",  "fox", "jumps",
                          "over", "the",   "slow", "red", "turtle"};
  biggies(words, 4);

  // lambda捕获和返回
  // 向函数传递lambda时，同时定义了一个(未命名的)新类型和该类型的一个对象
  // 默认情况下，新类型包含了捕获的变量，作为数据成员
  func1();
  func2();

  // 可变lambda
  func3();
  func4();

  // 返回类型问题
  vector<int> vi({-1, -2, 3, 1, 4});
  // 错误，编译器无法推断返回类型，默认会给void
  // transform(vi.begin(), vi.end(), vi.begin(), [](int i) {
  //     if (i < 0)
  //         return -i;
  //     else
  //         return i;
  // });
  // 显式指定返回类型
  transform(vi.begin(), vi.end(), vi.begin(), [](int i) -> int {
    if (i < 0)
      return -i;
    else
      return i;
  });
  for_each(vi.begin(), vi.end(), [](int i) { cout << i << " "; });
  cout << endl;

  return 0;
}

void elimDups(vector<string> &words) {
  // 按照字典顺序排序容器
  sort(words.begin(), words.end());
  // 消除相邻重复项，并将不重复的项排列在容器前部
  // 返回指向不重复区域之后一个位置的迭代器
  auto end_unique = unique(words.begin(), words.end());
  // 将不重复区域之后的元素都清除
  words.erase(end_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
  elimDups(words);
  stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {
    return a.size() < b.size();
  });
  // 获取一个迭代器，指向第一个满足size() >= sz的元素
  auto wc = find_if(words.begin(), words.end(),
                    [sz](const string &a) { return a.size() >= sz; });
  // 计算满足size >= sz的元素个数
  auto count = words.end() - wc;
  cout << "长度大于等于" << sz << "的元素有" << count << "个" << endl;
  for_each(wc, words.end(), [](const string &s) { cout << s << " "; });
  cout << endl;
}

// 值捕获
void func1() {
  size_t v1 = 42;
  // 当该lambda表达式创建时，f保存了v1的一个拷贝
  auto f = [v1] { return v1; };
  // 此处改变v1的值与lambda表达式中的v1无关
  v1 = 0;
  // 返回42
  auto j = f();
  cout << j << endl;
}

// 引用捕获
// 以引用方式捕获变量时，必须保证在lambda表达式执行时变量存在
void func2() {
  size_t v1 = 42;
  // 对象f包含了v1的一个引用
  auto f = [&v1] { return v1; };
  v1 = 0;
  // 返回0，f只引用了v1，并不存储它
  auto j = f();
  cout << j << endl;
}

void biggies2(vector<string> &words, vector<string>::size_type sz, ostream &os,
              char c) {
  elimDups(words);
  stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {
    return a.size() < b.size();
  });
  // 获取一个迭代器，指向第一个满足size() >= sz的元素
  auto wc = find_if(words.begin(), words.end(),
                    [sz](const string &a) { return a.size() >= sz; });
  // 计算满足size >= sz的元素个数
  auto count = words.end() - wc;
  os << "长度大于等于" << sz << "的元素有" << count << "个" << endl;

  // os隐式引用捕获，c显式值捕获
  for_each(wc, words.end(), [&, c](const string &s) { os << s << c; });
  os << endl;
  // os显示引用捕获，c隐式值捕获
  for_each(wc, words.end(), [=, &os](const string &s) { os << s << c; });
  os << endl;
}

void func3() {
  size_t v1 = 42;
  // 对于值拷贝的变量，如需要修改，必须加上关键字mutable
  // 加上mutable后参数列表必须写出来，即使是空参数
  auto f = [v1]() mutable { return ++v1; };
  v1 = 0;
  // 返回43
  auto j = f();
  cout << j << endl;
}

void func4() {
  size_t v1 = 42;
  // 对于非const变量的引用，可以通过f中的引用直接修改
  auto f = [&v1] { return ++v1; };
  v1 = 0;
  // 返回1
  auto j = f();
  cout << j << endl;
}