#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace std::placeholders;

// bind定义在头文件functional中
// 调用bind的一般形式为：auto newCallable = bind(callalbe, arg_list);
// 实参绑定时会用到占位符，定义在std::placeholders命名空间下

vector<string> words = {"string1", "abcde"};
bool check_size(const string &s, string::size_type sz) {
  return s.size() >= sz;
}

void f(int a, int b, int c, int d, int e) {
  cout << a << b << c << d << e << endl;
}

bool isShoter(const string &s1, const string &s2);
void print(ostream &os, const string &s, char c);

int main(int argc, char const *argv[]) {
  // check6是一个可调用对象，接受一个string类型的参数
  // 用该string和字面值6来调用check_size
  // _1参数是调用check6时获得的
  auto check6 = bind(check_size, _1, 6);

  string s = "hello";
  // 调用check6(s)会调用check_size(s, 6);
  bool b1 = check6(s);
  // find_if算法会调用第三个参数传入的可调用对象，会传入一个参数即容器中的一个元素
  auto wc = find_if(words.begin(), words.end(), bind(check_size, _1, 6));
  // 下句代码与上句等价
  auto wc2 = find_if(words.begin(), words.end(), check6);

  // bind的参数
  int a = 42, b = 43, c = 44;
  // 调用g(X, Y)会映射到f(a, b, Y, c, X)
  auto g = bind(f, a, b, _2, c, _1);

  // 用bind重排参数顺序
  // 单词由短至长
  sort(words.begin(), words.end(), isShoter);
  for_each(words.begin(), words.end(),
           [](const string &s) { cout << s << " "; });
  cout << endl;
  // 单词由长至短
  sort(words.begin(), words.end(), bind(isShoter, _2, _1));
  for_each(words.begin(), words.end(),
           [](const string &s) { cout << s << " "; });
  cout << endl;

  // 绑定引用参数：默认情况下，bind的非占位符参数会被拷贝
  // 错误：os不可以被拷贝
  // for_each(words.begin(), words.end(), bind(print, cout, _1, ' '));
  for_each(words.begin(), words.end(), bind(print, ref(cout), _1, ' '));

  return 0;
}

bool isShoter(const string &s1, const string &s2) {
  return s1.size() < s2.size();
}

void print(ostream &os, const string &s, char c) {
  os << "print:" << endl;
  os << s << c;
}