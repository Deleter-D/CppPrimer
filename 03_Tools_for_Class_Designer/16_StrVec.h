#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>

class StrVec {
public:
  // 声明一个模板函数，将新的元素放在容器末尾
  // 参数使用的是右值引用，在适当时候进行折叠
  template <class... Args> void emplace_back(Args &&...);

  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec &);
  StrVec(StrVec &&s) noexcept
      : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    s.elements = s.first_free = s.cap = nullptr;
  }
  StrVec &operator=(const StrVec &);
  StrVec &operator=(StrVec &&) noexcept;
  ~StrVec();
  void push_back(const std::string &);
  void push_back(std::string &&);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }
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

// 函数实现
template <class... Args> inline void StrVec::emplace_back(Args &&...args) {
  chk_n_alloc(); // 若需要则重新分配StrVec的内存空间
  alloc.construct(first_free++, std::forward<Args>(args)...);
}

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s) {
  chk_n_alloc();
  alloc.construct(first_free++, std::move(s));
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

  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
}

void StrVec::reallocate() {
  auto newcapacity = size() ? 2 * size() : 1;
  auto first = alloc.allocate(newcapacity);
  auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                      std::make_move_iterator(end()), first);
  free();
  elements = first;
  first_free = last;
  cap = elements + newcapacity;
}

#endif