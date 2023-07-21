#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {
  // 关联容器的额外类型别名
  set<string>::key_type v1;         // v1为string
  set<string>::value_type v2;       // v2为string
  map<string, int>::key_type v3;    // v3为string
  map<string, int>::mapped_type v4; // v4为int
  map<string, int>::value_type v5;  // v5为pair<const string, int>

  // 关联容器迭代器
  map<string, int> word_cout({{"hello", 2}, {"world", 1}});
  // 指向map元素的迭代器
  auto map_it = word_cout.begin();
  // map_it是指向pair<const string, int>对象的引用
  cout << map_it->first << " " << map_it->second << endl;
  // map_it->first = "new key"; // 错误：关键字是const的
  ++map_it->second; // 正确：可以通过迭代器改变元素的值

  while (map_it != word_cout.end()) {
    cout << map_it->first << " occurs " << map_it->second << " times" << endl;
    ++map_it;
  }

  set<int> iset({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  auto set_it = iset.begin();
  // *set_it = 42; // 错误：关键字是只读的
  cout << *set_it << endl; // 正确：可以读取关键字

  // 添加元素
  map<string, size_t> word_count;
  string word;
  while (cin >> word) {
    // map的insert返回一个pair
    // first指向具体给定关键字的元素，second指出元素是否插入成功
    auto ret = word_count.insert({word, 1});
    if (!ret.second)
      ++ret.first->second;
  }

  // 删除元素
  string removal_word = "hello";
  if (word_count.erase(removal_word))
    cout << "ok: " << removal_word << " removed." << endl;
  else
    cout << "oops: " << removal_word << " not found." << endl;

  // map的下标操作
  // 下标操作可能插入新元素，故只能对非const的map使用下标操作
  // 在word_count中搜索Anna，未找到则会将一个新的键值对插入容器
  // 关键字是const string，保存Anna，将值初始化为0，后又赋值为1
  word_count["Anna"] = 1;

  // 访问元素
  set<int> iset2({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  iset2.find(1);
  iset2.find(11);
  iset2.count(1);
  iset2.count(11);

  // 在multimap中查找元素
  multimap<string, string> authors(
      {{"莫言", "丰乳肥臀"}, {"余华", "活着"}, {"莫言", "红高粱"}});
  string search_item("莫言");
  auto entries = authors.count(search_item);
  auto iter = authors.find(search_item);
  // 具有相同关键字的元素在容器中会相邻存储
  while (entries) {
    cout << iter->second << endl;
    ++iter;
    --entries;
  }
  // 通过上下界的方式
  for (auto beg = authors.lower_bound(search_item),
            end = authors.upper_bound(search_item);
       beg != end; ++beg)
    cout << beg->second << endl;
  // 通过equal_range方式
  for (auto range = authors.equal_range(search_item);
       range.first != range.second; ++range.first)
    cout << range.first->second << endl;

  return 0;
}

/*
                       关联容器额外的类型别名
    —————————————————————————————————————————————————————————
    key_type    | 此容器类型的关键字类型
    mapped_type | 每个关键字关联的类型，只适用于map
    value_type  | 对于set，与key_type相同
                | 对于map，为pair<const key_type, mapped_type>
    —————————————————————————————————————————————————————————
*/

/*
                      从关联容器删除元素
    ———————————————————————————————————————————————————————
    c.erase(k)    | 从c中删除每个关键字为k的元素
                  | 返回一个size_type值，指出删除的元素的数量
    ———————————————————————————————————————————————————————
    c.erase(p)    | 从c中删除迭代器p指定的元素，
                  | p必须指向c中一个真实元素，不能等于c.end()
                  | 返回一个指向p之后元素的迭代器，
                  | 若p指向c中的尾元素，则返回c.end()
    ———————————————————————————————————————————————————————
    c.erase(b, e) | 删除迭代器b和e所表示范围内的元素，返回e
    ———————————————————————————————————————————————————————
*/

/*
                    map和unordered_map的下标操作
    ———————————————————————————————————————————————————————————
    下标和at操作只适用于非const的map和unordered_map
    c[k]    | 返回关键字为k的元素，
            | 若k不在c中，添加一个关键字为k的元素，对其值进行初始化
    c.at(k) | 访问关键字为k的元素，带参数检查，
            | 若k不在c中，则抛出out_of_range异常
    ———————————————————————————————————————————————————————————
*/

/*
                         关联容器访问元素的操作
    ———————————————————————————————————————————————————————————————
    lower_bound和upper_bound不适用于无序容器
    ———————————————————————————————————————————————————————————————
    c.find(k)        | 返回一个迭代器，指向第一个关键字为k的元素
                     | 若k不在容器中，则返回尾后迭代器
    c.count(k)       | 返回关键字等于k的元素的数量
                     | 对于不允许重复关键字的容器，返回值永远是0或1
    c.lower_bound(k) | 返回一个迭代器，指向第一个关键字不小于k的元素
    c.upper_bound(k) | 返回一个迭代器，指向第一个关键字大于k的元素
    c.equal_range(k) | 返回一个迭代器pair，表示关键字等于k的元素的范围
                     | 若k不存在，pair的两个成员均等于c.end()
    ———————————————————————————————————————————————————————————————
*/