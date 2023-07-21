#include "08_StrBlob.h"
#include "08_StrBlobPtr.h"
#include <stdexcept>

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il)
    : data(make_shared<vector<string>>(il)) {}

StrBlob::size_type StrBlob::size() const { return data->size(); }

bool StrBlob::empty() const { return data->empty(); }

void StrBlob::push_back(const string &s) { data->push_back(s); }

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

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() {
  auto ret = StrBlobPtr(*this, data->size());
  return ret;
}

shared_ptr<vector<string>> StrBlob::getData() { return data; }
