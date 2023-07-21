#pragma once
#include <memory>
#include <string>
#include <vector>
using namespace std;

class StrBlobPtr;

class StrBlob {
  friend class StrBlobPtr;

public:
  typedef vector<string>::size_type size_type;
  StrBlob();
  StrBlob(initializer_list<string> il);
  size_type size() const;
  bool empty() const;
  void push_back(const string &s);
  void pop_back();
  string &front();
  string &back();

  shared_ptr<vector<string>> getData();
  StrBlobPtr begin();
  StrBlobPtr end();

private:
  shared_ptr<vector<string>> data;
  void check(size_type i, const string &msg) const;
};