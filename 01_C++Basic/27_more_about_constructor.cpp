using namespace std;
#include <iostream>
#include <string>
#include "25_Sales_data_3.h"

int main()
{
    // 隐式类类型转换
    // 若构造函数支持一个实参的调用，那么也就定义了从参数类型向类类型隐式转换的规则
    Sales_data item;
    string null_book = "9-999-99999-9";
    // 构造一个临时的Sales_data对象
    // 该对象的units_sold和revenue为0，bookNo为null_book即"9-999-99999-9"
    // 只允许一步隐式类类型转换
    item.combine(null_book);

    // 错误：需要两次隐式类类型转换
    // 先把"9-999-99999-9"转换为string对象，再把该string对象转换成Sales_data
    // item.combine("9-999-99999-9");

    // 正确：显式地转换成string，隐式地转换成Sales_data
    item.combine(string("9-999-99999-9"));

    // 正确：隐式地转换成string，显式地转换成Sales_data
    item.combine(Sales_data("9-999-99999-9"));

    // 这种隐式转换可以通过在构造函数前加explicit关键字来抑制
    // 且explicit关键字只允许出现在类内的构造函数声明处
    // 不过即使使用explicit抑制了隐式转换，仍能通过static_cast强制进行隐式转换
    // 如：item.combine(static_cast<Sales_data>(null_book));
}
