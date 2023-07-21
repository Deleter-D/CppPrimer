#ifndef STRVEC2_H
#define STRVEC2_H

#include <memory>
#include <string>

class StrVec2 {
public:
  StrVec2() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec2(const StrVec2 &);
  StrVec2(StrVec2 &&s) noexcept
      : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    s.elements = s.first_free = s.cap = nullptr;
  }
  StrVec2 &operator=(const StrVec2 &);
  StrVec2 &operator=(StrVec2 &&) noexcept;
  ~StrVec2();
  void push_back(const std::string &); // 拷贝
  void push_back(std::string &&);      // 移动
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
  // 改造reallocate，令其使用移动操作，从而避免拷贝
  void reallocate();

  std::string *elements;
  std::string *first_free;
  std::string *cap;
};

std::allocator<std::string> StrVec2::alloc;

void StrVec2::push_back(const std::string &s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

// 右值引用的成员函数
void StrVec2::push_back(std::string &&s) {
  chk_n_alloc();
  alloc.construct(first_free++, std::move(s));
}

std::pair<std::string *, std::string *>
StrVec2::alloc_n_copy(const std::string *b, const std::string *e) {
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec2::free() {
  if (elements) {
    for (auto p = first_free; p != elements;)
      alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec2::StrVec2(const StrVec2 &s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec2::~StrVec2() { free(); }

StrVec2 &StrVec2::operator=(const StrVec2 &rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

StrVec2 &StrVec2::operator=(StrVec2 &&rhs) noexcept {

  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
}

void StrVec2::reallocate() {
  auto newcapacity = size() ? 2 * size() : 1;
  auto first = alloc.allocate(newcapacity);
  // 移动元素
  auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                      std::make_move_iterator(end()), first);
  free();
  elements = first;
  first_free = last;
  cap = elements + newcapacity;
}

#endif