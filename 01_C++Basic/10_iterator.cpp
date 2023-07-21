using namespace std;
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
  // begin返回指向第一个元素的迭代器
  // end返回指向最后一个元素的迭代器，称为尾后迭代器
  // 尾后迭代器指向容器尾元素的下一位置，并不实际指示某个元素，故不能对其进行递增或解引用
  // 若容器为空，则begin和end返回的都是尾后迭代器，可通过此来判断容器是否为空
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto b = v.begin(), e = v.end();

  // 迭代器访问string
  string s("some string");
  if (s.begin() != s.end()) {
    auto it = s.begin();
    *it = toupper(*it);
  }
  cout << s << endl;
  for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
    *it = toupper(*it);
  cout << s << endl;

  // 迭代器类型
  vector<int>::iterator it;        // it能读写vector<int>元素
  string::iterator it2;            // it2能读写string对象中的字符
  vector<int>::const_iterator it3; // it3只能读元素，不能写元素
  string::const_iterator it4;      // it4只能读元素，不能写元素

  // 若对象是常量，begin和end返回const_iterator，否则返回iterator
  vector<int> v;
  const vector<int> cv;
  auto it1 = v.begin();  // it1的类型是vector<int>::iterator
  auto it2 = cv.begin(); // it2的类型是vector<int>::const_iterator
  // C++11引入了cbegin和cend，可以在对象不是常量的情况下使用const_iterator
  auto it3 = v.cbegin(); // it3的类型是vector<int>::const_iterator

  // 结合解引用的成员访问
  vector<string> sv;
  auto sv_it = sv.begin();
  (*sv_it).empty();
  // *sv_it.empty(); //
  // 这是错误写法，试图访问sv_it的名为empty的成员，但sv_it是迭代器
  sv_it->empty(); // 箭头运算符，将解引用和成员访问两个操作合在一起

  // 注意：任意一种可能改变vector对象容量的操作，都会使相应的迭代器失效

  // 迭代器的运算
  // 实现二分查找
  vector<int> text = {1, 2, 3, 4, 5};
  auto sought = 2; // 目标值
  auto begin = text.begin(), end = text.end();
  auto mid = begin + (end - begin) / 2;

  while (mid != end && *mid != sought) {
    if (sought < *mid)
      end = mid;
    else
      begin = mid + 1;
    mid = begin + (end - begin) / 2;
  }
  if (mid != text.end())
    cout << "找到了" << *mid << endl;
  else
    cout << "没有找到" << endl;
  return 0;
}

/*
                                             标准容器迭代器的运算符
    ———————————————————————————————————————————————————————————————————————————————————————————————————————
    *iter           |  返回迭代器iter所指元素的引用
    iter->mem       |  解引用iter并获取该元素的名为mem的成员，等价于(*iter).mem
    ++iter          |  令iter指示容器的下一个元素
    --iter          |  令iter指示容器的上一个元素
    iter1 == iter2  |  判断两个迭代器是否相等，若两个迭代器指示的是同一个元素或它们是同一个容器的尾后迭代器，则相等
    iter1 != iter2  |  反之，不相等
    ———————————————————————————————————————————————————————————————————————————————————————————————————————
*/

/*
                              vector和string迭代器支持的运算
    ————————————————————————————————————————————————————————————————————————————————————
    iter + n       |  迭代器向尾部移动n个元素，结果迭代器指示容器内的一个元素或成为尾后迭代器
    iter - n       |  迭代器向头部移动n个元素，结果迭代器指示容器内的一个元素或成为尾后迭代器
    iter += n      |  将iter + n的结果赋给iter
    iter -= n      |  将iter - n的结果赋给iter
    iter1 - iter2  |  两个迭代器相减得到它们之间的距离
    >,>=,<,<=      |  迭代器指示的元素越靠尾部越大
    ————————————————————————————————————————————————————————————————————————————————————
*/