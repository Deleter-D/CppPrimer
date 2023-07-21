#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include "18_QueryResult.h"
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
class QueryResult;

class TextQuery {
public:
  using line_no = std::vector<std::string>::size_type;
  TextQuery(std::ifstream &);
  QueryResult query(const std::string &) const;

private:
  std::shared_ptr<std::vector<std::string>> file;
  // 该map用来映射每个单词与其出现的行号集合
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
  std::string text;
  while (std::getline(is, text)) // 逐行读取
  {
    file->push_back(text);         // 将该行插入vector中
    int n = file->size() - 1;      // 记录当前行号
    std::istringstream line(text); // 利用istringstream读取该行每个单词
    std::string word;
    while (line >> word) // 逐词读取
    {
      auto &lines = wm[word]; // 取map中以该单词为key的元素的引用
      if (!lines)
        // 若该单词不存在于map中，则创建一个新的元素
        lines.reset(new std::set<line_no>);
      // 否则直接插入行号
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::query(const std::string &sought) const {
  static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
  // 使用find而不是下标来避免在wm中添加单词
  // 返回一个pair，第一个元素是string，第二个元素是set<line_no>
  auto loc = wm.find(sought);
  if (loc == wm.end())
    // 未找到则返回包含空set的QueryResult
    return QueryResult(sought, nodata, file);
  else
    return QueryResult(sought, loc->second, file);
}

#endif