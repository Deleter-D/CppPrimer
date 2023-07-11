#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// 顺序容器：元素按在容器中的位置保存和访问
// 关联容器：元素按关键字保存和访问

bool Shorter(const string &s1, const string &s2);
pair<string, int> process(vector<string> &v);

int main(int argc, char const *argv[])
{
    // 使用map
    map<string, size_t> word_cout;
    string word;
    while (cin >> word)
        ++word_cout[word];
    // 此处的w是pair类型，两个元素之间并不是键-值关系，只是单词的第一个、第二个元素
    // pair的数据成员是public的，所以可以直接访问w.first与w.second
    for (const auto &w : word_cout)
        cout << w.first << " occurs " << w.second << ((w.second > 1) ? "times" : "time") << endl;

    // 使用set
    map<string, size_t> word_cout2;
    set<string> exclude = {"The", "But", "And", "Or", "An", "A", "the", "but", "and", "or", "an", "a"};
    string word2;
    while (cin >> word2)
        if (exclude.find(word2) == exclude.end())
            ++word_cout2[word2];
    for (const auto &w : word_cout2)
        cout << w.first << " occurs " << w.second << ((w.second > 1) ? "times" : "time") << endl;

    // map和set中关键字必须唯一
    map<string, string> authors = {{"001", "张三"}, {"002", "李四"}};

    // multimap和multiset
    vector<int> ivec;
    for (vector<int>::size_type i = 0; i != 10; ++i)
    {
        ivec.push_back(i);
        ivec.push_back(i);
    }
    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> miset(ivec.cbegin(), ivec.cend());
    cout << "iset size: " << iset.size() << endl;
    cout << "ivec size: " << ivec.size() << endl;
    cout << "miset size: " << miset.size() << endl;

    // 有序容器：map、multimap、set、multiset关键字类型必须定义元素比较的方法
    // 若要传入比较方法，需先在容器的类型中传入函数的指针
    // 然后通过构造函数参数的形式将函数传入，函数名会被自动解析为指针
    multiset<string, decltype(Shorter) *> strSet(Shorter);
    strSet.insert({"short", "one"});
    for_each(strSet.cbegin(), strSet.cend(), [](const string &s) { cout << s << " "; });
    cout << endl;

    // pair类型，定义在头文件utility中
    pair<string, string> anno;
    pair<string, size_t> word_count;
    pair<string, vector<int>> line;

    // 以pair作为返回类型
    vector<string> strvec({"hello", "world"});
    auto res = process(strvec);
    cout << res.first << " " << res.second << endl;

    return 0;
}

bool Shorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

pair<string, int> process(vector<string> &v)
{
    if (!v.empty())
        // return {v.back(), v.back().size()}; // 列表初始化，C++11
        // return pair<string, int>(v.back(), v.back().size()); // 显式构造
        return make_pair(v.back(), v.back().size()); // 推断类型
    else
        return pair<string, int>(); // 显式构造，并不是空pair，而是用空字符串和0初始化了
}

/*
                       关联容器类型
    ——————————————————————————————————————————————————
    按关键字有序保存元素
    map      | 关联数组，保存键-值对
    set      | 关键字即值，即只保存关键字的容器
    multimap | 关键字可重复出现的map
    multiset | 关键字可重复出现的set
    ——————————————————————————————————————————————————
    无序容器
    unordered_map      | 用哈希函数组织的map
    unordered_set      | 用哈希函数组织的set
    unordered_multimap | 哈希组织的map，关键字可重复出现
    unordered_multiset | 哈希组织的set，关键字可重复出现
    ——————————————————————————————————————————————————
*/