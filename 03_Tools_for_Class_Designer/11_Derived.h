#ifndef DERIVED_H
#define DERIVED_H

#include "11_Base.h"

class Derived : public Base {
  void f(const Derived &);
};

void Derived::f(const Derived &derived_obj) {
  Base::statmem();       // 通过基类访问
  Derived::statmem();    // 通过派生类访问
  derived_obj.statmem(); // 通过派生类对象访问
  statmem();             // 通过this对象访问
}

#endif