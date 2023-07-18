using namespace std;
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iterator>

int main()
{
    // C风格字符串不是一种类型，而是为了表达和使用字符串而形成的一种约定俗成的写法
    // C风格字符串的处理函数定义在C语言头文件string.h中，C++中通过cstring引入
    char ca[] = {'C', '+', '+'};
    cout << strlen(ca) << endl; // ca没有以空字符串结束，故函数返回的结果是错误的

    // C++字符串直接比较即可
    string s1 = "A string example";
    string s2 = "A different string";
    if (s1 < s2)
    {
        // TODO
    }

    // C风格字符串需要调用函数来比较
    const char ca1[] = "A string example";
    const char ca2[] = "A different string";
    if (ca1 < ca2) // 试图比较两个无关的指针
    {
        // TODO
    }
    if (strcmp(ca1, ca2) < 0) // 和两个string对象比较的效果一样
    {
        // TODO
    }

    // 与旧代码的接口
    string s("Hello World");
    // char *str = s; // 不能用string对象直接初始化字符的指针
    // 需要用string库中的c_str()函数
    // 如果后续的操作改变了s的值，则c_str之前所返回的数组将失效
    // 若想执行完c_str()后想一直都能使用其返回的数组，最好将该数组重新拷贝一份
    const char *str = s.c_str();

    // 使用数组初始化vector对象
    int int_arr[] = {0, 1, 2, 3, 4, 5};
    // ivec有6个元素，分别是int_arr中对应元素的副本
    vector<int> ivec(begin(int_arr), end(int_arr));
    // sub_vec有3个元素，分别是int_arr[1]、int_arr[2]和int_arr[3]的副本
    vector<int> sub_vec(int_arr + 1, int_arr + 4);
}

/*
                cstring的操作
    ——————————————————————————————————————
    strlen(p)       |  返回字符串长度
    strcmp(p1, p2)  |  比较两个字符串
    strcat(p1, p2)  |  拼接两个字符串
    strcpy(p1, p2)  |  把p2的内容拷贝到p1中
    ——————————————————————————————————————
    作为参数的字符串必须以空字符串结束
*/