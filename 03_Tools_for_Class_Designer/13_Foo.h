#ifndef FOO_H
#define FOO_H

#include <cstddef>

// 类模板的static成员
// 静态成员在模板类被实例化的时候就全部实例化了
// 而其他成员只有在被用到的时候才会实例化
template <typename T> class Foo {
public:
  using value_type = T;
  static std::size_t count() { return ctr; }

private:
  static std::size_t ctr;
};

// 将static数据成员定义成模板
// Foo被实例化时，定义并初始化ctr
template <typename T> std::size_t Foo<T>::ctr = 0;

// 使用类的类型成员
template <typename T>
// 由于类模板在未使用的时候不会被实例化，编译下方代码时可能类还不存在
// 故必须使用typename指定T::value_type是类型成员，而不是静态成员
typename T::value_type get_value(const T &c) {
  if (c.count() != 0)
    return c.count();
  else
    return typename T::value_type();
}
#endif