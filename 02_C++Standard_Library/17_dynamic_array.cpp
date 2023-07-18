#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// 动态数组并不是数组类型
// 分配动态数组会得到一个元素类型的指针

int main(int argc, char const *argv[])
{
    // 方括号中的数字必须是整数，但不必是常量
    // 可以通过其他手段获取，如调用get_size()等自定义业务函数
    int *pia = new int[5];

    typedef int arrT[42]; // arrT表示42个int的数组类型
    int *p = new arrT;    // 分配一个42个int的数组，p指向第一个int，编译器执行int *p = new int[42];

    // 初始化动态分配对象的数组
    int *pia2 = new int[10];         // 10个默认初始化的int，值未定义
    int *pia3 = new int[10]();       // 10个值初始化为0的int
    string *psa = new string[10];    // 10个默认初始化为空的string
    string *psa2 = new string[10](); // 10个值初始化为空string

    // 10个int用列表初始化
    int *pi4 = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 前4个string用列表初始化，剩余string使用值初始化
    string *psa3 = new string[10]{"a", "an", "the", string(3, 'x')};

    // 动态分配一个空数组是合法的
    size_t n = 0;
    int *pia4 = new int[n]; // pia4并不是空指针，而是类似于尾后指针

    // 理论上不允许定义长度为0的数组，但使用g++时可以编译通过
    // 在C语言中找到了类似的概念，0长度的数组又被称之为可变数组或柔性数组
    // 应该是编译器默认将0长度数组认为是动态数组，故而能够编译通过
    char carr[0];
    char *cpa = new char[0];

    // 释放动态数组
    int *q = new int;
    int *qa = new int[5];
    delete q;    // q必须指向一个动态分配的对象或为空
    delete[] qa; // qa必须指向一个动态分配的数组或为空，数组中的元素按逆序销毁

    // 智能指针和动态数组
    // 标准库提供了一个可以管理new分配的数组的unique_ptr版本
    // unique_ptr指向一个数组时，不能使用.或->运算符，因为指向的数组并不是对象
    unique_ptr<int[]> up(new int[5]); // up指向一个包含10个未初始化int的数组
    up.release();                     // 自动调用delete[]销毁其管理的指针

    // shared_ptr不直接支持管理动态数组
    // 若希望使用shared_ptr管理动态数组，必须自定义删除器
    shared_ptr<int> sip(new int[5], [](int *p) { delete[] p; });
    // shared_ptr未定义下标运算符，并且不支持指针的算术运算
    for (size_t i = 0; i < 5; i++)
        *(sip.get() + i) = i; // 必须使用get来获取内置指针后进行操作

    sip.reset(); // 自动调用使用lambda表达式自定义的删除器

    // allocator类：将内存分配和对象构造分离
    // 分配大块内存，但只有真正需要时才执行对象创建操作
    // 内存分配和对象构造组合在一起可能导致不必要的浪费
    size_t m = 42;
    string *const scpa = new string[m]; // 构造m个空string
    string s;
    string *sp = scpa; // sp指向scpa的第一个元素
    while (cin >> s && sp != scpa + m)
        // 赋予*sp一个新的值
        *sp++ = s;
    const size_t size = sp - scpa; // 记录读取的string个数
    delete[] scpa;

    // 上面的代码有三个问题
    // - 可能根本不需要m个string
    // - 每个对象都进行了两次赋值(默认初始化一次，输入时候一次)
    // - 没有默认构造函数的类就无法分配动态数组，必须分离内存分配和对象构造

    // allocator分配的内存是原始的、未构造的
    size_t num = 10;
    allocator<string> alloc;
    auto const ptr = alloc.allocate(num); // 分配num个未初始化的string
    auto qtr = ptr;                       // qtr指向最后构造的元素之后的位置
    alloc.construct(qtr++);               // *qtr为空string
    alloc.construct(qtr++, 10, 'c');      // *qtr为cccccccccc
    alloc.construct(qtr++, "hi");         // *qtr为hi

    cout << *ptr << endl; // 正确：使用string的<<运算符
    cout << *qtr << endl; // 灾难：qtr指向未构造的内存

    while (qtr != ptr)
        alloc.destroy(--qtr); // 释放已经构造的string

    alloc.deallocate(ptr, num);

    // 标准库为allocator类定义了两个伴随算法，可以在未初始化内存中创建对象
    vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 分配比ivec中元素所占空间大一倍的动态内存
    auto iarr = alloc.allocate(ivec.size() * 2);
    // 通过拷贝ivec中的元素来构造从iarr开始的元素
    // iarr_initialized将指向最后一个构造的元素之后的位置
    auto iarr_initialized = uninitialized_copy(ivec.begin(), ivec.end(), iarr);
    // 将剩余的元素初始化为42
    uninitialized_fill_n(iarr_initialized, ivec.size(), 42);
    return 0;
}

/*
                                指向数组的unique_ptr
    ———————————————————————————————————————————————————————————————————————————
    不支持成员访问运算符(.或->)，其他的操作不变
    ———————————————————————————————————————————————————————————————————————————
    unique_ptr<T[]> u    | 可以指向一个动态分配的数组，数组元素类型为T
    unique_ptr<T[]> u(p) | u指向内置指针p所指向的动态分配的数组，p必须能转换为类型T*
    u[i]                 | 返回u拥有的数组中位置i处的对象，u必须指向一个数组
    ———————————————————————————————————————————————————————————————————————————
*/

/*
                                           allocator类
    ————————————————————————————————————————————————————————————————————————————————————————
    allocator<T> a       | 定义了一个名为a的allocator对象，它可以为类型为T的对象分配内存
    ————————————————————————————————————————————————————————————————————————————————————————
    a.allocate(n)        | 分配一段原始的、未构造的内存，保存n个类型为T的对象
    ————————————————————————————————————————————————————————————————————————————————————————
    a.deallocate(p, n)   | 释放从T*指针p中地址开始的内存，这块内存保存了n个类型为T的对象
                         | p必须是一个先前由allocate返回的指针，且n必须是p创建时所要求的大小
                         | 在调用deallocate之前，用户必须对每个在这块内存中创建的对象调用destroy
    ————————————————————————————————————————————————————————————————————————————————————————
    a.construct(p, args) | p必须是一个类型为T*的指针，指向一块原始内存
                         | args被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象
    ————————————————————————————————————————————————————————————————————————————————————————
    a.destory(p)         | p为T*类型的指针，此算法对p指向的对象执行析构函数
    ————————————————————————————————————————————————————————————————————————————————————————
*/

/*
                                                allocator算法
    —————————————————————————————————————————————————————————————————————————————————————————————————
    这些函数在给定目的位置创建元素，而不是由系统分配内存给它们。
    —————————————————————————————————————————————————————————————————————————————————————————————————
    uninitialized_copy(b, e, b2)   | 从迭代器b和e指出的输入范围中拷贝元素到迭代器b2指定的未构造的原始内存中
                                   | b2指向的内存必须足够大，能容纳输入序列中元素的拷贝
    uninitialized_copy_n(b, n, b2) | 从迭代器b指向的元素开始，拷贝n个元素到b2开始的内存中
    —————————————————————————————————————————————————————————————————————————————————————————————————
    uninitialized_fill(b, e, t)    | 在迭代器b和e指定的原始内存范围中创建对象，对象的值均为t的拷贝
    uninitialized_fill_n(b, n, t)  | 从迭代器b指向的内存地址开始创建n个对象
                                   | b必须指向足够大的未构造的原始内存，能够容纳给定数量的对象
    —————————————————————————————————————————————————————————————————————————————————————————————————
*/