#ifndef RECORD_H
#define RECORD_H

using namespace std;
#include <string>

struct Account {
  string account_num;
  string password;
};

struct Phone {
  string phone_num;
  string location;
};

struct Name {
  string name;
  unsigned short gender;
};

struct Record {
  Account account;
  Phone phone;
  Name name;
};

#endif