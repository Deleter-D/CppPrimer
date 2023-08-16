#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>
using namespace std;

class TextQuery {
public:
  using line_no = vector<string>::size_type;
  // 嵌套类就像是外层类的成员一样，受到访问限制符的影响
  class QueryResult;
  QueryResult query(const string &) const;
};

class TextQuery::QueryResult {
  friend ostream &print(ostream &, const QueryResult &);

public:
  // 无需定义QueryResult::line_no
  // 嵌套类使用外层类的成员时无需对该成员的名称进行限定
  QueryResult(string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>);
  int static static_mem;
};
// 嵌套类是一个独立的类，与外层类基本没什么关系

// 定义嵌套类的成员
TextQuery::QueryResult::QueryResult(string s, shared_ptr<set<line_no>> ln,
                                    shared_ptr<vector<string>>) {}
int TextQuery::QueryResult::static_mem = 1024;

// 嵌套类作用域中的名称查找
// 返回类型必须指明QueryResult是一个嵌套类
TextQuery::QueryResult TextQuery::query(const string &s) const {
  // 内部再次使用就无需指定了
  return QueryResult(s, make_shared<set<line_no>>(),
                     make_shared<vector<string>>());
}