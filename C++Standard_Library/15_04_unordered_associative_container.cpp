#include "15_04_Sales_data.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 无序容器不使用比较运算符来组织元素，而是使用哈希函数和关键字类型的==运算符
// 无序容器的性能依赖于哈希函数的质量和桶的数量大小
// 每个挂载元素的位置称为一个桶

size_t hasher(const Sales_data &sd);
bool eqOp(const Sales_data &lhs, const Sales_data &rhs);

int main(int argc, char const *argv[])
{
    // 单词排序不按字典顺序
    unordered_map<string, size_t> word_count;
    string word;
    while (cin >> word)
        ++word_count[word];
    for (const auto &w : word_count)
        cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl;

    // 无序容器默认情况下
    // - 使用关键字类型的==运算符比较元素
    // - 使用一个hash<key_type>类型的对象来生成每个元素的哈希值
    // - 标准库为内置类型(包括指针)、string、智能指针都提供了hash模板
    using SD_multiset = unordered_multiset<Sales_data, decltype(hasher) *, decltype(eqOp) *>;
    SD_multiset bookStore(42, hasher, eqOp);
    cout << bookStore.bucket_count() << endl;
    // 若自定义类型重载了==运算符，则可以不传入无序容器的第三个类型参数
    return 0;
}

// 自定义哈希函数
size_t hasher(const Sales_data &sd)
{
    return hash<string>()(sd.isbn());
}

bool eqOp(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

/*
                                    无序容器管理操作
    ———————————————————————————————————————————————————————————————————————————————
    桶接口
    c.bucket_count()     | 正在使用的桶数目
    c.max_bucket_count() | 容器能容纳的桶数量上限
    c.bucket_size(n)     | 返回第n个桶中的元素数量
    c.bucket(k)          | 关键字为k的元素在哪个桶中
    ———————————————————————————————————————————————————————————————————————————————
    桶迭代器
    local_iterator         | 可以用来访问桶中元素的迭代器类型
    const_local_iterator   | 桶迭代器的const版本
    c.begin(n), c.end(n)   | 桶n的首元素迭代器和尾后迭代器
    c.cbegin(n), c.cend(n) | 与上面两个类似，但返回const_local_iterator
    ———————————————————————————————————————————————————————————————————————————————
    哈希策略
    c.load_factor()     | 每个桶的平均元素数量，返回float值
    c.max_load_factor() | c试图维护的平均桶大小，返回float值
                        | c会在需要时添加新的桶，以使得load factor <= max_load_factor
    c.rehash(n)         | 重组存储，使得bucket_count >= n
                        | 且bucket_count > size / max_load_factor
    c.reserve(n)        | 重组存储，使得c可以保存n个元素且不必rehash
    ———————————————————————————————————————————————————————————————————————————————
*/