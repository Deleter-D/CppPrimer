#include "01_Sales_data.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

// tuple中存放书店的编号和指定书籍的头尾迭代器
typedef tuple<vector<Sales_data>::size_type, vector<Sales_data>::const_iterator,
              vector<Sales_data>::const_iterator>
    matches;
struct compareIsbn {
  bool operator()(const Sales_data &sd, const string &book) {
    return sd.isbn() < book;
  }
  bool operator()(const string &book, const Sales_data &sd) {
    return book < sd.isbn();
  }
  bool operator()(const Sales_data &sd1, const Sales_data &sd2) {
    return sd1.isbn() < sd2.isbn();
  }
};
// findBook返回一个vector，每家销售了给定书籍的书店在其中都有一项
vector<matches> findBook(const vector<vector<Sales_data>> &files,
                         const string &book) {
  vector<matches> ret;
  // 遍历每家书店
  for (auto it = files.cbegin(); it != files.cend(); ++it) {
    // 查找具有相同ISBN的Sales_data范围
    auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn());
    // 此书店销售了指定书籍
    if (found.first != found.second)
      // 记录书店编号与首尾迭代器
      ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
  }
  return ret;
}

void reportResults(istream &in, ostream &os,
                   const vector<vector<Sales_data>> &files) {
  string s;
  while (in >> s) {
    auto trans = findBook(files, s);
    if (trans.empty()) {
      cout << s << " not found in any stores" << endl;
      continue;
    }
    for (const auto &store : trans)
      os << "store" << get<0>(store) << " sales: " << endl
         << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl;
  }
}

int main(int argc, char const *argv[]) {
  // 将一些数据组合成单一对象：快速而随意的数据结构
  tuple<size_t, size_t, size_t> threeD; // 三个成员都设置为0
  // 为每个成员提供初始值
  tuple<string, vector<double>, int, list<int>> someVal(
      "constants", {3.14, 2, 718}, 42, {0, 1, 2, 3, 4, 5});
  // tuple的构造函数是explicit的
  // tuple<size_t, size_t, size_t> threeD2 = {1, 2, 3}; // 错误
  tuple<size_t, size_t, size_t> threeD2{1, 2, 3}; // 正确
  // 表示书店交易记录的tuple
  auto item = make_tuple("0-999-78345-X", 3, 20.00);

  // 访问tuple的成员
  auto book = get<0>(item);  // 获取第一个成员
  auto cnt = get<1>(item);   // 获取第二个成员
  auto price = get<2>(item); // 获取第三个成员
  get<2>(item) *= 0.8;       // 取出的是引用，可以修改值

  typedef decltype(item) trans; // trans是item的类型
  // 返回trans类型对象中成员的数量
  size_t sz = tuple_size<trans>::value;
  // cnt的类型与item中的第二个成员相同
  tuple_element<1, trans>::type cnt2 = get<1>(item);

  // 关系和相等运算符
  tuple<string, string> duo("1", "2");
  tuple<size_t, size_t> towD(1, 2);
  // bool b = (duo == twoD); // 错误：不能比较size_t和string
  tuple<size_t, size_t, size_t> threeD3(1, 2, 3);
  // bool b = (towD < threeD3); // 错误：成员数量不同
  tuple<size_t, size_t> origin(0, 0);
  bool b = (origin < towD); // 正确

  // 使用tuple返回多个值
  // 见上方定义的findBook和reportResults
  vector<vector<Sales_data>> files;
  vector<Sales_data> store1;
  store1.push_back(Sales_data("9-783984-0", 2, 19.99));
  store1.push_back(Sales_data("9-783984-0", 3, 19.99));
  sort(store1.begin(), store1.end(), compareIsbn());
  vector<Sales_data> store2;
  store2.push_back(Sales_data("9-783984-0", 1, 19.99));
  store2.push_back(Sales_data("9-783984-1", 2, 29.99));
  store2.push_back(Sales_data("9-783984-0", 3, 19.99));
  sort(store2.begin(), store2.end(), compareIsbn());
  files.push_back(store1);
  files.push_back(store2);
  reportResults(cin, cout, files);

  return 0;
}

/*
                                tuple支持的操作
    ——————————————————————————————————————————————————————————————————————————
    tuple<T1, T2, ..., Tn> t;                 | t是一个tuple，成员数为n
                                              | 所有成员都进行值初始化
    tuple<T1, T2, ..., Tn> t(v1, v2, ..., vn) | 每个成员根据对应的值进行初始化
                                              | 该构造函数是explicit的
    make_tuple(v1, v2, ..., vn) | 返回一个用给定初始值初始化的tuple
                                | tuple的类型通过初始值的类型推断
    ——————————————————————————————————————————————————————————————————————————
    t1 == t2    | 当两个tuple具有相同数量的成员且成员对应相等时，两个tuple相等
    t1 != t2    | 这两个操作通过成员的==运算符来完成
                | 一旦某个成员不等，接下来的成员就不再比较
    t1 relop t2 | tuple的关系运算使用字典序
                | 两个tuple必须具有相同数量的成员
                | 使用<运算符比较t1和t2中的对应成员
    get<i>(t)   | 返回t的第i个数据成员的引用
                | 如果t是一个左值，结果是一个左值引用，否则，结果是一个右值引用
                | tuple的所有成员都是public的
    ——————————————————————————————————————————————————————————————————————————
    tuple_size<Type>::value      | 一个类模板，可以通过一个tuple类型来初始化
                                 | 它有一个public constexpr static数据成员value
                                 | 类型为size_t，表示给定tuple类型中成员的数量
    tuple_element<i, Type>::type | 一个类模板，可以通过一个整型常量
                                 | 和一个tuple类型来初始化。
                                 | 它有一个名为tyPe的public成员
                                 | 表示给定tuple类型中指定成员的类型
    ——————————————————————————————————————————————————————————————————————————
*/