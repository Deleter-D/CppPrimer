#include <string>
using namespace std;
/*
    定义一个类时有两种选择：定义拷贝操作，使类的行为
    - 像一个值
    - 像一个指针
*/

// 行为像值的类：对于管理的资源，每个对象都应该拥有一份自己的拷贝
class HasPtr {
public:
  HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}
  // 对ps指向的string，每个HasPtr对象都有自己的拷贝
  HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) {}
  HasPtr &operator=(const HasPtr &);
  ~HasPtr() { delete ps; }

private:
  string *ps;
  int i;
};

// 如果将一个对象赋予它自己，赋值运算符必须能正确的工作
// 大多数赋值运算符组合了析构函数和拷贝构造函数的工作
HasPtr &HasPtr::operator=(const HasPtr &rhs) {
  /*
      错误的赋值运算符重载
      delete ps; // 释放对象指向的string
      // 如果rhs和*this是同一个对象，则该操作将从已经释放的内存中拷贝数据
      ps = new string(*rhs.ps);
      i = rhs.i;
      return *this;
  */

  auto newp = new string(*rhs.ps); // 拷贝底层string
  delete ps;                       // 释放旧内存
  ps = newp; // 从右侧运算对象拷贝数据到本对象
  i = rhs.i;
  return *this; // 返回本对象
}

// 行为像指针的类
// 此处使用自定义的引用计数
class HasPtr2 {
public:
  // 构造函数分配新的string和新的计数器，将计数器置1
  HasPtr2(const string &s = string())
      : ps(new string(s)), i(0), use(new size_t(1)) {}
  // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
  HasPtr2(const HasPtr2 &p) : ps(p.ps), i(p.i), use(p.use) { ++*use; }
  HasPtr2 &operator=(const HasPtr2 &);
  ~HasPtr2();

private:
  string *ps;
  int i;
  size_t *use; // 自定义的引用计数
};

HasPtr2::~HasPtr2() {
  // 如果析构掉本对象后计数器变为0，则销毁所有成员
  if (--*use == 0) {
    delete ps;
    delete use;
  }
}

HasPtr2 &HasPtr2::operator=(const HasPtr2 &rhs) {
  ++*rhs.use; // 递增右侧运算对象的引用计数
  // 递减本对象的引用计数
  if (--*use == 0) {
    delete ps;
    delete use;
  }
  ps = rhs.ps;
  i = rhs.i;
  use = rhs.use;
  return *this;
}