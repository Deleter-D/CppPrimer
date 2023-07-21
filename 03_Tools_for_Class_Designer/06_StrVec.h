#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>

class StrVec {
public:
  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec &);
  // 移动构造函数
  // 不抛出异常的移动构造函数和移动赋值运算符必须标记为noexcept
  StrVec(StrVec &&s) noexcept // 移动操作不应该抛出任何异常
                              // 成员初始化器接管s中的资源
      : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    // 令s进入这样的状态，对其运行析构函数是安全的
    // 若不进行这一步，对s进行析构时，会释放掉刚刚移动的内存
    s.elements = s.first_free = s.cap = nullptr;
  }
  StrVec &operator=(const StrVec &);
  // 移动赋值运算符
  StrVec &operator=(StrVec &&) noexcept;
  ~StrVec();
  void push_back(const std::string &);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }

private:
  static std::allocator<std::string> alloc;
  void chk_n_alloc() {
    if (size() == capacity())
      reallocate();
  }
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                       const std::string *);
  void free();
  void reallocate();

  std::string *elements;
  std::string *first_free;
  std::string *cap;
};

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  if (elements) {
    for (auto p = first_free; p != elements;)
      alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec::StrVec(const StrVec &s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
  // 直接检测自赋值
  if (this != &rhs) {
    free();                  // 释放已有元素
    elements = rhs.elements; // 从rhs接管资源
    first_free = rhs.first_free;
    cap = rhs.cap;
    // 将rhs置于可以析构的状态
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
}

void StrVec::reallocate() {
  auto newcapacity = size() ? 2 * size() : 1;
  auto newdata = alloc.allocate(newcapacity);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i = 0; i != size(); ++i)
    alloc.construct(dest++, std::move(*elem++));
  free();
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

#endif