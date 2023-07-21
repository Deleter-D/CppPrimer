#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;

map<string, string> buildMap(ifstream &map_file);
const string &transform(const string &s, const map<string, string> &m);
void word_transform(ifstream &map_file, ifstream &input);

int main(int argc, char const *argv[]) {
  ifstream map_file("./15_03_map_file.txt");
  ifstream input("./15_03_text.txt");
  word_transform(map_file, input);
  return 0;
}

// 读入文件，建立转换映射
map<string, string> buildMap(ifstream &map_file) {
  map<string, string> trans_map;
  string key, value;
  // 将第一个单词放入key中，后面的放入value中
  while (map_file >> key && getline(map_file, value)) {
    // 检查是否有转换规则
    if (value.size() > 1)
      // 此时value中存在一个前导空格，去掉前导空格
      trans_map[key] = value.substr(1);
    else
      throw runtime_error("no rule for " + key);
  }
  return trans_map;
}

// 生成转换文本
const string &transform(const string &s, const map<string, string> &m) {
  auto map_it = m.find(s);
  if (map_it != m.cend())
    return map_it->second;
  else
    return s;
}

void word_transform(ifstream &map_file, ifstream &input) {
  auto trans_map = buildMap(map_file);
  string line;
  while (getline(input, line)) // 逐行读取
  {
    istringstream stream(line); // 读取每个单词
    string word;
    bool firstword = true; // 控制是否输出空格
    while (stream >> word) {
      if (firstword)
        firstword = false;
      else
        cout << " ";
      cout << transform(word, trans_map);
    }
    cout << endl;
  }
}
