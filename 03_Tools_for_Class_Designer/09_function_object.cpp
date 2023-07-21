#include "09_PrintString.h"
#include "09_ShorterString.h"
#include "09_SizeComp.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

// 函数对象：重载函数调用运算符
// 函数调用运算符必须是成员函数

struct absInt {
  int operator()(int val) const { return val < 0 ? -val : val; }
};

// 普通函数
int add(int i, int j) { return i + j; }

// 函数对象类
struct divide {
  int operator()(int denominator, int divisor) { return denominator / divisor; }
};

// 普通函数有重载的情况
int mul(int i, int j) { return i * j; }
double mul(double i, double j) { return i * j; }

int main(int argc, char const *argv[]) {
  // 像使用函数一样使用类的对象
  int i = -42;
  absInt absObj;      // 含有函数调用运算符的对象
  int ui = absObj(i); // 将i传递给absObj.operator()

  // 函数对象类通常含有一些数据成员，用于定制调用运算符中的操作
  string s = "Hello World";
  PrintString printer; // 使用默认值，打印到cout
  printer(s);          // 在cout中打印s，后面跟一个空格
  PrintString errors(cerr, '\n');
  errors(s); // 在cerr中打印s，后面跟一个换行符

  // 函数对象常常作为泛型算法的实参
  vector<string> vs{"Hello", "World"};
  for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));

  // lambda表达式是函数对象
  // 根据单词长度进行排序
  vector<string> words{"hello", "world", "hi", "one", "four"};
  stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {
    return a.size() < b.size();
  });
  // 第三个参数的lambda表达式的行为
  // 类似于09_ShorterString.h中定义的类的一个未命名对象
  stable_sort(words.begin(), words.end(), ShorterString());

  // 表示lambda表达式及相应捕获行为的类
  size_t sz = 4;
  auto wc = find_if(words.begin(), words.end(),
                    [sz](const string &s) { return s.size() >= sz; });
  // 该lambda表达式产生的类形如09_SizeComp.h中定义的类
  auto wc2 = find_if(words.begin(), words.end(), SizeComp(sz));

  // 标准库定义了一些函数对象，定义在头文件functional中
  plus<int> intAdd; // 可执行int加法的函数对象
  negate<int> intNegate;
  int sum = intAdd(10, 20);
  sum = intNegate(intAdd(10, 20));
  sum = intAdd(10, intNegate(10));

  // 在算法中使用标准库函数对象
  sort(words.begin(), words.end(), greater<string>());
  vector<string *> nameTable; // 指针的vector
  // 错误：nameTable中的指针彼此之间没有关系，所以<将产生未定义的行为
  sort(nameTable.begin(), nameTable.end(),
       [](string *a, string *b) { return a < b; });
  // 正确：标准库规定的指针的less是定义良好的
  sort(nameTable.begin(), nameTable.end(), less<string *>());

  // 可调用对象与function
  // 不同类型可能具有相同的调用形式(调用签名一致)
  // 普通函数，见上方add()定义
  add(4, 2);
  // lambda，其产生一个未命名的函数对象类
  auto mod = [](int i, int j) { return i % j; };
  mod(4, 2);
  // 函数对象类，见上方divide定义
  divide div;
  div(4, 2);

  // 标准库function的操作
  function<int(int, int)> f1 = add;      // 函数指针
  function<int(int, int)> f2 = divide(); // 函数对象类的对象
  function<int(int, int)> f3 = [](int i, int j) { return i * j; };
  cout << f1(4, 2) << endl;
  cout << f2(4, 2) << endl;
  cout << f3(4, 2) << endl;

  map<string, function<int(int, int)>> binops = {
      {"+", add},                                // 函数指针
      {"-", std::minus<int>()},                  // 标准库函数对象
      {"/", divide()},                           // 用户定义的函数对象
      {"*", [](int i, int j) { return i * j; }}, // 未命名的lambda
      {"%", mod}};                               // 命名的lambda

  binops["+"](4, 2);
  binops["-"](4, 2);
  binops["/"](4, 2);
  binops["*"](4, 2);
  binops["%"](4, 2);

  // 不能直接将重载函数的名字存入function类型的对象中
  map<string, function<int(int, int)>> binops2;
  // binops2.insert({"*", mul}); // 错误：无法判断哪个重载
  // 解决二义性问题的一个途径是存储函数指针
  int (*fp)(int, int) = mul;
  binops2.insert({"*", fp});
  // 也可以用lambda来消除二义性
  binops2.insert({"*", [](int i, int j) { return mul(i, j); }});
  return 0;
}

/*
                     标准库函数对象
    —————————————————————————————————————————————————
         算术             关系              逻辑
    plus<T>       | equal_to<T>      | logical_and<T>
    minus<T>      | not_equal_to<T>  | logical_or<T>
    multiplies<T> | greater<T>       | logical_not<T>
    divides<T>    | greater_equal<T> |
    modules<T>    | less<T>          |
    negate<T>     | less_equal<T>    |
    —————————————————————————————————————————————————
*/

/*
                               标准库function的操作
    ————————————————————————————————————————————————————————————————————————
    function<T> f;          | f是一个用来存储可调用对象的空function
                            | 这些可调用对象的调用形式应与函数类型T相同
                            | 即T是retType(args)
    function<T> f(nullptr); | 显式地构造一个空function
    function<T> f(obj);     | 在f中存储可调用对象obj的副本
    f                       | 将f作为条件，当f含有一个可调用对象时为真，否则为假
    f(args)                 | 调用f中的对象，参数是args
    ————————————————————————————————————————————————————————————————————————
    定义为function<T>的成员的类型
    result_type          | 该function类型的可调用对象返回的类型
    argument_type        | 当T有一个或两个实参时定义的类型
    first_argument_type  | 如果T只有一个实参，则argument_type是该类型的同义词
    second_argument_type | 如果T有两个实参，则first和second分别代表两个实参类型
    ————————————————————————————————————————————————————————————————————————
*/