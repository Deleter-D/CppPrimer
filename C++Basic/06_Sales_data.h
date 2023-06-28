#ifndef SALES_DATA_H
#define SALES_DATA_H
// 头文件保护，防止在别的文件引用时重复定义，一般头文件中都会存在

#include <string>
// 类定义可使用struct或class两个关键字
// struct是public的，class是private的
struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0; // C++11开始可以在定义中初始化
    double revenue = 0.0;
};

#endif