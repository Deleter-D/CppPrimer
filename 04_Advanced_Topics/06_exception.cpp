#include <iostream>
#include <stdexcept>
using namespace std;

// 栈展开(Stack Unwinding)
// - 当程序抛出异常时，程序暂停当前函数的执行过程，
//     并立即开始查找最邻近的异常匹配的catch子句
// - 异常传递过程中，当退出了某些作用域时，
//     该作用域内异常发生前创建的局部对象会被销毁

// 栈展开过程沿着嵌套函数的调用链不断查找，知道找到匹配的catch子句
// 一个异常如果没有被捕获，程序将调用标准库函数terminate终止当前程序

class Except0 {
public:
  // 这里的try既能处理构造函数体抛出的异常，又能处理成员初始化列表抛出的异常
  Except0(int i) try : a(i) {
  } catch (const exception &) {
  };
  ~Except0() { cout << "Except0 is deconstructed." << endl; }

private:
  int a;
};
class Except1 {
public:
  ~Except1() { cout << "Except1 is deconstructed." << endl; }
};
class Except2 {
public:
  ~Except2() { cout << "Except2 is deconstructed." << endl; }
};

// noexcpet
// 该函数可以通过编译，虽然违反了异常说明
void f() noexcept { throw exception(); }
void g() {}
void h() noexcept(noexcept(f())) { f(); }
void i() noexcept(noexcept(g())) { g(); }

// 函数指针
void alloc(int) noexcept(false) {} // alloc可能抛出异常
void recoup(int) noexcept(true) {} // recoup不会抛出异常

class Base {
public:
  virtual double f1(double) noexcept;
  virtual int f2() noexcept(false);
  virtual void f3();
};
class Derived : public Base {
public:
  // double f1(double); // 错误：Base::f1承诺不会抛出异常
  int f2() noexcept(false); // 正确：与Base::f2的异常说明一致
  void f3() noexcept; // 正确：Derived的f3做了更严格的限定，是允许的
};

class str_mismatch : public logic_error {
public:
  explicit str_mismatch(const string &s) : logic_error(s) {}
  str_mismatch(const string &s, const string &lhs, const string &rhs)
      : logic_error(s), left(lhs), right(rhs) {}

  const string left, right;
};
void my_exception() { throw str_mismatch("string mismatch", "hello", "world"); }

int main(int argc, char const *argv[]) {
  try {
    try {
      Except0 ex(1);
      bad_alloc err;
      throw err;
    } catch (const bad_alloc &err) {
      Except1 ex;
      cout << err.what() << endl;
      throw; // 重新抛出，只要参数为引用，才会抛出修改后的异常
    } catch (const exception &err) {
      Except2 ex;
      cout << err.what() << endl;
    } catch (...) {
      cout << "Unknown exception" << endl;
    }
  } catch (const bad_alloc &err) {
    Except1 ex;
    cout << "Outer layer: " << err.what() << endl;
  } catch (const exception &err) {
    Except2 ex;
    cout << "Outer layer: " << err.what() << endl;
  } catch (...) {
    cout << "Outer layer: Unknown exception" << endl;
  }

  // noexcept异常说明，见上方定义的f(),g(),h(),i()
  // noexcept有两层含义：
  // - 当跟在函数参数列表后面时，它是异常说明符，如f()
  // - 当作为noexcept异常说明的bool实参出现时，它是一个运算符，如h()，i()
  try {
    cout << "f: " << boolalpha << noexcept(f()) << endl;
    cout << "g: " << boolalpha << noexcept(g()) << endl;
    cout << "h: " << boolalpha << noexcept(h()) << endl;
    cout << "i: " << boolalpha << noexcept(i()) << endl;
    // f();
  } catch (exception &e) {
    cout << "caught: " << e.what() << endl;
  }

  // 函数指针声明为noexcept，则指向的函数必须一致
  // 见上方定义的alloc(),recoup()
  // 正确：recoup和pf1都承诺不抛出异常
  void (*pf1)(int) noexcept = recoup;
  // 正确：recoup不抛异常，pf2可能抛异常，二者互不干扰
  void (*pf2)(int) = recoup;
  // pf1 = alloc; // 错误：alloc可能抛出异常，但pf1以及承诺不抛出异常
  pf2 = alloc; // 正确：pf2和alloc都可能抛出异常

  // 若虚函数承诺不抛出异常，则派生出的虚函数也必须做出相同的承诺
  // 见上方定义的Base与Derived类

  // 自定义异常类
  // 见上方定义的mismatch类
  try {
    my_exception();
  } catch (const str_mismatch &e) {
    cerr << e.what() << ": left str(" << e.left << "), right str(" << e.right
         << ")" << endl;
  }
  return 0;
}

/*
                          异常类层次
                          exception
                              |
        —————————————————————————————————————————————
        |             |               |             |
    bad_cast    runtime_error    logic_error    bad_alloc
                      |               |
    overflow_error————|               |————domain_error
    underflow_error———|               |————invalid_argument
    range_error———————|               |————out_of_range
                                      |————length_error
*/
