#ifndef AGGREGATE_CLASS_H
#define AGGREGATE_CLASS_H

#include <string>
// 聚合类
/* 满足如下条件的类称为聚合类：
   1、所有成员都是public的
   2、没有定义任何构造函数
   3、没有类内初始值
   4、没有基类，也没有virtual函数*/
struct Aggregate_class {
  int ival;
  std::string s;
};

#endif