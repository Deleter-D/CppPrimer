#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// 读写一个IO对象会改变其状态，因此传递和返回的引用不能是const的
ofstream out1, out2;
// out1 = out2;              // 错误，不能对流对象赋值
// ofstream print(ofstream); // 错误，不能将形参或是返回类型设为流类型
// out2 = print(out2);       // 错误，out2不是可修改的左值

void process_input(istream &in)
{
    cin.good();
}

int main(int argc, char const *argv[])
{
    // 文件IO
    string ifile = "test.txt";  // string对象指定文件名
    ifstream fin(ifile);        // 构造一个ifstream并打开该文件
    ofstream fout;              // 创建一个文件输出流，未关联文件
    fout.open(ifile + ".copy"); // 打开指定文件
    if (fout)                   // 检查是否成功打开
    {
        cout << "file open succeed." << endl;
    }
    fin.close();           // 关闭文件
    fin.open(ifile + "2"); // 打开另一个文件

    // 文件流的自动构造和析构
    vector<string> args = {"file1", "file2", "file3"};
    for (string file_name : args)
    {
        ifstream input(file_name);
        if (input)
            process_input(input);
        else
            cerr << "couldn't open: " + file_name << endl;
    } // 每个循环步input都会离开作用域，故会被消耗，消耗时自动调用close

    // 文件模式
    ofstream out("file1");                                   // 隐含以输出模式打开文件并截断文件
    ofstream out2("file1", ofstream::out);                   // 隐含地截断文件
    ofstream out3("file1", ofstream::out | ofstream::trunc); // 与上两句效果相同
    // 保留文件内容时必须显示指定app模式
    ofstream app("file2", ofstream::app);                  // 隐含为输出模式
    ofstream app2("file2", ofstream::out | ofstream::app); // 与上句效果相同

    return 0;
}

/*
                                        fstream特有的操作（除继承iosteam外）
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————
    fstream fstrm;          | 创建一个未绑定的文件流，fstream是头文件fstream中定义的一个类
    fstream fstrm(s);       | 创建一个fstream，并打开名为s的文件，
                            | 这些构造函数都是explicit的，默认的文件模式mode依赖于fstream的类型
    fstream fstrm(s, mode); | 与前一个构造函数类似，但按指定mode打开文件
    fstrm.open(s);          | 打开名为s的文件，并将文件与fstrm绑定，默认的文件模式mode依赖于fstream的类型，返回void
    fstrm.close(s);         | 关闭fstrm绑定的文件，返回void
    fstrm.is_open(s);       | 返回bool值，指出与fstrm绑定的文件是否成功打开且尚未关闭
    ——————————————————————————————————————————————————————————————————————————————————————————————————————————
*/

/*
                      文件模式
    ——————————————————————————————————————————————
    in     | 以读方式打开
    out    | 以写方式打开
    app    | 即append追加，每次写操作前定位到文件末尾
    ate    | 即at end，每次打开文件后立即定位到末尾
    trunc  | 截断，如果打开的文件存在，则内容将被丢弃
    binary | 以二进制方式进行IO
    ——————————————————————————————————————————————
*/