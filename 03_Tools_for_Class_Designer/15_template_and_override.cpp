#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// 打印任何无法处理的类型
template <typename T> string debug_rep(const T &t, bool called_by_user = true) {
  ostringstream ret;
  if (called_by_user)
    ret << "[Version 01]";
  ret << t; // 使用T的<<运算符打印t的一个表示形式
  return ret.str();
}
// 打印指针的值，后跟指针指向的对象
// 此函数不能用于char*
template <typename T> string debug_rep(T *p) {
  ostringstream ret;
  ret << "[Version 02]";
  ret << "pointer: " << p; // 打印指针本身的值
  if (p)
    ret << " " << debug_rep(*p, false); // 打印指针指向的对象
  else
    ret << " null pointer"; // 或指出p为空
  return ret.str();         // 返回ret绑定的string的一个副本
}
// 非模板版本
string debug_rep(const string &s) {
  cout << "[Version 03]";
  return "" + s + "";
}
// 将字符指针按指针转换为string，并调用string版本的debug_rep
string debug_rep(char *p) { return debug_rep(string(p)); }
string debug_rep(const char *p) { return debug_rep(string(p)); }

int main(int argc, char const *argv[]) {
  // 函数模板可以被另一个模板或一个普通非模板函数重载
  string s("hi");
  // 此时第一个版本推导类型为const string&，第二个版本不接受对象(无法匹配)
  cout << debug_rep(s) << endl; // 只能匹配第一个版本
  // 此时第一个版本推导为const string*&(指针的引用)，第二个版本推到为string*
  cout << debug_rep(&s) << endl; // 第二个版本更精确
  const string *sp = &s;
  // 此时第一个版本推导为const string*&，第二个版本推导为const string*
  // 在模板重载的匹配中，优先匹配更特殊的
  // 第一个版本可以接受对象，也可以是指针，但第二个版本只能接受指针，更为特殊
  cout << debug_rep(sp) << endl; // 都是精确匹配，但第二个版本更特殊

  // 非模板和模板重载
  // 非模板版本优先匹配
  // 此处实现了非模板版本，会对上面的匹配情况有所改变
  cout << debug_rep(s) << endl;

  // 重载模板与类型转换
  cout << debug_rep("hi world!") << endl; // 匹配第二个版本
  // 有三个可行的版本
  // debug_rep(const T&)，T被绑定到char[10]
  // debug_rep(T*)，T被绑定到const char*
  // debug_rep(const string&)，要求从const char*到string的转换
  // 但会有一个问题，按照第二个版本的逻辑，输出指针将输出整个字符串，而不是地址
  // 同时，输出解引用后的char*也只会输出第一个字符

  // 若希望将字符指针按string处理，就需要给出一个更加匹配的版本
  // 此时，上句代码的输出就正常了

  return 0;
}