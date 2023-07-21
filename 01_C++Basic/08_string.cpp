using namespace std;
#include <cctype>
#include <iostream>
#include <string>

int main() {
  string s1;      // 空字符串
  string s2 = s1; // s2是s1的副本，等价于string s2(s1);
  string s3 = "hiya"; // s3是该字符串字面值的副本，等价于string s3("hiya");
  // 值得注意的是"hiya"本身与string并不完全相同，只是允许使用字面值来初始化一个string类型的字符串
  string s4(10, 'c'); // s4的内容是cccccccccc，即10个c

  // 逐个单词输入，以空格分割
  string word;
  while (cin >> word)
    cout << word << endl;

  // 输入一整行，以换行符分割
  string line;
  while (getline(cin, line)) {
    cout << line << endl;
  }

  // 字面值和string对象相加
  string str1 = "hello", str2 = "world";
  string str3 = str1 + "," + s2 + "\n";
  string str4 = str1 + ",";
  // 字面值之间无法相加，只有其中包含string对象才能借助string中的重载进行连接
  // 字面值在C++中并不是string对象
  // string str5 = "hello" + ",";
  string str6 = str1 + "," + "world";
  // str7的这种方式也不可以，优先进行的操作是两个字面值相加
  // string str7 = "hello" + "," + str2;
  string str8 =
      "hello" + ("," + str2); // 这样就将优先的操作变为string对象与字面值相加

  // cctype头文件是C++中兼容了C语言中的ctype.h头文件
  // C++中兼容C语言的标准库头文件name.h时将其头文件命名为cname
  // 在C++中应尽量避免使用.h,因为cname头文件中定义的名字从属于命名空间std
  string str("Hello World!!!");
  decltype(str.size()) punct_cnt = 0; // 存储标点符号个数
  for (auto c : str)
    if (ispunct(c))
      ++punct_cnt;
  cout << punct_cnt << " punctuation characters in " << str << endl;

  // 转换为大写
  string orig = str; // 保存初始状态
  for (auto &c : str) // auto推演结果为char，加上&变为引用以修改内容
    c = toupper(c);
  cout << str << endl;

  // 将第一个空格前的字符转换为大写
  str = orig; // 恢复原样
  decltype(str.size()) index = 0;
  while (index != str.size() && !isspace(str[index])) {
    str[index] = toupper(str[index]);
    ++index;
  }
  cout << str << endl;

  // 利用下标判断十进制数对应的十六进制数
  const string hexdigits = "0123456789ABCDEF"; // 可能的十六进制数
  cout << "Enter a series of numbers between 0 and 15\n"
       << "separated by spaces. Hit Enter when finished:" << endl;
  string result;
  string::size_type n;
  while (cin >> n)
    if (n < hexdigits.size())
      result += hexdigits[n];
  cout << "Your hex number is: " << result << endl;
  return 0;
}

/*
                             string的操作
    ————————————————————————————————————————————————————————————————
    os<<s         | 将s写到输出流os中，返回os
    is>>s         | 从is中读取字符串赋值给s，以空格分割，返回is
    getline(is,s) | 从is中读取一行赋值给s，以换行符分割，返回is
    s.empty()     | s为空返回true，否则返回false
    s.size()      | 返回s中字符的个数，返回值为string::size_type类型
    s[n]          | 返回s中第n个字符的引用，n从0开始
    s1+s2         | 返回s1和s2连接后的结果
    s1=s2         | 用s2的副本替代s1中原来的字符
    s1==s2        | 判断s1和s2是否完全一样
    s1!=s2        | 判断s1和s2是否不完全一样
    <,<=,>,>=     | 利用字符在字典中的顺序进行比较
    —————————————————————————————————————————————————————————————————
*/

/*
                          cctype头文件中的函数
    ———————————————————————————————————————————————————————————————
    isalnum(c)   |   当c是字母或数字时为true
    isalpha(c)   |   当c是字母时为true
    iscntrl(c)   |   当c是控制字符时为true
    isdigit(c)   |   当c是数字时为true
    isgraph(c)   |   当c不是空格但可打印时为true
    islower(c)   |   当c是小写字母时为true
    isupper(c)   |   当c是大写字母时为true
    isprint(c)   |   当c是可打印字符时为true(即c是空格或c具有可视形式)
    ispunct(c)   |   当c是标点符号时为true
                 |   即c不是控制字符、数字、字母、可打印空白中的一种
    isspace(c)   |   当c是空白时为true，即c是空格、横向制表符、
                 |   纵向制表符、回车符、换行符、进纸符中的一种
    isxdigit(c)  |   当c是十六进制数字时为true
    tolower(c)   |   如果c是大写字母，输出对应的小写字母，否则原样输出c
    toupper(c)   |   如果c是小写字母，输出对应的大写字母，否则原样输出c
    ———————————————————————————————————————————————————————————————
*/