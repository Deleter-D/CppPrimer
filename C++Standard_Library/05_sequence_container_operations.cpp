#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

class PersonInfo
{
public:
    PersonInfo()
    {
        name = "";
        phone = "";
    }
    PersonInfo(string name, string phone)
    {
        name = name;
        phone = phone;
    }

private:
    string name;
    string phone;
};

int main(int argc, char const *argv[])
{
    // list、forward_list和deque容器支持将元素插入到容器头部
    list<int> ilist;
    for (size_t ix = 0; ix != 4; ++ix)
        ilist.push_front(ix);

    // insert提供了更一般的功能
    vector<string> vwords = {"World"};
    list<string> words = {"World"};
    // vector不支持push_front，但可以通过插入到begin之前实现这个操作
    vwords.insert(vwords.begin(), "Hello");
    words.push_front("Hello");
    // 将元素插入到vector、deque和string中的任何位置都是合法的，但可能很耗时

    // 插入范围内的元素
    vector<string> svec;
    svec.insert(svec.end(), 10, "Anna");
    vector<string> v = {"squasi", "simba", "frollo", "scar"};
    // 将v的最后两个元素添加到svec的开始位置
    svec.insert(svec.begin(), v.end() - 2, v.end());

    // 使用insert的返回值
    list<string> slist;
    auto iter = slist.begin();
    string word;
    while (cin >> word)
        iter = slist.insert(iter, word); // 等价于调用push_front

    // 使用emplace操作，构造元素而不是拷贝元素
    list<PersonInfo> people;
    // emplace使用PersonInfo的构造函数
    people.emplace_back("Anna", "133xxxx");
    // people.push_back("Anna", "133xxxx"); // 错误：push_back不构造元素
    people.push_back(PersonInfo("Anna", "133xxxx")); // 正确
    people.emplace_back();                           // 正确：使用PersonInfo的默认构造函数

    // 访问元素
    list<int> ilist2 = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    if (!ilist2.empty())
    {
        // val1和val2是ilist2中第一个元素值的拷贝
        auto val1 = *ilist2.begin(), val2 = ilist2.front();
        // val3和val4是ilist2中最后一个元素值的拷贝
        auto val3 = *(--ilist2.end());
        auto val4 = ilist2.back();
    }

    // 访问成员函数返回的是引用
    if (!ilist2.empty())
    {
        ilist2.front() = 42;
        // 若想取到元素的引用，需要显式的加上&
        auto &v = ilist2.back();
        v = 1024;
        // 否则返回的是值的拷贝，并不会改变ilist2中的值
        auto v2 = ilist2.back();
        v2 = 0;
    }

    // 删除容器元素
    ilist2.pop_front();
    auto it = ilist2.begin();
    while (it != ilist2.end())
        if (*it % 2)
            it = ilist2.erase(it);
        else
            ++it;

    // 改变容器大小
    list<int> ilist3(10, 42); // 10个int，每个都是42
    ilist3.resize(15);        // 将5个值为0的意思添加到ilist3的末尾
    ilist3.resize(25, 1);    // 将10个值为1的元素添加到ilist3的末尾
    ilist3.resize(5);         // 从ilist3末尾删除20个元素
    return 0;
}

/*
                                向顺序容器添加元素的操作，一下操作array均不支持
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————————
    forward_list有自己版本的insert和emplace
    forward_list不支持push_back和emplace_back
    vector和string不支持push_front和emplace_front
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————————
    c.push_back(t)        | 在c的尾部创建一个值为t或由args创建的元素，返回void
    c.emplace_back(args)  |
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————————
    c.push_front(t)       | 在c的头部创建一个值为t或由args创建的元素，返回void
    c.emplace_front(args) |
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————————
    c.insert(p, t)        | 在迭代器p指向的元素之前创建一个值为t或由args创建的元素，返回指向新添加元素的迭代器
    c.emplace(p, args)    |
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————————
    c.inster(p, n, t)     | 在迭代器p指向的元素之前插入n个值为t的元素，返回指向新添加的第一个元素的迭代器，若n为0，则返回p
    c.insert(p, b, e)     | 将迭代器b和e指定范围内的元素插入到迭代器p指向的元素之前，b和e不能指向c中的元素，
                          |     返回指向新添加的第一个元素的迭代器，若范围为空，则返回p
    c.insert(p, il)       | il是一个花括号包围的元素值列表，将这些给定值插入到迭代器p指向的元素之前，返回指向新添加的第一个
                          |     元素的迭代器，若列表为空，则返回p
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————————
    向一个vector、string或deque插入元素会使所有指向容器的迭代器、指针和引用失效
*/

