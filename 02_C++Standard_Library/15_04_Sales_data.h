#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>
using namespace std;

class Sales_data {
private:
  string bookNo;

public:
  Sales_data() = default;
  Sales_data(const string &s) : bookNo(s){};
  string isbn() const;
  ~Sales_data() = default;
};

string Sales_data::isbn() const { return bookNo; }

#endif