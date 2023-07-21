#ifndef STRVEC3_H
#define STRVEC3_H

#include <memory>
#include <string>

class StrVec3 {
public:
  StrVec3() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec3(const StrVec3 &);
  StrVec3(StrVec3 &&s) noexcept
      : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    s.elements = s.first_free = s.cap = nullptr;
  }
  StrVec3 &operator=(const StrVec3 &);
  StrVec3 &operator=(StrVec3 &&) noexcept;
  ~StrVec3();
  void push_back(const std::string &);
  void push_back(std::string &&);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }

  // 重载下标运算符
  std::string &operator[](std::size_t n) { return elements[n]; }
  const std::string &operator[](std::size_t n) const { return elements[n]; }

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

std::allocator<std::string> StrVec3::alloc;

void StrVec3::push_back(const std::string &s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec3::push_back(std::string &&s) {
  chk_n_alloc();
  alloc.construct(first_free++, std::move(s));
}

std::pair<std::string *, std::string *>
StrVec3::alloc_n_copy(const std::string *b, const std::string *e) {
  auto data = alloc.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec3::free() {
  if (elements) {
    for (auto p = first_free; p != elements;)
      alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec3::StrVec3(const StrVec3 &s) {
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec3::~StrVec3() { free(); }

StrVec3 &StrVec3::operator=(const StrVec3 &rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

StrVec3 &StrVec3::operator=(StrVec3 &&rhs) noexcept {

  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
}

void StrVec3::reallocate() {
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