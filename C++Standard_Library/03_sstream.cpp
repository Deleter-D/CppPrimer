#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct PersonInfo
{
    string name;
    vector<string> phones;
};

int main(int argc, char const *argv[])
{
    // 字符串IO
    string line, word;         // 分别保存来自输入的一行和单词
    vector<PersonInfo> people; // 保存来自输入的所有信息

    cout << "input please:" << endl;
    while (getline(cin, line))
    {
        PersonInfo info;
        istringstream record(line); // 创建sstream对象，绑定输入的行
        record >> info.name;        // 读取姓名
        while (record >> word)      // 读取电话号码
        {
            info.phones.push_back(word); // 保存
        }
        people.push_back(info); // 将该记录追加到people末尾
    }

    cout << "input end" << endl;

    for (PersonInfo person : people)
    {
        cout << person.name << endl;
        for (string phone : person.phones)
        {
            cout << "numbers: " << phone << endl;
        }
    }

    system("pause");
    return 0;
}

/*
                                    stringstream特有的操作
    —————————————————————————————————————————————————————————————————————————————————————
    sstream strm;    | strm是一个未绑定的stringstream对象，sstream是头文件sstream中定义的类型
    sstream strm(s); | strm是一个sstream对象，保存string s的一个拷贝，次构造函数是explicit的
    strm.str()       | 返回strm所保存的string拷贝
    strm.str(s)      | 将string s拷贝到strm中，返回void
    —————————————————————————————————————————————————————————————————————————————————————
*/