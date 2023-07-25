#ifndef NOTQUERY_H
#define NOTQUERY_H

#include "12_Query.h"
#include "12_QueryResult.h"
#include "12_Query_base.h"
#include "12_TextQuery.h"
#include <memory>
#include <string>

class NotQuery : public Query_base {
  friend Query operator~(const Query &);

  NotQuery(const Query &q) : query(q) {}
  // 具体的类：NotQuery将定义所有继承而来的纯虚函数
  QueryResult eval(const TextQuery &) const;
  std::string rep() const { return "~(" + query.rep() + ")"; }

  Query query;
};

inline Query operator~(const Query &operand) {
  return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const {
  // 通过Query运算对象对eval进行虚调用
  auto result = query.eval(text);
  // 开始时结果set为空
  auto ret_lines = std::make_shared<std::set<line_no>>();
  // 必须在运算对象出现的所有行中进行迭代
  auto beg = result.begin(), end = result.end();
  // 对于输入文件的每一行，如果不在result中，将其添加到ret_lines
  auto sz = result.get_file()->size();
  for (std::size_t n = 0; n != sz; ++n) {
    // 若还没有处理完result的所有行
    // 检查当前行是否存在
    if (beg == end || *beg != n)
      ret_lines->insert(n); // 若不在result中，添加该行
    else if (beg != end)
      ++beg; // 否则继续获取result的下一行
  }
  return QueryResult(rep(), ret_lines, result.get_file());
}

#endif