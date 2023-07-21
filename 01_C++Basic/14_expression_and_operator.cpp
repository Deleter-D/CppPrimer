using namespace std;
#include "06_Sales_data.h"
#include <iostream>
#include <string>
#include <vector>

// C++表达式要么是左值，要么是右值
// C语言中：左值可以位于赋值语句的左侧，右值不能
// C++中：左值是能取到地址的表达式，右值是不能取到地址的表达式

/*
    常量对象为代表的左值不能作为赋值语句的左侧运算对象
    某些表达式的求值结果是对象，但它们是右值
*/

/*
    当一个对象被当作右值的时候，用的是对象的值，即内存中的内容
    当一个对象被当作左值的时候，用的是对象的身份，即内存中的位置
*/

/*
    通常情况：
    左值可以当作右值，实际使用的是它的内容
    不能把右值当作左值
*/

// decltype与表达式
int num;
int *p = &num;
decltype(*p) i = num; // 解引用运算符生成左值，所以decltype(*p)的结果是int&
decltype(&p) j = &p; // 取地址运算符生成右值，所以decltype(&p)的结果是int**

// 取余和取模运算
// 此处不考虑因取负而导致溢出的情况
// m % (-n) == m % n;
// (-m) % n == -(m % n);
// (m / n) * n + m % n == m;

// 模拟测试函数
int get_value(int i) { return i + 1; }

int main() {
  // 逻辑和关系运算符
  string text[4] = {"Hello", " ", "", "the world."};
  for (const auto &s : text) {
    cout << s;
    // 遇到空字符或以句号结束的字符串就进行换行
    if (s.empty() || s[s.size() - 1] == '.')
      cout << endl;
    else
      cout << " ";
  }

  // 赋值运算符
  // 注意：初始化并非赋值运算
  int i = 0, j = 0, k = 0; // 初始化
  const int ci = i;        // 初始化

  k = 0;

  // C++11允许使用列表作为赋值语句右侧的运算对象
  // k = {3.14}; //
  // 使用列表初始化时，对值的要求更高，这种会发生窄化转换，是不被允许的
  k = 3.14; // 不使用列表时，窄化是被允许的，k的值为3

  vector<int> vi;                      // 初始化为空
  vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 赋值

  // 赋值运算满足右结合律
  int ival, jval;
  ival = jval = 0; // 0先赋值给jval，jval再赋值给ival

  int *pval;
  // ival = pval = 0;//
  // 0先赋值给指针pval是允许的，但指针pval再赋值给ival是不允许的，二者类型不同

  string s1, s2;
  s1 = s2 = "OK";

  // 赋值运算的优先级较低
  int i2 = 0;
  while (i2 != 42) {
    // TODO
    i2 = get_value(i2);
  }
  // 利用优先级优化写法
  int j2 = 0;
  while ((j2 = get_value(j2)) != 42) {
    // TODO
  }

  // 符合赋值运算
  int i3 = 0;
  i3 = i3 + 1;
  i3 += 1; // 这种方式可以少取一次i3的值

  // 递增和递减运算符
  int i4 = 0, j4;
  // 尽量使用前置递增/递减，因为后置递增/递减需要单独存储一个递增/递减前的值
  j4 = ++i4; // 此时i4为1，j4为1，先递增，再赋值
  j4 = i4++; // 此时i4为2，j4为1，先赋值，再递增

  // 成员访问运算符
  // 点运算符和箭头运算符都可以访问成员
  // ptr->mem等价于(*ptr).mem
  string str1 = "a string", *p = &str1;
  auto n = str1.size();
  n = (*p).size();
  n = p->size();

  // 条件运算符
  int grade = 0;
  string finalgrade = (grade < 60) ? "fail" : "pass";
  // 允许嵌套，满足右结合律
  finalgrade = (grade > 90) ? "high pass" : (grade < 60) ? "fail" : "pass";
  cout << ((grade < 60) ? "fail" : "pass") << endl;

  // 位运算符，满足左结合律
  // 取反   ~expr
  // 左移   expr1 << expr2
  // 右移   expr1 >> expr2
  // 位与   expr1 & expr2
  // 位异或 expr1 ^ expr2
  // 位或   expr1 | expr2
  // 关于符号位如何处理没有明确规定，所以强烈建议仅将位运算符用于处理无符号类型
  unsigned char bits = 0233; // 10011011
  cout << (bits << 8) << endl;

  bits = 0227; // 10010111
  cout << (~bits) << endl;

  unsigned char b1 = 0145; // 01100101
  unsigned char b2 = 0257; // 10101111
  cout << (b1 & b2) << endl;
  cout << (b1 | b2) << endl;
  cout << (b1 ^ b2) << endl;

  // 用一个二进制位表示某个学生是否通过测试
  unsigned long quizl = 0;
  quizl |= 1UL << 27;                // 将第27位置1
  quizl &= ~(1UL << 27);             // 将第27位置0
  bool status = quizl & (1UL << 27); // 判断27位是1还是0
  cout << status << endl;

  // sizeof运算符，返回所占字节数
  Sales_data data, *data_ptr;
  cout << "---------" << endl;
  cout << sizeof(Sales_data) << endl; // 存储Sales_data类型的对象所占的空间大小
  cout << sizeof data << endl; // data的类型大小，即sizeof(Sales_data)
  cout << sizeof data_ptr << endl; // 指针所占空间大小

  // sizeof和*优先级一样，满足右结合律
  // data_ptr可以是无效指针，并不会解引用执行
  sizeof *data_ptr; // 等价于sizeof(*data_ptr)，是指针所指类型的大小，即sizeof(Sales_data)

  cout << sizeof data.revenue << endl;
  cout << sizeof Sales_data::revenue << endl;

  // sizeof运算能够得到整个数组的大小
  int int_array[5];
  constexpr size_t sz = sizeof(int_array) / sizeof(*int_array);
  int int_array2[sz]; // sizeof返回一个常量表达式，可以用来初始化数组
  cout << sz << endl;

  // 逗号运算符
  // 含有两个运算对象，按照从左向右的顺序依次求值
  // 返回结果位右侧表达式的值
  vector<int> ivec = {1, 2, 3, 4};
  vector<int>::size_type cnt = ivec.size();
  for (vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt)
    ivec[ix] = cnt;
}
