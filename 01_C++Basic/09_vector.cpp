using namespace std;
#include <iostream>
#include <vector>

/*
                                初始化vector对象的方法
    ———————————————————————————————————————————————————————————————————————————————————
    vector<T> v1                 |  v1是一个空vector，它潜在的元素是T类型的，执行默认初始化
    vector<T> v2(v1)             |  v2中包含有v1所有元素的副本
    vector<T> v2 = v1            |  等价于v2(v1)，v2中包含有v1所有元素的副本
    vector<T> v3(n, val)         |  v3包含了n个重复的元素，每个元素的值都是val
    vector<T> v4(n)              |  v4包含了n个重复地执行了值初始化的对象
    vector<T> v5{a, b, c...}     |  v5包含了初始值个数的元素，每个元素被赋予相应的值
    vector<T> v5 = {a, b, c...}  |  等价于v5{a, b, c...}
    ———————————————————————————————————————————————————————————————————————————————————
*/

int main()
{
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : v)
        i *= i; // 求平方
    for (auto i : v)
        cout << i << " ";
    cout << endl;

    // 输入成绩并统计各成绩挡位的人数
    vector<unsigned> grades;        // 存储成绩
    vector<unsigned> scores(11, 0); // 存储各成绩挡位的人数0-9,10-19,...,90-99,100
    unsigned grade;
    while (cin >> grade)
    {
        if (grade <= 100)
            grades.push_back(grade);
        ++scores[grade / 10];
    }

    cout << "grades.size = " << grades.size() << endl;
    for (auto item : grades)
        cout << item << " ";
    cout << endl;

    cout << "scores.size = " << scores.size() << endl;
    for (auto item : scores)
        cout << item << " ";
    cout << endl;
    return 0;
}

/*
                                  vector支持的操作
    ——————————————————————————————————————————————————————————————————————————————
    v.empty()          |  若v不含任何元素返回true，否则返回false
    v.size()           |  返回v中元素的个数
    v.push_back(t)     |  向v的尾端添加一个值为t的元素
    v[n]               |  返回v中第n个位置上元素的引用
    v1 = v2            |  用v2中元素的拷贝替换v1中的元素
    v1 = {a, b, c...}  |  用列表中元素的拷贝替换v1中的元素
    v1 == v2           |  v1和v2相等当且仅当它们的元素数量相同且对应位置的元素值都相同
    v1 != v2           |
    <,<=,>,>=          |  以字典顺序进行比较
    ——————————————————————————————————————————————————————————————————————————————
*/