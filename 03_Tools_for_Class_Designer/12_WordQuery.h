#ifndef WORDQUERY_H
#define WORDQUERY_H

#include "12_Query.h"
#include "12_QueryResult.h"
#include "12_Query_base.h"
#include "12_TextQuery.h"
#include <string>

class WordQuery : public Query_base {
  friend class Query; // Query使用WordQuery构造函数

  WordQuery(const std::string &s) : query_word(s) {}
  // 具体的类：WordQuery将定义所有继承而来的纯虚函数
  QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
  std::string rep() const { return query_word; }

  std::string query_word; // 待查找的单词
};

#endif