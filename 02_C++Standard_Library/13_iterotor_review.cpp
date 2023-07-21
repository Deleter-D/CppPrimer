#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  // 插入迭代器
  list<int> lst = {1, 2, 3, 4};
  auto lstInserter = inserter(lst, lst.begin());
  *lstInserter = 42; // 等价于it = c.insert(lst.begin(), 42); ++it;
  for_each(lst.begin(), lst.end(), [](const int &i) { cout << i << " "; });
  cout << endl;

  list<int> lst2, lst3;
  copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
  for_each(lst2.cbegin(), lst2.cend(), [](const int &i) { cout << i << " "; });
  cout << endl;
  copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
  for_each(lst3.cbegin(), lst3.cend(), [](const int &i) { cout << i << " "; });
  cout << endl;

  // 流迭代器
  istream_iterator<int> int_iter(cin);
  istream_iterator<int> eof;
  vector<int> vec;
  while (int_iter != eof)
    vec.push_back(*int_iter++);
  for_each(vec.cbegin(), vec.cend(), [](const int &i) { cout << i << " "; });
  cout << endl;

  // 从文件流中读取
  ifstream fin("./13_file.txt");
  istream_iterator<string> str_it(fin);
  for (int i = 0; i < 3; i++) {
    cout << *str_it++ << " ";
  }
  cout << endl;

  // 使用算法操作迭代器
  istream_iterator<int> int_iter2(cin), eof2;
  cout << accumulate(int_iter2, eof2, 0) << endl;

  // 使用ostream_iterator输出序列
  ostream_iterator<int> out_iter(cout, " ");
  for (auto e : vec)
    *out_iter++ = e; // 赋值语句将元素写入cout中
  cout << endl;
  // 与上面等价，*和++不对out_iter做任何操作
  for (auto e : vec)
    out_iter = e;
  cout << endl;

  copy(vec.begin(), vec.end(), out_iter);
  cout << endl;

  // 反向迭代器
  // 反向迭代器需要递减运算符，故forward_list或流迭代器不能创建反向迭代器
  vector<int> vec2({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (auto r_iter = vec2.crbegin(); r_iter != vec2.crend(); ++r_iter)
    cout << *r_iter << " ";
  cout << endl;

  sort(vec2.begin(), vec2.end());   // 升序
  sort(vec2.rbegin(), vec2.rend()); // 降序

  string line = "FIRST,MIDDLE,LAST";
  // 查找逗号分割的第一个字符串
  auto comma = find(line.cbegin(), line.cend(), ',');
  cout << string(line.cbegin(), comma) << endl;
  // 查找逗号分割的最后一个字符串
  auto rcomma = find(line.crbegin(), line.crend(), ',');
  // 错误：将会逆序输出字符串的每个字符
  cout << string(line.crbegin(), rcomma) << endl;
  // 正确：得到一个正向迭代器，从逗号开始读取字符，直到末尾
  cout << string(rcomma.base(), line.cend()) << endl;
  return 0;
}

/*
    插入迭代器有三种类型：
    - back_inserter，创建一个使用push_back的迭代器
    - front_inserter，创建一个使用push_front的迭代器
    - inserter，创建一个使用insert的迭代器，插入指定迭代器之前的位置
    ——————————————————————————————————————————————————————————
                          插入迭代器操作
    ——————————————————————————————————————————————————————————
    it = t          | 在it指定的当前位置插入t
                    | 假设c是it绑定的容器，依赖于插入迭代器的种类，
                    | 该赋值操作会分别调用c.push_back(t)、
                    | c.push_front(t)或c.insert(p, t)
                    | 其中p为传给inserter迭代器的位置
    *it, ++it, it++ | 这些操作虽然都存在，但不会对it执行任何操作，
                    | 每个操作均返回it
    ——————————————————————————————————————————————————————————
*/

/*
                            istream_iterator操作
    ————————————————————————————————————————————————————————————————————
    istream_iterator<T> in(is); | in从输入流is读取类型为T的值
    istream_iterator<T> end;    | 读取类型为T的值的istream_iterator迭代器，
                                | 表示尾后位置 in1 == in2
                                | in1和in2必须读取相同类型
    in1 != in2 | 如果都是尾后迭代器，或绑定到相同的输入，则二者相等
    *in        | 返回从流中读取的值
    in->mem    | 与(*in).mem含义相同
    ++in, in++ | 使用元素类型所定义的>>运算符从输入流中读取下一个值
               | 前置版本返回一个指向递增后迭代器的引用，后置版本返回旧值
    ————————————————————————————————————————————————————————————————————
*/

/*
                        ostream_iterator操作
    ———————————————————————————————————————————————————————————————
    ostream_iterator<T> out(os);    | out将类型为T的值写到输出流os中
    ostream_iterator<T> out(os, d); | out将类型为T的值写到输出流os中，
                                    | 每个值后面都输出一个d
                                    | d指向一个空字符结尾的字符数组
    out = val          | 用<<运算符将val写入到out所绑定的ostream中
                       | val的类型必须与out可写的类型兼容
    *out, ++out, out++ | 这些操作虽然都存在，但不会对out执行任何操作，
                       | 每个操作均返回out
    ———————————————————————————————————————————————————————————————
*/
