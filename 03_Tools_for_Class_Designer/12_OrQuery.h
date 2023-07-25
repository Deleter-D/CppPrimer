#ifndef ORQUERY_H
#define ORQUERY_H

#include "12_BinaryQuery.h"
#include "12_Query.h"
#include "12_QueryResult.h"
#include "12_TextQuery.h"
#include <memory>
#include <set>

class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);

  OrQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "|") {}
  // 具体的类：OrQuery继承了rep并定义了其他纯虚函数
  QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &rhs, const Query &lhs) {
  return std::shared_ptr<Query_base>(new OrQuery(rhs, lhs));
}

// 返回运算对象查询结果set的并集
QueryResult OrQuery::eval(const TextQuery &text) const {
  // 通过Query成员lhs和rhs进行的虚调用
  // 调用eval返回每个运算对象的QueryResult
  auto right = rhs.eval(text), left = lhs.eval(text);
  // 保存left和right的并集set
  auto ret_lines = std::make_shared<std::set<line_no>>();
  std::set_union(left.begin(), left.end(), right.begin(), right.end(),
                 std::inserter(*ret_lines, ret_lines->begin()));
  // 返回新的QueryResult，它表示lhs和rhs的并集
  return QueryResult(rep(), ret_lines, left.get_file());
}

#endif