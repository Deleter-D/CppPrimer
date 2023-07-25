#ifndef BINARYQUERY_H
#define BINARYQUERY_H

#include "12_Query.h"
#include "12_Query_base.h"
#include <string>

class BinaryQuery : public Query_base {
protected:
  BinaryQuery(const Query &l, const Query &r, std::string s)
      : lhs(l), rhs(r), opSym(s) {}
  // 抽象类型：BinaryQuery不定义eval
  std::string rep() const {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
  }

  Query lhs, rhs;    // 左侧和右侧运算对象
  std::string opSym; // 运算符的名称
};

#endif