#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>

class StrVec {
public:
  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec &);
  StrVec &operator=(const StrVec &);
  ~StrVec();
  void push_back(const std::string &);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }

private:
  // 分配元素工具
  // 此处只是声明，类的静态数据成员需要在类外定义
  static std::allocator<std::string> alloc;
  // 被添加元素的函数所使用
  void chk_n_alloc() {
    if (size() == capacity())
      reallocate();
  }
  // 被拷贝构造函数、赋值运算符和析构函数所使用
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                       const std::string *);
  void free();       // 销毁元素并释放内存
  void reallocate(); // 获得更多内存并拷贝已有元素

  std::string *elements;   // 指向数组首元素的指针
  std::string *first_free; // 指向数组第一个空闲元素的指针
  std::string *cap;        // 指向数组尾后位置的指针
};

// 定义static成员
std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s) {
  chk_n_alloc();                    // 确保有空间容纳新元素
  alloc.construct(first_free++, s); // 在first_free指向的元素中构建s的副本
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
  // 分配空间保存给定范围中的元素，分配的空间恰好容纳给定的元素
  auto data = alloc.allocate(e - b);
  // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  // 不能传递给deallocate一个空指针，若elements为0，则函数不进行任何操作
  if (elements) {
    for (auto p = first_free; p != elements;)
      alloc.destroy(--p); // 逆序销毁
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec::StrVec(const StrVec &s) {
  // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs) {
  // 调用alloc_n_copy分配空间以容纳与rhs中一样多的元素
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

void StrVec::reallocate() {
  // 分配当前大小两倍的内存空间
  auto newcapacity = size() ? 2 * size() : 1;
  // 分配新内存
  auto newdata = alloc.allocate(newcapacity);
  // 将数据从旧内存移动到新内存
  auto dest = newdata;  // 指向新数据中下一个空闲位置
  auto elem = elements; // 指向旧数据中下一个元素
  for (size_t i = 0; i != size(); ++i)
    // 重新分配过程中是移动而不是拷贝元素
    alloc.construct(dest++, std::move(*elem++));
  free(); // 移动完成后释放旧内存空间
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

#endif