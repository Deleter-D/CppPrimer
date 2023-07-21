#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void elimDups(vector<string> &words);
bool isShoter(const string &s1, const string &s2);

int main(int argc, char const *argv[]) {
  vector<string> words = {"the",  "quick", "red",  "fox", "jumps",
                          "over", "the",   "slow", "red", "turtle"};
  /*
      第三个参数是一个谓词
      - 谓词是一个可调用的表达式
      - 返回结果是一个能用作条件的值
      - 谓词分为一元谓词和二元谓词
  */
  sort(words.begin(), words.end(), isShoter);
  for (auto &item : words)
    cout << item << " ";
  cout << endl;

  elimDups(words);
  // 稳定排序算法，维持相等元素的原有顺序
  stable_sort(words.begin(), words.end(), isShoter);
  for (auto &item : words)
    cout << item << " ";
  cout << endl;

  return 0;
}

void elimDups(vector<string> &words) {
  // 按照字典顺序排序容器
  sort(words.begin(), words.end());
  // 消除相邻重复项，并将不重复的项排列在容器前部
  // 返回指向不重复区域之后一个位置的迭代器
  auto end_unique = unique(words.begin(), words.end());
  // 将不重复区域之后的元素都清除
  words.erase(end_unique, words.end());
}

bool isShoter(const string &s1, const string &s2) {
  return s1.size() < s2.size();
}
