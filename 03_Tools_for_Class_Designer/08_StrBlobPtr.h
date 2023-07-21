#pragma once
#include "08_StrBlob.h"
#include <memory>
#include <string>
#include <vector>
using namespace std;

class StrBlobPtr {
public:
  StrBlobPtr() : curr(0){};
  StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.getData()), curr(sz){};
  string &deref() const;
  StrBlobPtr &incr();
  // 重载成员访问运算符
  string &operator*() const;
  string *operator->() const;

private:
  shared_ptr<vector<string>> check(size_t, const string &) const;
  weak_ptr<vector<string>> wptr;
  size_t curr;
};