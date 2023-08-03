#ifndef BLOB_H
#define BLOB_H

#include "13_BlobPtr.h"
#include <memory>
#include <stdexcept>
#include <vector>

// 类模板和友元：一对一友好关系
// 前置声明，在Blob中声明友元所需要的
template <typename T> class BlobPtr;
// 运算符==中的参数所需要的
template <typename T> class Blob;
template <typename T> bool operator==(const Blob<T> &, const Blob<T> &);

template <typename T> class Blob {
  // 每个Blob实例将访问权限授予相同类型实例化的BlobPtr和==运算符
  friend class BlobPtr<T>;
  friend bool operator==<T>(const Blob<T> &, const Blob<T> &);

public:
  typedef T value_type;
  typedef typename std::vector<T>::size_type size_type;

  // 构造函数
  Blob();
  Blob(std::initializer_list<T>);
  // 类模板的成员模板
  template <typename It> Blob(It b, It e);
  // Blob中的元素数目
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  // 添加和删除元素
  void push_back(const T &t) { data->push_back(t); }
  // 移动版本
  void push_back(T &&t) { data->push_back(std::move(t)); }
  void pop_back();
  // 元素访问
  T &front();
  T &back();
  T &operator[](size_type i);
  const T &operator[](size_type i) const;

private:
  std::shared_ptr<std::vector<T>> data;
  // 若data[i]无效，则抛出msg
  void check(size_type i, const std::string &msg) const;
};

// 类模板的构造函数
template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
    : data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>  // 类的类型参数
template <typename It> // 构造函数的类型参数
Blob<T>::Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e)) {}

// 类模板的成员函数
template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
  if (i >= data->size())
    throw std::out_of_range(msg);
}

template <typename T> void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  return data->pop_back();
}

template <typename T> T &Blob<T>::front() {
  check(0, "front on empty Blob");
  return data->front();
}

template <typename T> T &Blob<T>::back() {
  check(0, "back on empty Blob");
  return data->back();
}

template <typename T> T &Blob<T>::operator[](size_type i) {
  check(i, "subscript out of range");
  return (*data)[i];
}

template <typename T> const T &Blob<T>::operator[](size_type i) const {
  check(i, "subscript out of range");
  return (*data)[i];
}

template <typename T> bool operator==(const Blob<T> &b1, const Blob<T> &b2) {
  if (b1.size() != b2.size())
    return false;
  for (std::size_t i = 0; i < b1.size(); ++i) {
    if (b1[i] != b2[i])
      return false;
  }
  return true;
}

#endif