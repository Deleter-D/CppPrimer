#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 可以指向类的非静态成员的指针

class Screen {
public:
  typedef string::size_type pos;
  char get_cursor() const { return contents[cursor]; }
  char get() const {}
  char get(pos ht, pos wd) const {}

  string contents;
  pos cursor;
  pos height, width;
};

class Screen2 {
public:
  typedef string::size_type pos;
  char get_cursor() const { return contents[cursor]; }
  char get() const {}
  char get(pos ht, pos wd) const {}
  // data是一个静态成员，返回一个成员指针
  static const string Screen2::*data() { return &Screen2::contents; }

private:
  string contents;
  pos cursor;
  pos height, width;
};

// 指向Screen2成员函数的指针，接受两个pos实参，返回一个char
using Action = char (Screen2::*)(Screen2::pos, Screen2::pos) const;
Screen2 &action(Screen2 &, Action = &Screen2::get) {}

class Screen3 {
public:
  typedef string::size_type pos;
  char get_cursor() const { return contents[cursor]; }
  char get() const {}
  char get(pos ht, pos wd) const {}
  static const string Screen3::*data() { return &Screen3::contents; }

  using Action = Screen3 &(Screen3::*)();
  // 光标移动函数
  Screen3 &home() {
    cursor = 0;
    return *this;
  }
  Screen3 &forward() {
    cursor++;
    return *this;
  }
  Screen3 &back() {
    cursor--;
    return *this;
  }
  Screen3 &up() {
    cursor += height;
    return *this;
  }
  Screen3 &down() {
    cursor -= height;
    return *this;
  }

  enum Directions { HOME, FORWARD, BACK, UP, DOWN };
  Screen3 &move(Directions);

private:
  string contents;
  pos cursor;
  pos height, width;
  // 函数表，将上面5个光标移动函数以成员函数指针的形式存入数组中
  static Action Menu[];
};
Screen3 &Screen3::move(Directions cm) {
  // 通过函数表来调用不同的光标移动函数
  return (this->*Menu[cm])();
}
Screen3::Action Screen3::Menu[] = {&Screen3::home, &Screen3::forward,
                                   &Screen3::back, &Screen3::up,
                                   &Screen3::down};

int main(int argc, char const *argv[]) {
  // 数据成员的指针
  // pdata可以指向一个常量(非常量)Screen对象的string成员
  const string Screen::*pdata;
  // 一个指向Screen类的const string成员的指针
  pdata = &Screen::contents; // 初始化
  // 初始化后，该指针并没有指向任何对象
  // 也可以使用下句方便的定义类成员指针
  // auto pdata = &Screen::contents;

  // 使用数据成员指针
  Screen myScreen, *pScreen = &myScreen;
  // .*解引用pdata以获得myScreen对象的contents成员
  auto s = myScreen.*pdata;
  // ->*解引用pdata以获得pScreen指向的对象的contents成员
  s = pScreen->*pdata;

  // 数据成员一般是私有的，通常需要定义函数来返回指向该成员的指针
  const string Screen2::*pdata2 = Screen2::data();
  Screen2 myScreen2;
  auto s2 = myScreen2.*pdata2;

  // 成员函数指针
  // pmf是一个指针，可以指向Screen2的某个常量成员函数
  auto pmf = &Screen2::get_cursor;
  char (Screen2::*pmf2)(Screen2::pos, Screen2::pos) const;
  pmf2 = &Screen2::get;
  // 和普通函数指针不同，不存在自动转换规则

  // 使用成员函数指针
  Screen2 myScreen3, *pScreen3 = &myScreen3;
  // 通过pScreen所指的对象定义pmf所指的函数
  char c1 = (pScreen3->*pmf)();
  // 通过myScreen3对象将实参0，0传给含有两个形参的get函数
  char c2 = (myScreen3.*pmf2)(0, 0);

  // 使用成员指针的类型别名
  // 见上方定义的Action
  Action get = &Screen2::get;
  // 接受一个Screen引用和一个指向Screen成员函数的指针
  // 见上方定义的Screen2 &action(Screen2 &, Action = &Screen2::get);
  Screen2 myScreen4;
  // 等价调用
  action(myScreen4);                // 使用默认实参
  action(myScreen4, get);           // 使用定义的变量get
  action(myScreen4, &Screen2::get); // 显式传入地址

  // 成员指针函数表
  // 见上方定义的Screen3
  Screen3 myScreen5;
  myScreen5.move(Screen3::HOME);
  myScreen5.move(Screen3::DOWN);

  // 将成员函数用作可调用对象
  vector<string> svec;
  // fp指向string的empty函数
  auto fp = &string::empty;
  // 错误：必须使用.*或->*调用成员指针
  // find_if(svec.begin(), svec.end(), fp);
  // 错误：想通过成员指针调用函数，必须使用->*运算符
  // if (fp(*it)) {}
  // 成员指针不是可调用对象

  // 使用function生成一个可调用对象
  function<bool(const string &)> fcn = &string::empty;
  find_if(svec.begin(), svec.end(), fcn);
  // 指向成员函数的对象将被传给隐式的this形参
  // 假设it是find_if内部的迭代器，则*it是给定范围的一个对象
  // if(fcn(*it))
  // 本质上function将函数调用转换成了if((*it).*p())
  // 其中p是fcn内部的一个指向成员函数的指针

  // 使用mem_fn生成一个可调用对象
  // 和function不同，mem_fn可以根据成员指针的类型推断可调用对象的类型
  find_if(svec.begin(), svec.end(), mem_fn(&string::empty));
  // mem_fn生成的可调用对象含有一对重载的函数调用运算符
  auto f = mem_fn(&string::empty); // f接受一个string或string*
  f(*svec.begin()); // 正确：传入string对象，f使用.*调用empty
  f(&svec[0]);      // 正确：传入string指针，f使用->*调用empty

  // 使用bind生成一个可调用对象
  // 选择范围中的每个string，并将其bind到empty的第一个隐式实参上
  auto it =
      find_if(svec.begin(), svec.end(), bind(&string::empty, placeholders::_1));
  auto f2 = bind(&string::empty, placeholders::_1);
  f2(*svec.begin()); // 正确：传入string对象，f2使用.*调用empty
  f2(&svec[0]);      // 正确：传入string指针，f2使用->*调用empty

  return 0;
}
