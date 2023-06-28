using namespace std;
#include <iostream>
#include "28_Aggregate_class.h"
#include "28_Literal_class.h"

int main()
{
    // 聚合类
    Aggregate_class data1 = {0, "Anna"}; // 可以使用初始值列表

    // Aggregate_class data2 = {"Anna", 0};// 错误：不能使用“Anna”初始化ival，也不能用0初始化s

    // 副作用：添加或删除一个成员后，所有的初始化语句都需要更新

    // 字面值常量类
    constexpr Literal_class io_sub(false, true, false); // 调试IO
    if (io_sub.any())
        cerr << "print appropriate error messages." << endl;
    constexpr Literal_class prod(false); // 无调试
    if (prod.any())
        cerr << "print an error message" << endl;
}