#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

class QueryResult
{
    friend std::ostream &print(std::ostream &, const QueryResult &);

  public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f)
        : sought(s), lines(p), file(f)
    {
    }

  private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

std::ostream &print(std::ostream &, const QueryResult &);

#endif