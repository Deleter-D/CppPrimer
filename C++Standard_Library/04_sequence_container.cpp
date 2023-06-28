#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <deque>
#include <array>
using namespace std;

// 假设noDefault是一个没有默认构造函数的类型
// vector<noDefault> v1(10, init); // 提供了元素初始化器，则正确
// vector<noDefault> v2(10);       // 没有提供初始化器，则错误

class A
{
public:
    // A未提供默认构造函数
    A(string b) { a = b; }

private:
    string a;
};

int main(int argc, char const *argv[])
{
    A aObj("hello");
    vector<A> objA(100, aObj);

    /*迭代器
    所有容器的迭代器接口的实现方式都相同
        访问元素（使用解引用实现）
        递增运算符（从当前元素移动到下一个元素）*/

    // 迭代器范围由一对迭代器begin和end表示（左闭右开区间）
    vector<int> nums = {1, 2, 3, 4, 5};
    auto begin = nums.begin();
    auto end = nums.end();
    while (begin != end)
    {
        *begin++ = 0;
    }
    for (int num : nums)
        cout << num << " ";

    // 每个容器定义了很多类型，想要使用这些类型，必须显式使用
    list<string>::iterator iter;
    vector<int>::difference_type cout;

    // begin和end有多个版本：带r的返回反向迭代器，以c开头的返回const迭代器
    list<string> a = {"Milton", "Shakespear", "Austen"};
    auto it1 = a.begin();   // list<string>::iterator
    auto it2 = a.rbegin();  // list<string>::reverse_iterator
    auto it3 = a.cbegin();  // list<string>::const_iterator
    auto it4 = a.crbegin(); // list<string>::const_reverse_iterator
    // it1 = it3; // 错误
    // it3 = it1; // 正确

    // 实际上有两个名为begin的成员，一个是const成员，返回const_iterator类型，一个是非常量成员，返回iterator类型
    // rbegin、end、rend等情况类似
    const list<string> b = {"Milton", "Shakespear", "Austen"};
    // list<string>::iterator cit1 = b.begin(); // 错误，this指针指向的是const对象
    list<string>::const_iterator cit2 = b.begin(); // 正确

    // 将一个容器初始化为另一个容器的拷贝
    list<string> authors = {"Milton", "Shakespear", "Austen"};
    vector<const char *> articles = {"a", "an", "the"};
    list<string> list2(authors); // 正确：类型匹配
    // deque<string> authList(authors); // 错误：容器类型不匹配
    // vector<string> words(articles); // 错误：容器类型不匹配
    forward_list<string> words(articles.begin(), articles.end()); // 正确：将const char*元素转换为string
    auto it = authors.end();
    deque<string> authList(authors.begin(), it); // 两个迭代器表示一个范围，拷贝元素直到（但不包括）it指向的元素

    // 与顺序容器大小相关的构造函数
    vector<int> ivec(10, -1);     // 10个int元素，每个都初始化为-1
    list<string> svec(10, "hi!"); // 10个string，每个都初始化为"hi!"
    forward_list<int> fivec(10);  // 10个元素，每个都初始化为0
    deque<string> dqsvec(10);     // 10个元素，每个都是空string
    // 标准库array的大小是类型的一部分
    array<int, 5> ia1;
    array<int, 5> ia2 = {0, 1, 2, 3, 4};
    array<int, 5> ia3 = {42};
    // 内置数组类型不能进行拷贝，或对象赋值操作，但array并无此限制
    int digs[5] = {0, 1, 2, 3, 4};
    // int cpy[5] = digs; // 错误：内置数组不支持拷贝或赋值
    array<int, 5> digits = {0, 1, 2, 3, 4};
    array<int, 5> copy = digits; // 正确：许局类型匹配即合法

    // 容器的赋值运算
    list<string> names;
    vector<const char *> oldstyle;
    // names = oldstyle; // 错误：容器类型不匹配
    names.assign(oldstyle.cbegin(), oldstyle.cend()); // 正确：可以将const char*转换为string

    list<string> slist1(1); // 一个元素，为空string
    // 下面这句等价于slist1.clear();  slist1.insert(slist1.begin(), 10, "Hiya!");
    slist1.assign(10, "Hiya!"); // 10个元素，每个都是"Hiya!"

    // swap操作交换两个相同类型容器的内容
    vector<string> svec1(10);
    vector<string> svec2(24);
    swap(svec1, svec2); // 调用完成后svec1包含24个string元素

    // 容器关系运算操作
    vector<int> v1 = {1, 3, 5, 7, 9, 12};
    vector<int> v2 = {1, 3, 9};
    vector<int> v3 = {1, 3, 5, 7};
    vector<int> v4 = {1, 3, 5, 7, 9, 12};
    v1 < v2;  // true
    v1 < v3;  // false
    v1 == v4; // true
    v1 == v2; // false
    // 当其他元素类型定义了相应的比较运算符时，才可以使用关系运算符来比较两个容器

    return 0;
}