/*
                                    顺序容器中访问元素的操作
    ————————————————————————————————————————————————————————————————————————————————————
    at和下标操作只适用于string、vector、deque和array
    back不适用于forward_list
    ————————————————————————————————————————————————————————————————————————————————————
    c.back()  | 返回c中尾元素的引用，若c为空，函数行为未定义
    c.front() | 返回c中首元素的引用，若c为空，函数行为未定义
    c[n]      | 返回c中下标为n的元素的引用，n是一个无符号整数，若n>=c.size()，则函数行为未定义
    c.at(n)   | 返回下标为n的元素的引用，如果下标越界，则抛出out_of_range异常
    ————————————————————————————————————————————————————————————————————————————————————
*/

/*
                                        顺序容器的删除操作
    ———————————————————————————————————————————————————————————————————————————————————————————
    forward_list有特殊版本的erase
    forward_list不支持pop_back
    vector和string不支持pop_front
    ———————————————————————————————————————————————————————————————————————————————————————————
    c.pop_back()  | 删除c中尾元素，若c为空，则函数行为未定义，函数返回void
    c.pop_front() | 删除c中首元素，若c为空，则函数行为未定义，函数返回void
    c.erase(p)    | 删除迭代器p所指的元素，返回一个指向被删元素之后元素的迭代器，
                  | 若p指向尾元素，则返回尾后迭代器（off-the-end），若p是尾后迭代器，则函数行为未定义
    c.erase(b, e) | 删除迭代器b和e所指定范围内的元素，返回一个指向最后一个被删除元素之后的元素的迭代器
                  | 若e本身就是尾后迭代器，则函数也返回尾后迭代器
    c.clear()     | 删除c中所有元素，返回void
    ———————————————————————————————————————————————————————————————————————————————————————————
    删除deque中除首尾元素之外的任何元素都会使得迭代器、引用和指针失效
    指向vector或string中删除点之后位置的迭代器、引用和指针都会失效
    ———————————————————————————————————————————————————————————————————————————————————————————
*/

/*
                                    forward_list中插入或删除元素的操作
    ————————————————————————————————————————————————————————————————————————————————————————————————
    lst.before_begin()        | 返回指向链表首元素之前不存在的元素的迭代器，此迭代器不能解引用
    lst.cbefore_begin()       | 返回一个const_iterator
    ————————————————————————————————————————————————————————————————————————————————————————————————
    lst.insert_after(p, t)    | 在迭代器p之后的位置插入元素，t是一个对象
    lst.insert_after(p, n, t) | n是数量
    lst.insert_after(p, b, e) | b和e是表示范围的一对迭代器，b和e不能指向lst内
    lst.insert_after(p, il)   | il是一个花括号列表，返回一个指向最后一个插入元素的迭代器，
                              | 如果范围为空，则返回p，若p为尾后迭代器，则函数行为未定义
    ————————————————————————————————————————————————————————————————————————————————————————————————
    emplace_after(p, args)    | 使用args在p指定的位置之后创建一个元素，返回一个指向该新元素的迭代器
                              | 若p为尾后迭代器，则函数行为未定义
    ————————————————————————————————————————————————————————————————————————————————————————————————
    lst.erase_after(p)        | 删除p指向的位置之后的元素，返回一个指向被删除元素之后元素的迭代器，
                              | 若不存在这样的元素，则返回尾后迭代器，若p指向lst的尾元素或是一个尾后迭代器
                              | 则函数行为未定义
    lst.erase_after(b, e)     | 删除从b之后直到e（不包括e）之间的元素
    ————————————————————————————————————————————————————————————————————————————————————————————————
*/

/*
                            顺序容器大小操作
    ———————————————————————————————————————————————————————————————————
    resize不适用于array
    ———————————————————————————————————————————————————————————————————
    c.resize(n)    | 调整c的大小为n个元素，若n<c.size()，则多出的元素被丢弃
                   | 若必须添加新元素，对新元素进行值初始化
    c.resize(n, t) | 调整c的大小为n个元素，任何新添加的元素都初始化为值t
    ———————————————————————————————————————————————————————————————————
    如果resize缩小容器，则指向别删除元素的迭代器、引用和指针都会失效
    对vector、string和deque进行resize可能导致所有迭代器、引用和指针都会失效
    ———————————————————————————————————————————————————————————————————
*/