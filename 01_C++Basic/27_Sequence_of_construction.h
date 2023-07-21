#ifndef SEQUENCE_OF_CONSTRUCTION_H
#define SEQUENCE_OF_CONSTRUCTION_H

class Sequence {
  // 默认是private的
  int i;
  int j;

public:
  // 构造函数初始值列表中的顺序不会影响实际的初始化顺序
  // 初始化的顺序是成员出现在类中的顺序，故会先初始化i，再初始化j
  // 这将导致i在j之前被初始化，是未定义的行为
  Sequence(int val) : j(val), i(j) {}
  // 尽量使用参数作为初始化值，这样就与i和j的初始化顺序无关了
  // Sequence(int val) : j(val), i(val) {}

  // 一个构造函数为所有参数都提供了默认实参，也就定义了默认构造函数
  Sequence(int val = 0) : j(val), i(val) {}
};

#endif