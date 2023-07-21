#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  // 填充算法
  vector<int> vec({1, 2, 3, 4, 5});
  // 将范围内元素重置为0
  fill(vec.begin(), vec.end(), 0);
  for (auto item : vec)
    cout << item << " ";
  cout << endl;
  // 将范围内元素重置为10
  fill(vec.begin(), vec.begin() + vec.size() / 2, 10);
  for (auto item : vec)
    cout << item << " ";
  cout << endl;

  vector<int> vec2;
  // 将所有元素置0
  fill_n(vec2.begin(), vec2.size(), 0);

  // vector<int> vec3;
  // 错误：容器本身没有10个元素
  // fill_n(vec3.begin(), 10, 1);

  // 插入迭代器
  // back_inster，定义在头文件iterator中的函数
  // 接受指向容器的引用，返回绑定该容器的插入迭代器
  vector<int> vec3;
  auto it = back_inserter(vec3); // 通过该迭代器赋值，元素将插入容器中
  *it = 42;

  vector<int> vec4;
  // 正确：利用插入迭代器添加元素
  fill_n(back_inserter(vec4), 10, 0);

  // 拷贝算法
  int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int a2[sizeof(a1) / sizeof(*a1)];
  // 将a1的内容拷贝给a2
  auto ret = copy(begin(a1), end(a1), a2);

  list<int> intList({0, 0, 1, 0, 0, 1});
  // 将所有值为0的元素替换为42
  replace(intList.begin(), intList.end(), 0, 42);

  list<int> ilist({0, 0, 1, 0, 0, 1});
  vector<int> ivec;
  // ilist并未改变，ivec包含ilist的一份拷贝，但ilist中值为0的元素，在ivec中都变为了42
  replace_copy(ilist.cbegin(), ilist.cend(), back_inserter(ivec), 0, 42);

  return 0;
}