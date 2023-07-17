#include <iostream>
#include <memory>
using namespace std;

// shared_ptr和new结合使用

shared_ptr<int> clone(int p);
void process(shared_ptr<int> ptr)
{
    // 使用ptr
} // 离开作用域，ptr被销毁

int main(int argc, char const *argv[])
{
    shared_ptr<double> p1;           // 一个指向double的shared_ptr
    shared_ptr<int> p2(new int(42)); // 用普通指针初始化一个智能指针

    // 智能指针的构造函数是explict的，只能显式调用
    // shared_ptr<int> p3 = new int(1024); // 错误：这样将隐式调用智能指针的构造函数，但构造函数是explict
    shared_ptr<int> p4(new int(1024)); // 正确：显式调用构造函数
    auto p5 = clone(42);
    // 默认情况下，用来初始化智能指针的普通指针必须指向动态内存
    // 否则必须提供操作来代替delete

    // 内置指针和智能指针混用的风险
    shared_ptr<int> pi(new int(42)); // 引用计数为1
    process(pi);                     // 拷贝p会增加它的引用计数，在process中的引用计数值为2
    int i = *pi;                     // 正确：引用计数值为1
    // 用内置指针显式构造一个shared_ptr可能会导致错误
    int *x(new int(1024));
    // process(x);               // 错误：无法将int*转换为shared_ptr<int>
    process(shared_ptr<int>(x)); // 合法的：但内存会被释放
    int j = *x;                  // 未定义：x是一个悬空指针

    // get：向不能使用智能指针的代码传递一个内置指针
    shared_ptr<int> p(new int(42));
    int *q = p.get(); // 正确：但使用q时要注意，不要让它管理的指针被释放
    // 新作用域
    {
        // 未定义：两个独立的shared_ptr指向相同的内存
        shared_ptr<int> p2(q);
    }             // 离开作用域p2被销毁，它所指向的内存被释放
    int foo = *p; // 未定义：p指向的内存已经被释放

    // 永远不要使用get初始化另一个智能指针或为另一个智能指针赋值
    // reset：更新引用计数，若需要的话，会释放p指向的对象
    // p = new int(1024);   // 错误：不允许将一个指针赋予shared_ptr
    p.reset(new int(1024)); // 正确：p指向一个新对象
    if (!p.unique())
        p.reset(new int(*p)); // 我们不是待使用对象的唯一用户，分配新的拷贝
    *p += 1;                  // 现在我们称为了该拷贝的唯一用户，可以改变对象的值
    return 0;
}

shared_ptr<int> clone(int p)
{
    // 错误：隐式转换为shared_ptr<int>
    // return new int(p);
    // 正确：显式地用int*创建shared_ptr<int>
    return shared_ptr<int>(new int(p));
}

/*
                                    定义和改变shared_ptr的方法
    —————————————————————————————————————————————————————————————————————————————————————————
    shared_ptr<T> p(q)     | p管理内置指针q所指向的对象，q必须指向new分配的内存，且能够转换为T*类型
    shared_ptr<T> p(u)     | p从unique_ptr u那里接管了对象的所有权，并将u置空
    shared_ptr<T> p(q, d)  | p接管了内置指针q所指向的对象的所有权，q必须能转换为T*类型
                           | p将使用可调用对象d来代替delete
    shared_ptr<T> p(p2, d) | p是shared_ptr p2的拷贝，唯一的区别是p将用可调用对象d来代替delete
    p.reset()              | 若p是唯一指向其对象的shared_ptr，reset会释放此对象
    p.reset(q)             | 若传递了可选的参数内置指针q，会令p指向q，否则会将p置为空
    p.reset(q, d)          | 若还传递了参数d，将会调用d而不是delete来释放
    —————————————————————————————————————————————————————————————————————————————————————————
*/