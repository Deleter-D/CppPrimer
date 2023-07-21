#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

#include "16_01_StrBlob.h"
#include <memory>
#include <string>
#include <vector>
using namespace std;

class StrBlobPtr {
public:
  StrBlobPtr() : curr(0){};
  StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.getData()), curr(sz){};
  string &deref() const;
  StrBlobPtr &incr(); // 前缀递增

private:
  shared_ptr<vector<string>> check(size_t, const string &) const;
  weak_ptr<vector<string>> wptr; // 保存一个weak_ptr意味着底层vector可能被销毁
  size_t curr;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i,
                                             const string &msg) const {
  auto ret = wptr.lock(); // 判断底层vector是否还存在
  if (!ret)
    throw runtime_error("unbound StrBlobPtr");
  if (i >= ret->size())
    throw out_of_range(msg);
  return ret; // 返回vector的shared_ptr
}

string &StrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr]; //*p是对象所指的vector
}

StrBlobPtr &StrBlobPtr::incr() {
  // 若curr指向容器尾后则不能递增
  check(curr, "increcement past end of StrBlobPtr");
  ++curr;       // 推进
  return *this; // 返回递增后的对象
}

#endif