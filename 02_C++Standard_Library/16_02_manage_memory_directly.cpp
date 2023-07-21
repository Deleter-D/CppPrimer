#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 直接管理内存
int main(int argc, char const *argv[]) {
  // 默认初始化
  int *pi = new int; // pi指向一个动态分配的、未初始化的无名对象
  string *ps = new string; // 初始化为空string

  // 直接初始化
  int *pi2 = new int(1024);          // pi指向值为1024的int
  string *ps2 = new string(10, '9'); // ps2指向"9999999999"的string
  // vector有10个元素，值为列表中的值
  vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // 值初始化
  string *ps3 = new string;   // 默认初始化为空string
  string *ps4 = new string(); // 值初始化为空string
  int *pi3 = new int;         // 默认初始化，值未定义
  int *pi4 = new int();       // 值初始化，值为0

  // 使用auto从初始化器推断待分配对象的类型
  auto p1 = new auto(42);
  // auto p2 = new auto{1, 2, 3}; // 错误：括号中只能有单个初始化器

  // 用new分配const对象是合法的
  const int *pci = new const int(1024);
  const string *pcs = new const string;

  // 内存耗尽
  int *pi5 = new int; // 若分配失败，new抛出std::bad_alloc异常
  int *pi6 = new (nothrow) int; // 若分配失败，new返回空指针

  // 指针值和delete
  int i, *pi7 = &i, *pi8 = nullptr;
  double *pd = new double(33), *pd2 = pd;
  // delete i;   // 错误：i不是指针
  delete pi7; // 未定义：pi7指向一个非动态内存对象
  delete pd;  // 正确
  delete pd2; // 未定义：pd2指向的内存已经被释放
  delete pi8; // 正确：释放空指针总是没有错的

  const int *pci2 = new const int(1024);
  delete pci2; // 正确：释放const对象

  // 动态分配的对象，释放前会一直存在
  // 参考下方factory与use_factory函数

  // 在delete后，指针就变成了悬空指针
  int *p(new int(42)); // p指向动态内存
  auto q = p;          // p和q指向相同内存
  delete p;            // p和q均变为无效
  p = nullptr;         // 指出p不再绑定任何对象
  // q依然是悬空指针

  return 0;
}

int *factory(int arg) { return new int(arg); }

void use_factory(int arg) {
  int *p = factory(arg);
  // 使用完p后要delete
  // 否则当退出当前作用域后，p的生命周期结束了，但所指向的内存并未释放，就导致了内存泄漏
  delete p;
}

int *use_factory2(int arg) {
  int *p = factory(arg);
  // 或者将p返回
  // 当退出作用域后，p虽然不存在了，但由于返回了，故会有其他指针接管p原来指向的内存空间
  return p;
}