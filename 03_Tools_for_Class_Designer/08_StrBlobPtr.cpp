#include "08_StrBlobPtr.h"
#include <stdexcept>

string &StrBlobPtr::operator*() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr]; // (*p)是对象所指的vector
}

string *StrBlobPtr::operator->() const {
  // 将实际工作委托给解引用运算符
  return &this->operator*();
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i,
                                             const string &msg) const {
  auto ret = wptr.lock();
  if (!ret)
    throw runtime_error("unbound StrBlobPtr");
  if (i >= ret->size())
    throw out_of_range(msg);
  return ret;
}

string &StrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr() {
  check(curr, "increcement past end of StrBlobPtr");
  ++curr;
  return *this;
}