#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  const char *cp = "Hello World!!!";
  char noNull[] = {'H', 'i'};
  string s1(cp); // 拷贝cp中的字符直到遇到空字符
  cout << "s1: " << s1 << endl;
  string s2(noNull, 2); // 从noNull拷贝两个字符
  cout << "s2: " << s2 << endl;
  string s3(noNull); // 未定义：noNull不是以空字符结束
  cout << "s3: " << s3 << endl;
  string s4(cp + 6, 5); // 从cp[6]开始拷贝5个字符
  cout << "s4: " << s4 << endl;
  string s5(s1, 6, 5); // 从s1[6]开始拷贝5个字符
  cout << "s5: " << s5 << endl;
  string s6(s1, 6); // 从s1[6]开始，直到s1末尾
  cout << "s6: " << s6 << endl;
  string s7(s1, 6, 20); // 只拷贝到s1末尾
  cout << "s7: " << s7 << endl;
  // string s8(s1, 16); // 抛出out_of_range异常
  // cout << "s8: " << s8 << endl;

  string s("hello world");
  string sub1 = s.substr(0, 5);
  cout << "sub1: " << sub1 << endl;
  string sub2 = s.substr(6);
  cout << "sub2: " << sub2 << endl;
  string sub3 = s.substr(6, 11);
  cout << "sub3: " << sub3 << endl;
  // string sub4 = s.substr(12); // 抛出out_of_range异常
  // cout << "sub4: " << sub4 << endl;

  // 除了迭代器版本的insert和erase外，string还提供了下表版本
  s.insert(s.size(), 5, '!'); // 在末尾插入5个感叹号
  cout << "s insert: " << s << endl;
  s.erase(s.size() - 5, 5); // 删除末尾5个字符
  cout << "s erase: " << s << endl;
  // 还提供了接受C风格字符串的版本
  const char *cp2 = "Stately, plump Buck";
  s.assign(cp2, 7); // 将s指定为cp的前7个字符
  cout << "s char* assign: " << s << endl;
  s.insert(s.size(), cp2 + 7); // 将cp+7开始的字符插入s末尾
  cout << "s char* insert: " << s << endl;

  string ss = "some thing", ss2 = "some other thing";
  s.insert(0, ss2);                // 在s中位置0之前插入ss2的拷贝
  s.insert(0, ss2, 0, ss2.size()); // 在s[0]之前插入s2[0]开始的s2.size()个字符
  cout << "s string insert: " << s << endl;

  // append和replace函数
  string str("C++ Primer"), str2 = str;
  // 下面两句等价
  str.insert(str.size(), " 4th Ed.");
  str2.append(" 4th Ed.");
  cout << "str: " << str << " str2: " << str2 << endl;
  // 下面两句与第三句等价
  str.erase(11, 3);
  str.insert(11, "5th");
  str2.replace(11, 3, "5th");
  cout << "str: " << str << " str2: " << str2 << endl;

  // 搜索操作
  string name("AnnaBelle");
  auto pos1 = name.find("Anna");

  string numbers("0123456789"), name2("r2d2");
  auto pos2 = name2.find_first_of(numbers);
  cout << "first number in " << name2 << " is at " << pos2 << endl;

  string dept("03714p3");
  auto pos3 = dept.find_first_not_of(numbers);
  cout << "first not number in " << dept << " is at " << pos3 << endl;

  string::size_type pos = 0;
  while ((pos = name2.find_first_of(numbers, pos)) != string::npos) {
    cout << "found number at index " << pos << " element is " << name2[pos]
         << endl;
    ++pos;
  }

  string river("Mississippi");
  auto first_pos = river.find("is");
  auto last_pos = river.rfind("is");

  // string与数值的转换
  int i = 42;
  string one = to_string(i);
  double d = stod(one);

  string pi = "pi = 3.14!!!";
  d = stod(pi.substr(
      pi.find_first_of("+-.0123456789"))); // 等价于d = stod("3.14!!!")

  return 0;
}

