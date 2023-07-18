#include <string>
using namespace std;

// 前面定义的，行为像值的类
class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);

  public:
    HasPtr(const string &s = string()) : ps(new string(s)), i(0)
    {
    }
    HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i)
    {
    }
    HasPtr &operator=(HasPtr);
    ~HasPtr()
    {
        delete ps;
    }

  private:
    string *ps;
    int i;
};

/*
HasPtr &HasPtr::operator=(const HasPtr &rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}
*/

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps); // 交换指针，而不是string数据
    swap(lhs.i, rhs.i);   // 交换int成员
}

// 利用swap重新实现赋值运算符重载
// 此处的rhs是值传递的，意味着HasPtr的拷贝构造函数将右侧运算对象中的string拷贝到rhs
HasPtr &HasPtr::operator=(HasPtr rhs)
{
    // 交换左侧运算对象和局部变量rhs的内容
    swap(*this, rhs); // rhs现在指向本对象曾经使用的内存
    return *this;     // rhs被销毁，从而delete了rhs中的指针
}

int main(int argc, char const *argv[])
{
    // 使用行为像值的对象进行交换操作较为麻烦
    // 需要定义中间变量，其中包含较多的隐式的构造与析构调用
    HasPtr v1, v2;
    HasPtr temp = v1;
    v1 = v2;
    v2 = temp;

    // 可以定义swap操作来实现交换
    return 0;
}