/*
                                      顺序容器类型
    ———————————————————————————————————————————————————————————————————————————————————
    vector       | 可变大小数组。支持快速随机访问。在尾部之外的位置插入或删除元素可能变慢
    deque        | 双端队列。支持快速随机访问。在头尾位置插入或删除速度很快
    list         | 双向链表。只支持双向顺序访问。在list中任何位置进行插入或删除速度都很快
    forward_list | 单向链表。只支持单向顺序访问。在链表任何位置进行插入或删除操作速度都很快
    array        | 固定大小的数组。支持快速随机访问。不能添加或删除元素
    string       | 与vector相似的容器，但专用于保存字符。随机访问快。在尾部插入或删除速度很快
    ———————————————————————————————————————————————————————————————————————————————————
*/

/*
                                                容器定义和初始化
    ————————————————————————————————————————————————————————————————————————————————————————————————————————————
    C c;                | 默认构造函数。若C是一个array，则c中元素按默认方式初始化，否则c为空
    ————————————————————————————————————————————————————————————————————————————————————————————————————————————
    C c1(c2);           | c1初始化为c2的拷贝，c1和c2必须是相同类型的容器，
    C c1 = c2;          | 且保存的是相同的元素类型；对于array，两者还必须大小相同
    ————————————————————————————————————————————————————————————————————————————————————————————————————————————
    C c{a, b, c...};    | c初始化为初始化列表中元素的拷贝，列表中元素的类型必须与c的元素类型相容，
    C c = {a, b, c...}; | 对于array类型，列表中元素数目必须等于或小于array的大小，任何遗漏的元素都进行值初始化
    ————————————————————————————————————————————————————————————————————————————————————————————————————————————
    C c(b, e);          | c初始化为迭代器b和e指定范围中的元素的拷贝，范围中元素的类型必须与c的元素类型相容（array不适用）
    ————————————————————————————————————————————————————————————————————————————————————————————————————————————
    只有顺序容器（不包括array）的构造函数才能接受大小参数
    C seq(n);           | seq包含n个元素，这些元素进行了值初始化，该构造函数是explicit的（string不适用）
    C seq(n, t);        | seq包含n个初始化为值t的元素
    ————————————————————————————————————————————————————————————————————————————————————————————————————————————
*/

/*
                                            容器赋值运算
    ————————————————————————————————————————————————————————————————————————————————————————————
    c1 = c2; | 将c1中的元素替换为c2中元素的拷贝，c1和c2必须具有相同的类型
    c = {a, b, c...} | 将c中元素替换为初始化列表中元素的拷贝（array不适用）
    swap(c1, c2); | 交换c1和c2中的元素，c1和c2必须具有相同的类型，swap通常比从c2向c1拷贝元素快得多
    ————————————————————————————————————————————————————————————————————————————————————————————
    assign操作不适用于关联容器和array
    seq.assign(b, e) | 将seq中的元素替换为迭代器b和e所表示的范围中的元素，迭代器b和e不能指向seq中的元素
    seq.assign(i1) | 将seq中的元素替换为初始化列表i1中的元素
    seq.assign(n, t) | 将seq中的元素替换为n个值为t的元素
    ————————————————————————————————————————————————————————————————————————————————————————————
    赋值相关运算会导致指向左边容器内部的迭代器、引用和指针失效
    而swap操作将容器内容交换不会导致指向容器的迭代器、引用和指针失效
    容器类型为array和string的情况除外
    ————————————————————————————————————————————————————————————————————————————————————————————
*/