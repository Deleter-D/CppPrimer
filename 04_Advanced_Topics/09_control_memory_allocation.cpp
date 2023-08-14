#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

struct MyClass {
  MyClass() { cout << "MyClass constructed\n"; }
  ~MyClass() { cout << "MyClass destructed\n"; }

  // operator new函数和operator delete函数
  // 可以定义为全局作用域，也可以定义为成员函数

  // operator new的返回类型必须是void*
  // 第一个参数必须是size_t，不允许有默认实参
  void *operator new(size_t t) {
    puts("override version: normal.");
    void *m = malloc(t);
    if (m)
      return m;
    else
      throw bad_alloc();
  }

  void *operator new(size_t t, nothrow_t obj) noexcept {
    puts("override version: nothrow.");
    void *m = malloc(t);
    return m;
  }

  // void *operator new(size_t, void*)不允许重载

  void operator delete(void *p) noexcept {
    puts("deleting normal.");
    free(p);
  }

  void operator delete(void *p, nothrow_t obj) noexcept {
    puts("deleting nothrow.");
    free(p);
  }
};

class Foo {
public:
  Foo(int val = 0) { _val = val; }

  void writeFoo() {
    cout << "_val: " << _val << ", address: " << this;
    cout << endl;
  }
  ~Foo() = default;

private:
  int _val;
};

int main(int argc, char const *argv[]) {
  string *sp = new string("a value"); // 分配并初始化一个string对象
  string *arr = new string[10]; // 分配10个默认初始化的string对象
  // new表达式实际执行的三个步骤：
  // - new表达式调用名为operator new或operator new[]的标准库函数，
  //   分配一块足够大的、原始的、未命名的内存空间
  // - 运行相应的构造函数，创建对象
  // - 返回一个指向该对象的指针
  delete sp;    // 销毁*sp，然后释放sp指向的内存空间
  delete[] arr; // 销毁数组中的元素，然后释放对应的内存空间
  // delete表达式实际执行的两个步骤：
  // - 对指针所指向的对象或者数组指针所指的数组中的元素调用析构函数
  // - 编译器调用名为operator delete或operator delete[]的标准库函数，
  //   释放内存空间

  // 如果希望控制内存分配的过程，则需要定义自己的
  // operator new函数和operator delete函数

  MyClass *pt = new (nothrow) MyClass; // 指定调用noexcept版本的operator new
  delete pt;
  // 若new失败了，且是nothrow版本，则调用的delete将是nothrow版本
  // 否则将使正常版本，这个过程是自动的
  cout << endl;
  MyClass *pt2 = new MyClass;
  delete pt2;

  // 定位new表达式
  // 当只传入一个指针类型的实参时，new表达式构造对象但不分配内存
  // 分配3个Foo对象所需的内存空间
  char *buf = new char[sizeof(Foo) * 3];
  // 实例化Foo对象，并将其放到buf中的第1个Foo位置
  Foo *pb = new (buf) Foo(0);
  // 实例化Foo对象，并将其放到buf中的第3个Foo位置
  Foo *pb1 = new (buf + sizeof(Foo) * 2) Foo(1);
  // 实例化Foo对象，并将其放到buf中的第2个Foo位置
  Foo *pb2 = new (buf + sizeof(Foo)) Foo(2);

  pb->~Foo(); // 调用析构函数会销毁对象，但不会释放内存
  pb->writeFoo();
  pb1->writeFoo();
  pb2->writeFoo();
  return 0;
}
