#ifndef SHORTERSTRING_H
#define SHORTERSTRING_H

#include <string>

class ShorterString {
public:
  bool operator()(const std::string &s1, const std::string &s2) const {
    return s1.size() < s2.size();
  }
};

#endif