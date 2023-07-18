using namespace std;
#include <iostream>

int main()

{
    // 严格来说C++没有多维数组，但允许在数组中存放数组
    int ia[3][4];
    int arr[10][20][30];

    // 多维数组的初始化
    // 允许使用花括号初始化多维数组
    int ia2[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}};
    int ia3[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // 效果同上
    int ia4[3][4] = {{0}, {4}, {8}};                        // 相当于{0,0,0,0,4,0,0,0,8,0,0,0};
    int ia5[3][4] = {0, 1, 2, 3};                           // 相当于{0,1,2,3,0,0,0,0,0,0,0,0};

    // 下标引用
    ia[2][3] = arr[0][0][0]; // 可以直接取值赋值
    int(&row)[4] = ia[1];    // 将数组引用row绑定到ia的第二个4元素数组上

    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia6[rowCnt][colCnt]; //使用常量表达式初始化
    for (size_t i = 0; i != rowCnt; ++i)
        for (size_t j = 0; j != colCnt; ++j)
            ia6[i][j] = i * colCnt + j;

    // 显式标注&使auto将row推演为数组的引用
    for (auto &row : ia6)
        for (auto &col : row)
            cout << col << ' ';
    cout << endl;

    // 如直接用auto进行推演
    // for (auto row : ia6)     // row此时会被推演为指针
    //     for (auto col : row) // 本行会报错，因为int *row没有合适的begin函数
    //         cout << col;

    // 若无需对数组内容进行修改，则col可以不使用引用
    for (auto &row : ia6) // row需要声明为引用，可以避免被推演为指针
        for (auto col : row)
            cout << col << ' ';
    cout << endl;

    // 指针和多维数组
    int ia7[3][4];
    int(*p)[4] = ia7; // p指向ia7的第一个4元素数组
    p = &ia7[2];      // p指向ia7的第三个4元素数组
    for (auto p = ia7; p != ia7 + 3; ++p)
        for (auto q = *p; q != *p + 4; ++q)
            cout << *q << ' ';
    cout << endl;
    // 也可以使用标准库的begin和end函数，更安全
    for (auto p = begin(ia7); p != end(ia7); ++p)
        for (auto q = begin(*p); q != end(*p); ++q)
            cout << *q << ' ';
    cout << endl;

    // 使用类型别名简化多维数组指针
    using int_array = int[4];
    for (int_array *p = begin(ia7); p != end(ia7); ++p)
        for (int *q = begin(*p); q != end(*p); ++q)
            cout << *q << ' ';
    cout << endl;
}
