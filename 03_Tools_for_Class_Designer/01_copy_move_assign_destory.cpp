#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

/*
    一个类通过定义五种特殊的成员函数来控制对象的拷贝、移动、赋值和销毁
    - 拷贝构造函数
    - 拷贝赋值运算符
    - 移动构造函数
    - 移动赋值运算符
    - 析构函数
    如果一个类未定义上述操作，则编译器会自动合成缺失的操作
*/

class Foo {
public:
  Foo() { cout << "default constructor" << endl; }
  // 拷贝构造函数：第一个参数是自身类型的引用，额外参数都有默认值
  // 拷贝构造函数通常不应该是explicit的
  // 需要拷贝操作的类也需要赋值操作，反之亦然
  Foo(const Foo &) { cout << "copy constructor" << endl; }
  // 拷贝赋值运算符：接受一个与其所在类相同类型的参数
  Foo &operator=(const Foo &) { cout << "operator = overload" << endl; };
  // 析构函数：不接收参数，不允许重载
  // 构造函数初始化对象的非static数据成员
  // 析构函数释放对象的使用资源，并销毁对象的非static数据成员
  // 析构函数首先执行函数体，然后销毁成员
  // 需要自定义析构函数的类也需要拷贝和赋值操作
  ~Foo() { cout << "destructor" << endl; };
};
Foo f(Foo f) { return f; }

void fun(vector<int>) // fun的参数进行拷贝初始化
{
  cout << "vector's copy initialization." << endl;
};

int main(int argc, char const *argv[]) {
  cout << "Foo fooa ";
  Foo fooa;
  cout << "Foo foob(fooa) ";
  Foo foob(fooa);
  cout << "Foo fooc = foob ";
  Foo fooc = foob;
  cout << "f(foob) ";
  f(foob);

  // 拷贝初始化
  // 拷贝构造函数用来初始化非引用类类型参数，所以自己的参数必须是引用类型
  string dots(10, '.');               // 直接初始化
  string s(dots);                     // 直接初始化
  string s2 = dots;                   // 拷贝初始化
  string null_book = "9-999-99999-9"; // 拷贝初始化
  string nines = string(100, '9');    // 拷贝初始化

  // 拷贝初始化的限制
  vector<int> v1(10); // 正确：直接初始化
  // vector<int> v2 = 10; // 错误：接受大小的构造函数是explicit的
  // fun(10);           // 错误：不能用一个explicit的构造函数来拷贝一个实参
  fun(vector<int>(10)); // 正确：从一个int直接构造一个临时vector

  // 编译可以绕过拷贝构造函数
  string null_book2 = "9-999-99999-9"; // 拷贝初始化
  string null_book3("9-999-99999-9");  // 编译器略过了拷贝构造函数

  // 新作用域
  {
    Foo *p = new Foo;             // p为内置指针
    auto p2 = make_shared<Foo>(); // p2为shared_ptr
    Foo item(*p);                 // 拷贝构造函数将*p拷贝到item中
    vector<Foo> vec;              // 局部对象
    vec.push_back(*p2);           // 拷贝p2指向的对象
    // 当指向一个对象的引用或指针离开作用域时，不会执行析构函数，所以需要手动delete
    delete p; // 对p指向的对象调用析构函数
  }
  // 退出局部作用域，对item、p2和vec调用析构函数
  // 销毁p2会递减其引用计数，若引用计数变为0，对象被释放
  // 销毁vec会销毁它的元素
  return 0;
}

// 可以使用=default显式地要求编译器生成合成版本
class Sales_data {
public:
  Sales_data() = default;
  Sales_data(const Sales_data &) = default;
  Sales_data &operator=(const Sales_data &);
  ~Sales_data() = default;
};
Sales_data &Sales_data::operator=(const Sales_data &) = default; // 非内联

// 可以使用=delete阻止拷贝
// 与=defalut不同，=delete必须出现在函数第一次声明的时候，不能像上面非内联形式
struct NoCopy {
  NoCopy() = default;              // 使用合成的默认构造函数
  NoCopy(const NoCopy &) = delete; // 阻止拷贝
  NoCopy &operator=(const NoCopy &) = delete; // 阻止拷贝
  ~NoCopy() = default;                        // 使用合成的析构函数
};
// 若析构函数定义为了=delete，则不能定义该类型的变量或释放执行该类型动态分配对象的指针

// 本质上，当不可能拷贝、赋值或销毁类的成员时，类的合成拷贝控制成员就被定义为删除的
