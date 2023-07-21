#ifndef WINDOW_H
#define WINDOW_H

#include <string>
using sz = std::string::size_type;

struct Window {
  sz height;
  sz width;
  char background;
};

#endif