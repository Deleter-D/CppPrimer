#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void elimDups(vector<string> &words);

int main(int argc, char const *argv[]) {
  // 重排容器元素算法
  vector<string> words = {"the",  "quick", "red",  "fox", "jumps",
                          "over", "the",   "slow", "red", "turtle"};
  elimDups(words);

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