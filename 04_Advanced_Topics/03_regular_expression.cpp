#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

// 正则表达式
// 描述字符序列的方法

bool valid(const smatch &);

int main(int argc, char const *argv[]) {
  // 查找不再字符c之后的字符串ei
  string pattern("[^c]ei");
  // 需要包含pattern的整个单词，即左右都允许有其他字母
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
  // regex是一个正则表达式的类
  regex r(pattern); // 构造一个用于查找模式的regex
  // smatch是一个容器类，保存在string中搜索的结果
  smatch results; // 定义也给对象保存搜索结果

  string test_str = "receipt freind theif receice";
  // 用r在test_str中查找与pattern匹配的子串
  // regex_search将寻找第一个与正则表达式匹配的子序列
  if (regex_search(test_str, results, r))
    cout << results.str() << endl;

  // 指定regex对象的选项：指定一些标志类影响regex如何操作
  regex r2("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase); // icase表示忽略大小写
  smatch results2;
  vector<string> files{"hello.cpp", "world.cxx", "foo.h", "hi.cc"};
  for (string filename : files)
    if (regex_search(filename, results2, r2))
      cout << results2.str() << endl;

  // 正则表达式的语法是否正确是在运行时解析的
  try {
    regex r3("[[:alnum:]+\\.(cpp|cxx|cc)", regex::icase);
  } catch (regex_error e) {
    cout << e.what() << "\ncode: " << e.code() << endl;
  }

  // 正则表达式类的输入序列类型
  regex r4("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
  // smatch results4; // 将匹配string输入序列，而不是char*
  cmatch results4; // 将匹配字符数组输入序列
  if (regex_search("myfile.cc", results4, r4)) // 输入为C风格字符串
    cout << results4.str() << endl;

  // 使用sregex_iterator来获得所有匹配
  string file("Hello cei world freind meizhu hoho");
  for (sregex_iterator it(file.begin(), file.end(), r), end_it; it != end_it;
       ++it)
    cout << it->str() << endl;

  // 显式匹配单词出现的上下文
  for (sregex_iterator it(file.begin(), file.end(), r), end_it; it != end_it;
       ++it) {
    auto pos = it->prefix().length();           // 获取前缀的大小
    pos = pos > 40 ? pos - 40 : 0;              // 最多取40个字符
    cout << it->prefix().str().substr(pos)      // 前缀的最后一部分
         << "\n\t>>> " << it->str() << " <<<\n" // 匹配的字符串
         << it->suffix().str().substr(0, 40)    // 后缀的第一部分
         << endl;
  }

  // 使用子匹配操作
  // 两个子表达式：点之前表示文件名部分，点之后表示文件扩展名
  regex r5("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
  smatch results5;
  string filename("aa.cpp");
  if (regex_search(filename, results5, r5))
    cout << results5.str(1) << endl; // 打印第一个子表达式

  // 子表达式用于数据验证
  // 正则表达式中的模式通常包含一个或多个子表达式
  string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
  // - (\\()?   表示区号部分可选的左括号
  // - (\\d{3}) 表示区号
  // - (\\))?   表示区号部分可选的右括号
  // - ([-. ])? 表示区号部分可选的分隔符
  // - (\\d{3}) 表示号码的下三位数字
  // - ([-. ])? 表示可选的分隔符
  // - (\\d{4}) 表示号码的最后四位数
  regex r6(phone);
  smatch results6;
  string number("(800) 555-1212");
  if (regex_search(number, results6, r6))
    if (valid(results6)) {
      cout << results6[2].str() // 打印区号
           << results6[4].str() // 打印区号后可选择的分隔符
           << results6[5].str() // 打印号码的中间三位
           << results6[6].str() // 打印号码的可选分隔符
           << results6[7].str() // 打印号码的最后四位
           << endl;
    } else {
      cout << "invalid phone number" << endl;
    }

  // 使用regex_replace将找到的序列替换为另一个序列
  string fmt = "$2.$5.$7";    // 将号码格式改为ddd.ddd.dddd
  string fmt2 = "$2. $5. $7"; // 将号码格式改为ddd. ddd. dddd
  cout << regex_replace(number, r6, fmt) << endl;
  cout << regex_replace(number, r6, fmt2) << endl;

  number = "(08) 555-1800";
  // 不匹配则不会输出
  cout << regex_replace(number, r6, fmt) << endl;
  // 加上format_no_copy，不匹配则原样输出
  cout << regex_replace(number, r6, fmt2, regex_constants::format_no_copy)
       << endl;
  return 0;
}

bool valid(const smatch &m) {
  // 若区号前有左括号
  if (m[1].matched)
    // 则区号后必须有右括号
    return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
  else
    // 否则区号后不能有括号
    // 另外两个组成部分之间的分隔符必须比配
    return !m[3].matched && m[4].str() == m[6].str();
}