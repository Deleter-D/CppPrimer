#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    const char *cp = "Hello World!!!";
    char noNull[] = {'H', 'i'};
    string s1(cp); // 拷贝cp中的字符直到遇到空字符
    cout << "s1: " << s1 << endl;
    string s2(noNull, 2); // 从noNull拷贝两个字符
    cout << "s2: " << s2 << endl;
    string s3(noNull); // 未定义：noNull不是以空字符结束
    cout << "s3: " << s3 << endl;
    string s4(cp + 6, 5); // 从cp[6]开始拷贝5个字符
    cout << "s4: " << s4 << endl;
    string s5(s1, 6, 5); // 从s1[6]开始拷贝5个字符
    cout << "s5: " << s5 << endl;
    string s6(s1, 6); // 从s1[6]开始，直到s1末尾
    cout << "s6: " << s6 << endl;
    string s7(s1, 6, 20); // 只拷贝到s1末尾
    cout << "s7: " << s7 << endl;
    // string s8(s1, 16); // 抛出out_of_range异常
    // cout << "s8: " << s8 << endl;

    string s("hello world");
    string sub1 = s.substr(0, 5);
    cout << "sub1: " << sub1 << endl;
    string sub2 = s.substr(6);
    cout << "sub2: " << sub2 << endl;
    string sub3 = s.substr(6, 11);
    cout << "sub3: " << sub3 << endl;
    // string sub4 = s.substr(12); // 抛出out_of_range异常
    // cout << "sub4: " << sub4 << endl;

    return 0;
}

/*
                                      额外的构造函数
    —————————————————————————————————————————————————————————————————————————————————
    string s(cp, n)          | s是cp指向的数组中前n个字符的拷贝，该数组至少应该包含n个字符
    string s(s2, pos2)       | s是string s2从下标pos2开始的字符的拷贝
                             | 若pos2>s2.size()，构造函数行为未定义
    string s(s2, pos2, len2) | s是string s2从下标pos2开始len2个字符的拷贝
                             | 若pos2>s2.size()，构造函数的行为未定义
                             | 无论len2的值是多少，构造函数至多拷贝s2.size()-pos2个字符
    —————————————————————————————————————————————————————————————————————————————————
*/

/*
                            子字符串操作
    ———————————————————————————————————————————————————————————————
    s.substr(pos, n) | 返回一个string，包含s中从pos开始的n个字符的拷贝
                    | pos的默认值为0，n的默认值为s.size()-pos
    ———————————————————————————————————————————————————————————————
*/