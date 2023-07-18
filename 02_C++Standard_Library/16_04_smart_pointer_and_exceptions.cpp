#include <iostream>
#include <memory>
using namespace std;

// 若使用智能指针，即使程序块结束过早，也能正确释放内存
void f()
{
    shared_ptr<int> sp(new int(42));
    // 这段代码抛出一个异常，且未在f中被捕获
} // 在函数结束时shared_ptr会自动释放内存

// 直接管理内存则无法做到
void f2()
{
    int *pi = new int(42);
    // 这段代码抛出一个异常，且未在f中被捕获
    delete pi;
}

// 使用类似的技术管理不具有良好定义析构函数的类
struct destination; // 表示链接目标
struct connection   // 使用链接所需的信息
{
};
connection connect(destination *){}; // 打开链接
void disconnect(connection){};       // 关闭链接
void func(destination &d)
{
    // 获得链接
    connection c = connect(&d);
    // 使用链接
    // 若退出func之前没有调用disconnect，就无法关闭c了
}
// 定义一个操作来代替delete
void end_connection(connection *p)
{
    disconnect(*p);
}

void func2(destination &d)
{
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
    // 这样即使不调用disconnect，在作用域结束后，链接会被自动释放
}

int main(int argc, char const *argv[])
{

    return 0;
}