#include <iostream>
#include <vector>
using namespace std;

void process_input(istream &in)
{
    cin.good();
}

int main(int argc, char const *argv[])
{

    auto old_state = cin.rdstate(); // 记录当前cin的状态
    cin.clear();                    // 使cin有效
    process_input(cin);             // 使用cin
    cin.setstate(old_state);        // 将cin置为原有状态

    // 复位failbit和badbit，保持其他标志位不变
    cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);

    // 输出流的缓冲区
    cout << "hi!" << endl;  // 输出hi和一个换行，然后刷新缓冲区
    cout << "hi!" << flush; // 输出hi，然后刷新缓冲区
    cout << "hi!" << ends;  // 输出hi和一个空字符，然后刷新缓冲区

    cout << unitbuf;   // 使用unitbuf使所有输出操作后都立即刷新缓冲区
    cout << nounitbuf; // 使用nounitbuf回到正常的缓冲方式

    // 每个流同时最多关联到一个流，但多个流可以同时关联到一个ostream
    cin.tie(&cout);
    ostream *old_tie = cin.tie(nullptr); // old_tie指向当前关联到cin的流
    cin.tie(&cerr);                      // 将cin与cerr关联，读取cin会刷新cerr而不是cout
    cin.tie(old_tie);                    // 重建cin与cout之间的正常关联

    return 0;
}

/*
                         io库类型和头文件
    ——————————————————————————————————————————————————————————
    | 头文件  | 类型
    ——————————————————————————————————————————————————————————
    iostream | istream, wistream 从流中读取
             | ostream, wostream 写到流中去
             | iostream, wiostream 对流进行读写
    ——————————————————————————————————————————————————————————
    fstream  | ifstream, wifstream 从文件中读取
             | ofstream, wofstream 写到文件中去
             | fstream, wfstream 读写文件
    ——————————————————————————————————————————————————————————
    sstream  | istringstream, wistringstream 从string对象中读取
             | ostringstream, wostringstream 写到string对象中去
             | stringstream, wstringstream 对string对象进行读写
    ——————————————————————————————————————————————————————————
*/

/*
                                                IO库条件状态
    —————————————————————————————————————————————————————————————————————————————————————————————————————
    strm::iostate     | strm是一种IO类型，iostate是一种机器相关的类型，提供了表达条件状态的完整功能
    strm::badbit      | 流已崩溃
    strm::failbit     | 一个IO操作失败了
    strm::eofbit      | 流达到了文件结束
    strm::goodbit     | 流未处于错误状态，此值保证为0
    s.eof()           | 若流s的eofbit置位，则返回true
    s.fail()          | 若流s的failbit或badbit置位，则返回true
    s.bad()           | 若流s的badbit置位，则返回true
    s.good()          | 若流s处于有效状态，则返回true
    s.clear()         | 将流s中的所有条件状态位复位，将流的状态设置为有效，返回void
    s.clear(flags)    | 根据给定的flags标志位，将流s中对应条件状态位复位，返回void。flags的类型为strm::iostate
    s.setstate(flags) | 根据给定的flags标志位，将流s中对应条件状态位复位，返回void。flags的类型为strm::iostate
    s.rdstate()       | 返回流s的当前条件状态，返回类型为strm::iostate
    —————————————————————————————————————————————————————————————————————————————————————————————————————
*/