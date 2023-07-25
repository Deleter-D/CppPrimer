#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include "12_Query.h"
#include "12_QueryResult.h"
#include "12_TextQuery.h"
#include <string>

class Query_base {
  friend class Query;

protected:
  using line_no = TextQuery::line_no;
  virtual ~Query_base() = default;

private:
  // eval返回当前Query匹配的QueryResult
  virtual QueryResult eval(const TextQuery &) const = 0;
  // rep表示查询的一个string
  virtual std::string rep() const = 0;
};

#endif