#include "16_01_StrBlob.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>
using namespace std;
/*
    栈对象：仅在其定义的程序块运行时才存在(有严格的生命周期，不会内存泄露)
    static对象：在使用之前分配，在程序结束时销毁(有严格的生命周期，不会内存泄露)
    堆对象：动态分配的对象，在程序运行过程中可以随时建立或删除的对象

    动态内存管理：
    new    | 在动态内存中为对象分配空间并返回一个指向该对象的指针
    delete | 接受一个动态对象的指针，销毁该对象并释放与之关联的内存

    新C++标准提供了两个智能指针来更安全的使用动态内存
    shared_ptr | 允许多个指针指向同一个对象
    unique_ptr | “独占”所有对象
    类似于常规指针，区别在于它负责自动释放所指向的对象
*/

int main(int argc, char const *argv[])
{
    shared_ptr<string> p1;
    shared_ptr<list<int>> p2;
    if (p1 && p1->empty())
        *p1 = "hi";

    // 最安全的分配和使用动态内存的方法是调用make_shared标准库函数
    shared_ptr<int> p3 = make_shared<int>(42);            // p3是指向值为42的int的shared_ptr
    shared_ptr<string> p4 = make_shared<string>(10, '9'); // p4指向值为"9999999999"的string
    shared_ptr<int> p5 = make_shared<int>();              // p5指向值初始化的int，即0
    auto p6 = make_shared<vector<string>>();              // p6指向动态分配的空vector<string>

    // 引用计数
    auto r = make_shared<int>(42); // r指向的int只有一个引用者
    auto q = make_shared<int>(43);
    r = q; // 令r指向另一个地址，递增q指向的对象的引用计数，递减r原来指向的对象的引用计数
    // 此时，r原来指向的对象以及没有引用者，会自动释放

    // 使用动态内存的原因
    // 允许多个对象共享相同的状态
    vector<string> v1;
    { // 新作用域
        vector<string> v2({"a", "an", "the"});
        v1 = v2;
    } // 离开作用域，v2被销毁，其中元素也被销毁
    // v1中有三个元素，是v2原来元素的拷贝
    for_each(v1.cbegin(), v1.cend(), [](const string &s) { cout << s << " "; });
    cout << endl;
    // 与容器不同，希望定义一个类，对象不用拷贝，而是直接共享相同的元素
    StrBlob b1;
    { // 新作用域
        StrBlob b2 = {"a", "an", "the"};
        // b1和b2共享相同的元素
        b1 = b2;
    } // b2被销毁了，但b2中的元素不能销毁
    // b1指向最初由b2创建的元素

    return 0;
}

// factory返回一个shared_ptr，指向一个动态分配的对象
shared_ptr<int> factory(int arg)
{
    return make_shared<int>(arg);
}

void use_factory(int arg)
{
    // 使用factory创建动态对象
    shared_ptr<int> p = factory(arg);
} // 离开此作用域，p指向的内存会自动释放

/*
                    shared_ptr和unique_ptr都支持的操作
    —————————————————————————————————————————————————————————————————
    shared_ptr<T> sp      | 空智能指针，可以指向类型为T的对象
    unique_ptr<T> up      |
    —————————————————————————————————————————————————————————————————
    p                     | 将p用作一个条件判断，若p指向一个对象则为true
    *p                    | 解引用p，获得它指向的对象
    p->mem                | 等价于(*p).mem
    p.get()               | 返回p中保存的指针，若智能指针释放了其对象
                          | 返回的指针所指向的对象也就消失了
    swap(p, q), p.swap(q) | 交换p和q中的指针
    —————————————————————————————————————————————————————————————————
*/

/*
                                        shared_ptr独有操作
    ———————————————————————————————————————————————————————————————————————————————————————————
    make_shared<T> (args) | 返回一个shared_ptr，指向一个动态分配的类型为T的对象，使用ags初始化此对象
    shared_ptr<T> p(q)    | p是shared_ptr q的拷贝，此操作会递增q中的计数器，q中的指针必须能转换为T*
    ———————————————————————————————————————————————————————————————————————————————————————————
    p = q                 | p和q都是shared_ptr，所保存的指针必须能相互转换
                          | 此操作会递减p的引用计数，递增q的引用计数
                          | 若p的引用计数变为0，则将其管理的原内存释放
    ———————————————————————————————————————————————————————————————————————————————————————————
    p.unique()            | 若p.use_count()为1，则返回true，否则返回false
    p.use_count()         | 返回与p共享对象的智能指针数量，可能很慢，主要用于调试
    ———————————————————————————————————————————————————————————————————————————————————————————
*/