using namespace std;
#include <iostream>
#include <string>
#include <iterator>

// 局部对象
// 自动对象：生命周期从变量声明开始，到函数快末尾结束
// 局部静态对象：生命周期从变量声明开始，直到程序结束才销毁
size_t count_calls()
{
    static size_t ctr = 0; // 局部静态对象
    return ++ctr;
}

// 参数传递
// 传值参数
void reset(int *ip) // 指针形参
{
    *ip = 0; // 改变了指针ip所指对象的值
    ip = 0;  // 只改变了ip的局部拷贝，实参未被改变
}

// 传引用参数
void reset2(int &i)
{
    i = 0; // 改变了i所引用对象的值
}

// 使用引用避免拷贝
// 当实参较大时，可以使用引用避免产生副本，且若无需改变形参的值，最好将其声明为常量引用
bool isShroter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

// 使用引用形参返回额外信息
// 函数本身返回s中c第一次出现的位置
// 引用参数occurs统计c出现的总次数
string::size_type find_char(const string &s, char c, string::size_type &occurs)
{
    auto ret = s.size(); // c第一次出现的位置
    occurs = 0;
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if (s[i] == c)
        {
            if (ret == s.size())
                ret = i; // 记录第一次出现的位置
            ++occurs;    // 每出现一次加1
        }
    }
    return ret;
}

// const形参和实参
// 形参的顶层const会被忽略
void func(const int i) // func能够读取i，但不能向i写值
{
    // TODO
}
// void func(int i) {} // 不允许这种重载，编译器无法判断实参是否是const

// 指针或引用形参与const
void reset3(int *ip)
{
    *ip = 0;
    ip = 0;
}
// 重载reset3
void reset3(int &ip)
{
    ip = 0;
}

// 数组形参
// 以数组作为形参的函数必须确保使用数组时不会越界
void print(const int *);
void print(const int[]);
void print(const int[10]); // 这里的10只是一个期望
// 确保不越界的方式
// 1、利用数组本身的介绍符
void print(const char *cp)
{
    if (cp)                // 若cp不是一个空指针
        while (*cp)        // 取出来的不是空字符
            cout << *cp++; // 输出当前字符，并将指针移动到下一位置
    cout << endl;
}
// 2、使用标准库规范
void print(const int *beg, const int *end)
{
    // 输出beg到end之间(不含end)的所有元素
    while (beg != end)
        cout << *beg++ << " ";
    cout << endl;
}
// 3、显式传递一个表示数组大小的形参
void print(const int ia[], size_t size)
{
    for (size_t i = 0; i != size; ++i)
        cout << ia[i] << " ";
    cout << endl;
}

// C++允许将变量定义成数组的引用
void print_arr(int (&arr)[10]) // 此处的10是类型的一部分，实参必须是大小为10的int数组
{
    for (auto elem : arr)
        cout << elem << " ";
    cout << endl;
}

// 传递多维数组
// 将matrix声明成指向含有10个整数的数组的指针
void print_matrix(int (*matrix)[10], int rowSize) // 行数通过rowSize传递，列数必须是10
{
    for (size_t i = 0; i != rowSize; ++i)
    {
        for (auto elem : matrix[i])
            cout << elem << " ";
        cout << endl;
    }
}
// 这种声明方式等价于上述方式，将matrix声明成指向含有10个整数的数组的指针
void print_matrix2(int matrix[][10], int rowSize) // 行数通过rowSize传递，列数必须是10
{
    for (size_t i = 0; i != rowSize; ++i)
    {
        for (auto elem : matrix[i])
            cout << elem << " ";
        cout << endl;
    }
}

// 含有可变参数的函数
// 如果所有的实参类型相同，可以传递一个名为initializer_list的标准库类型
/*                              initializer_lsit提供的操作
——————————————————————————————————————————————————————————————————————————————————————————————
initializer_list<T> lst;             |  默认初始化，T类型元素的空列表
initializer_list<T> lst{a,b,c,...};  |  list的元素数量和初始值一样多；
                                     |  lst的元素是对应初始值的副本；
                                     |  列表中的元素是const
——————————————————————————————————————————————————————————————————————————————————————————————
list2(list)                          |  拷贝或赋值一个initializer_list对象不会拷贝列表中的元素；
lst2=list                            |  拷贝后，原始列表和副本共享元素
——————————————————————————————————————————————————————————————————————————————————————————————
lst.size()                           |  列表中的元素数量
lst.begin()                          |  返回指向lst中首元素的指针
lst.end()                            |  返回指向lst中尾元素下一位置的指针
——————————————————————————————————————————————————————————————————————————————————————————————
*/
initializer_list<string> ls;
initializer_list<int> li;

void error_msg(initializer_list<string> ls)
{
    for (auto beg = ls.begin(); beg != ls.end(); ++beg)
        cout << *beg;
    cout << endl;
}

int main()
{
    // count_calls测试
    for (size_t i = 0; i != 10; ++i)
        cout << count_calls() << endl;

    // reset测试
    int i = 42;
    reset(&i); // 改变i的值，而非i的地址
    cout << "i = " << i << endl;

    // reset2测试
    int j = 42;
    reset2(j);
    cout << "j = " << j << endl;

    // isShroter测试
    string str1 = "hello world!";
    string str2 = "hello!";
    cout << (isShroter(str1, str2) ? "true" : "false") << endl;

    // find_char测试
    string str3 = "hannah";
    char c = 'h';
    string::size_type occurs;
    cout << "The first character " << c << " is located in " << find_char(str3, c, occurs) << endl;
    cout << "And it occurs a total of " << occurs << " times in the string." << endl;

    // reset3测试
    int k = 0;
    const int ck = k;
    string::size_type ctr = 0;

    reset3(&k); // 调用形参类型是int*的reset3函数
    // reset3(&ck); // 错误：不能用指向const int对象的指针初始化int*
    reset3(k); //调用形参类型是int&的reset3函数
    // reset3(ck);  // 错误：不能把普通引用绑定到const对象ck上
    // reset3(42);  // 错误：不能把普通引用绑定到字面值上
    // reset3(ctr); //错误：类型不匹配，ctr是无符号类型

    // print测试
    int ia[2] = {0, 1};
    // 避免越界方式2
    print(begin(ia), end(ia));
    // 避免越界方式3
    print(ia, end(ia) - begin(ia));

    // print_arr测试
    int l = 0;
    int ia2[2] = {0, 1};
    int ia3[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // print_arr(&l);  // 错误：实参不是含有10个整数的数组
    // print_arr(ia2); // 错误：实参不是含有10个整数的数组
    print_arr(ia3);

    // print_matrix测试
    int matrix[5][10] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
        {30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
        {40, 41, 42, 43, 44, 45, 46, 47, 48, 49}};
    cout << "The matrix is:" << endl;
    print_matrix(matrix, 5);
    print_matrix2(matrix, 5);

    // error_msg测试
    string excepted = "test passed";
    string actual = "test faild";
    if (excepted != actual)
        error_msg({"functionX\n", "excepted is ", excepted, "\nactual is ", actual});
    else
        error_msg({"functionX", " is okey"});

    return 0;
}

// main：处理命令行选项
// argc表示参数个数
// argv是存放char*类型的数组，容量由argc决定
// int main(int argc, char *argv[]) {}
// int main(int argc, char **argv) {}

// 若运行prog -d -o ofile data0
// argc = 5或空字符串
// argv[0] = "prog"
// argv[1] = "-d"
// ...
// argv[4] = "data0"
// argv[5] = 0 最后一个指针之后的元素值保证为0