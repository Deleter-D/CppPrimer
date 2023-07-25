#ifndef ANDQUERY_H
#define ANDQUERY_H

#include "12_BinaryQuery.h"
#include "12_Query.h"
#include "12_QueryResult.h"
#include "12_TextQuery.h"
#include <algorithm>
#include <memory>
#include <set>

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &, const Query &);

  AndQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "&") {}
  // 具体的类：AndQuery继承了rep并定义了其他纯虚函数
  QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const {
  // 通过Query运算对象进行虚调用，获得运算对象的查询结果set
  auto left = lhs.eval(text), right = rhs.eval(text);
  // 保存left和right的交集set
  auto ret_lines = std::make_shared<std::set<line_no>>();
  // 将两个范围的交集写入一个目的迭代器中
  // 本次调用的目的迭代器向ret添加元素
  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                        std::inserter(*ret_lines, ret_lines->begin()));
  return QueryResult(rep(), ret_lines, left.get_file());
}

#endif