using namespace std;
#include "24_Sales_data_2.h"
#include <iostream>

int main() {
  Sales_data total;
  if (read(cin, total)) {
    Sales_data trans;
    while (read(cin, trans)) {
      if (total.isbn() == trans.isbn())
        total.combine(trans);
      else {
        print(cout, total) << endl;
        total = trans; // Sales_data的默认赋值操作
                       /* 上述操作等价于：
                          total.bookNo = trans.bookNo;
                          total.units_sold = trans.units_sold;
                          total.revenue = trans.revenue;
                       */
      }
    }
    print(cout, total) << endl;
  } else {
    cerr << "No data!" << endl;
  }
}