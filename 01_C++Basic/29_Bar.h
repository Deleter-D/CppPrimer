#ifndef BAR_H
#define BAR_H

class Bar {
public:
private:
  static Bar mem1; // 正确：静态成员可以是不完全类型
  Bar *mem2;
  // Bar mem3; // 错误：数据成员必须是完全类型
};

class Screen {
public:
  // 可以使用静态成员作为默认实参，因为它本身并不是对象的一部分
  Screen &clear(char = bkground);

private:
  static const char bkground;
};

#endif