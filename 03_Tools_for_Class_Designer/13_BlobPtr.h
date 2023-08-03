#ifndef BLOBPTR_H
#define BLOBPTR_H

#include "13_Blob.h"
#include <memory>
#include <string>
#include <vector>

template <typename T> class Blob;

// 在类代码内简化模板类名的使用
template <typename T> class BlobPtr {
public:
  BlobPtr() : curr(0) {}
  BlobPtr(Blob<T> &a, std::size_t sz = 0) : wptr(a.data), curr(sz) {}
  T &operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
  }
  T *operator->() const { return &this->operator*(); }

  // 前置递增/递减运算符
  // 在类模板的作用域内，可以直接使用模板名，而不必指定模板实参
  BlobPtr &operator++() {
    check(curr, "increment past end of Blob");
    ++curr;
    return *this;
  }
  BlobPtr &operator--() {
    check(curr, "decrement past begin of Blob");
    --curr;
    return *this;
  }

  BlobPtr operator++(int);
  BlobPtr operator--(int);

private:
  // 若检查成功，check返回一个指向vector的shared_ptr
  std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &) const;
  // 保存也给weak_ptr，表示底层vector可能被销毁
  std::weak_ptr<std::vector<T>> wptr;
  std::size_t curr; // 数组当前位置
};

// 类模板外使用类模板名
// 后置递增/递减运算符，但返回原值
template <typename T> BlobPtr<T> BlobPtr<T>::operator++(int) {
  BlobPtr ret = *this; // 保存当前值
  ++*this;             // 推进一个元素，前置++检查递增的合法性
  return ret;          // 返回保存的状态
}

template <typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string &msg) const {
  auto ret = wptr.lock();
  if (!ret)
    throw std::runtime_error("unbound BlobPtr");
  if (i >= ret->size())
    throw std::out_of_range(msg);
  return ret;
}

#endif