#include "05_StrVec.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  StrVec strvec;
  strvec.push_back("Hello");
  strvec.push_back("World");
  cout << "size: " << strvec.size() << endl;
  cout << "capacity: " << strvec.capacity() << endl;
  return 0;
}
