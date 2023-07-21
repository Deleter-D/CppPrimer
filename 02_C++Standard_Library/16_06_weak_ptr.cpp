#include "16_01_StrBlob.h"
#include "16_06_StrBlobPtr.h"
#include <memory>
using namespace std;
// weak_ptr绑定到shared_ptr,不会改变引用计数

int main(int argc, char const *argv[]) {
  auto p = make_shared<int>(42);
  weak_ptr<int> wp(p); // wp弱共享p,p的引用计数未改变
  // 不能使用weak_ptr直接访问对象,必须调用lock
  if (shared_ptr<int> np = wp.lock()) // 若np不空则条件成立
  {
    // 在if中,np与p共享对象
  }

  // 使用伴随指针类
  StrBlob b;
  auto beg = b.begin();
  auto end = b.end();

  return 0;
}

/*
                                weak_ptr
    ——————————————————————————————————————————————————————————————
    weak_ptr<T> w     | 空weak_ptr可以指向类型T的对象
    weak_ptr<T> w(sp) | 与shared_ptr sp指向相同对象的weak_ptr,
                      | T必须能转换为sp指向的类型
    w = p             | p可以是一个shared_ptr或weak_ptr,
                      | 赋值后w与p共享对象
    w.reset()         | 将w置空
    w.use_count()     | 与w共享对象的shared_ptr的数量
    w.expired()       | 若w.use_count()为0则返回true,否则返回false
    w.lock()          | 若expired为ture,返回空shared_ptr,
                      | 否则返回一个指向w的对象的shared_ptr
    ——————————————————————————————————————————————————————————————
*/