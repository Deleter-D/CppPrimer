using namespace std;
#include <iostream>
#include <string>
#include <iterator>
#include <cstddef>

// 数组证明形式为 T a[d];
// T为元素类型、a为数组名称、d为元素个数(d必须是常量表达式)
// 要注意的是，const只限制只读，并不要求编译时就确定
// 但只有编译时const才可以表示数组大小
unsigned cnt = 42;
constexpr unsigned sz = 42;
constexpr unsigned get_size() { return 42; }
int arr[10];
int *parr[sz];
// string bad[cnt]; // cnt并非常量表达式，故错误
string strs[get_size()]; // 只有当get_size()是constexpr时正确

// 不存在引用数组
// 可以使用列表初始化，但必须指定数组类型，不可使用auto
const unsigned sz2 = 3;
int arr1[sz2] = {0, 1, 2};
int arr2[] = {0, 1, 2};         // 自动推断元素个数
int arr3[5] = {0, 1, 2};        // 等价于arr3[] = {0, 1, 2, 0, 0};
string arr4[3] = {"hi", "bye"}; // 等价于arr4 = {"hi", "bye", ""};

// 字符数组有特殊性，字符串字面值的结尾处还有一个空字符
char ca1[] = {'C', '+', '+'};       // 没有空字符，大小为3
char ca2[] = {'C', '+', '+', '\0'}; // 含有显式空字符，大小为4
// 这将导致没有空间存放空字符，故错误
// const char ca3[3] = "C++";
char ca4[] = "C++"; // 含有空字符，大小为4

int main()
{
    // 不能将数组的内容拷贝给其他数组作为其初始值，也不能用数组为其他数组赋值
    int a[] = {0, 1, 2};
    // int a2[] = a; // 初始化时拷贝错误
    // a2 = a;       // 赋值错误

    // 复杂数组的声明
    int *ptrs[10]; // ptrs是含有10个整型指针的数组
    // int &refs[10]; // 不存在引用数组，故错误
    int(*Parray)[10] = &arr; // Parray是一个指向含有10个整数的数组的指针
    int(&Rarray)[10] = arr;  // Rarray是一个指向含有10个整数的数组的引用
    int *(&arry)[10] = ptrs; // arry是数组的引用，该数组包含10个整型指针

    // 使用数组的时候，编译器一般会把它转换成指针
    string nums[] = {"one", "two", "three"};
    string *sp = &nums[0]; // p指向nums的第一个元素
    string *sp2 = nums;    // 等价于p2 = &nums[0]

    int iarr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iarr2(iarr); // auto的推演结果是int*，iarr2指向iarr的第一个元素，等价于iarr2(&iarr[0]);

    // 使用decltype时，上述转换不会发生，即不会将iarr判断为指针
    decltype(iarr) iarr3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // iarr3是整型数组

    // 指针也是迭代器
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = arr;      // p指向arr的第一个元素，即arr[0]
    ++p;               // p指向arr[1]
    int *e = &arr[10]; // e指向arr尾元素的下一个位置
    for (int *b = arr; b != e; ++b)
    {
        cout << *b << endl;
    }

    // 上述代码以计算的方式得到尾后指针，这种做法极易出错
    // 可以使用定义在iterator头文件中的begin和end函数
    int *first = begin(arr);
    int *last = end(arr);

    while (first != last)
    {
        cout << *first << endl;
        ++first;
    }

    // 指针运算
    constexpr size_t sz = 5; // size_t类型包含在头文件cstddef中，本名为unsigned long long
    int i_arr[sz] = {0, 2, 4, 6, 8};
    int *ip = i_arr;       // 等价于int *ip = &arr[0];
    int *ip2 = ip + 4;     // ip2指向arr的尾元素arr[4]
    int *ip3 = i_arr + sz; // ip3指向arr尾元素的下一个位置，不要解引用
    int *ip4 = i_arr + 10; // 指针越界，语法上允许，但越界访问很危险

    auto n = end(i_arr) - begin(i_arr); // n为5，即arr的元素个数
    int *be = begin(i_arr), *en = end(i_arr);
    while (be < en)
    {
        cout << *be << endl;
        ++be;
    }

    // 解引用和指针运算交互
    int num = *(i_arr + 4); // num为8
    num = *i_arr + 4;       // num为0 + 4

    // 下标和指针
    int ii = i_arr[2]; // ii为4
    int *ptr = i_arr;
    ii = *(ptr + 2); // 等价于ii = i_arr[2];

    int *ptr2 = &i_arr[2]; // ptr2指向i_arr的第三个元素
    int j = ptr2[1];       // j为6
    int k = ptr2[-2];      // k为0，但string、vector的下标不可为负
}