/*
                              额外的构造函数
    ———————————————————————————————————————————————————————————————————
    string s(cp, n)          | s是cp指向的数组中前n个字符的拷贝，
                             | 该数组至少应该包含n个字符
    string s(s2,pos2)        | s是string s2从下标pos2开始的字符的拷贝
                             | 若pos2>s2.size()，构造函数行为未定义
    string s(s2, pos2, len2) | s是string s2从下标pos2开始len2个字符的拷贝
                             | 若pos2>s2.size()，构造函数的行为未定义
                             | 无论len2的值是多少，构造函数至多
                             | 拷贝s2.size()-pos2个字符
    ———————————————————————————————————————————————————————————————————
*/

/*
                            子字符串操作
    ———————————————————————————————————————————————————————————————
    s.substr(pos, n) | 返回一个string，包含s中从pos开始的n个字符的拷贝
                     | pos的默认值为0，n的默认值为s.size()-pos
    ———————————————————————————————————————————————————————————————
*/

/*
                              字符串搜索操作
    ————————————————————————————————————————————————————————————————————————
    s.find(args)              | 查找s中args第一次出现的位置
    s.rfind(args)             | 查找s中args最后一次出现的位置
    s.find_first_of(args)     | 在s中查找args中任意一个字符第一次出现的位置
    s.find_last_of(args)      | 在s中查找args中任意一个字符最后一次出现的位置
    s.find_first_not_of(args) | 在s中查找第一个不在args中的字符
    s.find_last_not_of(args)  | 在s中查找最后一个不在args中的字符
    ————————————————————————————————————————————————————————————————————————
    每个函数都有4个重载版本，args必须是以下形式之一
    ————————————————————————————————————————————————————————————————————————
    s2, pos    | 从s中位置pos开始查找字符串s2，pos默认为0
    cp, pos    | 从s中位置pos开始查找指针cp指向的以空字符结尾的
               | C风格字符串，pos默认为0
    cp, pos, n | 从s中位置pos开始查找指针cp指向的数组的前n个字符，pos和n无默认值
    ————————————————————————————————————————————————————————————————————————
*/

/*
                           s.compare的参数形式
    ————————————————————————————————————————————————————————————————
    s2                     | 比较s和s2
    pos1, n1, s2           | 将s中从pos1开始的n1个字符与s2进行比较
    pos1, n1, s2, pos2, n2 | 将s中从pos1开始的n1个字符与s2中从pos2开始
                           | 的n2个字符进行比较
    cp                     | 比较s与cp指向的以空字符结尾的字符数组
    pos1, n1, cp           | 将s中从posl开始的nl个字符与cp指向的
                           | 以空字符结尾的字符数组进行比较
    pos1, n1, cp, n2       | 将s中从pos1开始的nl个字符与指针cp指向的
                           | 地址开始的n2个字符进行比较
    ————————————————————————————————————————————————————————————————
*/

/*
                          string和数值之间的转换
    —————————————————————————————————————————————————————————————————
    to_string(val)  | 返回val的string表示
    —————————————————————————————————————————————————————————————————
    stoi(s, p, b)   | 返回s的起始子串（表示整数内容）的数值，返回值类型
    stol(s, p, b)   | 分别是int、long、unsigned long、
                    | long long、unsigned long long
    stoul(s, p, b)  | b表示转换所用的基数，默认值为10
    stoll(s, p, b)  | p是size_t指针，用来保存s中第一个非数值字符的下标
    stoull(s, p, b) | p默认为0，即函数不保存下标
    —————————————————————————————————————————————————————————————————
    stof(s, p)      | 返回s的起始子串（表示浮点数内容）的数值，返回值类型
    stod(s, p)      | 分别是float、double或long double
    stold(s, p)     | 参数p的作用与整数转换函数中一样
    —————————————————————————————————————————————————————————————————
*/