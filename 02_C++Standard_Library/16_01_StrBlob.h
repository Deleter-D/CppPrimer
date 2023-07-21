#ifndef STRBLOB_H
#define STRBLOB_H

#include "16_06_StrBlobPtr.h"
#include <memory>
#include <string>
#include <vector>
using namespace std;

class StrBlob {
  friend class StrBlobPtr;

public:
  typedef vector<string>::size_type size_type;
  StrBlob();
  StrBlob(initializer_list<string> il);
  size_type size() const { return data->size(); };
  bool empty() const { return data->empty(); };
  void push_back(const string &s) { data->push_back(s); }
  void pop_back();
  string &front();
  string &back();

  shared_ptr<vector<string>> getData();
  StrBlobPtr begin() { return StrBlobPtr(*this); }
  StrBlobPtr end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
  }

private:
  shared_ptr<vector<string>> data;
  void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il)
    : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const {
  if (i >= data->size())
    throw out_of_range(msg);
}

string &StrBlob::front() {
  check(0, "front on empty StrBlob");
  return data->front();
}

string &StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}

void StrBlob::pop_back() {
  check(0, "pop_back on empty StrBlob");
  return data->pop_back();
}

shared_ptr<vector<string>> StrBlob::getData() { return data; }

#endif