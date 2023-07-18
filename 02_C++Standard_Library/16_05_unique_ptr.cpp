#include <iostream>
#include <memory>
#include <string>
using namespace std;

// unique_ptr：拥有所指向的对象

unique_ptr<int> clone(int p);
unique_ptr<int> clone2(int p);

int main(int argc, char const *argv[])
{
    unique_ptr<double> p1;
    unique_ptr<int> p2(new int(42));
    unique_ptr<string> ps1(new string("HelloWorld!"));
    // unique_ptr<string> ps2(ps1); // 错误：unique_ptr不支持拷贝
    unique_ptr<string> ps3;
    // ps3 = ps2; // 错误：unique_ptr不支持赋值

    // 虽然不支持拷贝或赋值
    // 但可以通过release或reset将指针的所有权从一个(非const)对象转移给另一个
    unique_ptr<string> ups1(new string("HelloWorld!"));
    unique_ptr<string> ups2(ups1.release()); // 将ups1置空
    unique_ptr<string> ups3(new string("C++Primer"));
    ups2.reset(ups3.release()); // 将所有权从ups3转移给ups2
    // ups2.release();          // 会导致内存泄露
    auto p = ups2.release(); // 正确，但要记得delete p
    delete p;

    // 不能拷贝的例外：可以拷贝或赋值一个将要被销毁的unique_ptr
    unique_ptr<int> upi1 = clone(42);
    unique_ptr<int> upi2 = clone2(42);

    return 0;
}

unique_ptr<int> clone(int p)
{
    // 正确：从int*创建一个unique_ptr<int>
    return unique_ptr<int>(new int(p)); // 返回后该临时对象会被销毁，可以让其他智能指针接管
}

unique_ptr<int> clone2(int p)
{
    unique_ptr<int> ret(new int(p));
    return ret; // 正确：返回的是即将销毁的局部对象
}

// 向unique_ptr传递删除器
struct destination; // 表示链接目标
struct connection   // 使用链接所需的信息
{
};
connection connect(destination *){}; // 打开链接
void disconnect(connection){};       // 关闭链接
void end_connection(connection *p)
{
    disconnect(*p);
}
void func(destination &d)
{
    // 获得链接
    connection c = connect(&d);
    // 传入删除器的类型即可调用对象
    unique_ptr<connection, decltype(end_connection) *> p(&c, end_connection);
}

/*
                                       unique_ptr的操作
    —————————————————————————————————————————————————————————————————————————————————————
    unique_ptr<T> u1      | 空unique_ptr，可以指向类型为T的对象，u1会使用delete来释放它的指针
    unique_ptr<T, D> u2   | u2会使用一个类型为D的可调用对象来释放它的指针
    unique_ptr<T, D> u(d) | 空unique_ptr，指向类型为T的对象，用类型为D的对象d代替delete
    u = nullptr           | 释放u指向的对象，将u置空
    u.release()           | u放弃对指针的控制器，返回指针，并将u置空
    u.reset()             | 释放u指向的对象
    u.reset(q)            | 若提供了内置指针q，则令u指向该对象
    u.reset(nullptr)      | 否则将u置空
    —————————————————————————————————————————————————————————————————————————————————————
*/