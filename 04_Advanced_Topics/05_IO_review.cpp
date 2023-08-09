#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  // 通过操纵符改变格式状态
  cout << "default bool values: " << true << " " << false << endl;
  // boolalpha改变布尔值输出的状态
  cout << "alpha bool values: " << boolalpha << true << " " << false << endl;

  bool bool_val = false;
  // noboolalpha恢复默认状态
  cout << bool_val << " " << noboolalpha << bool_val << endl;

  cout << "default: " << 20 << " " << 1024 << endl;
  cout << "octal: " << oct << 20 << " " << 1024 << endl;
  cout << "hex: " << hex << 20 << " " << 1024 << endl;
  cout << "decimal: " << dec << 20 << " " << 1024 << endl;

  cout << showbase; // 显式基底，八进制前添0，十六进制前添0x
  cout << "default: " << 20 << " " << 1024 << endl;
  cout << "in octal: " << oct << 20 << " " << 1024 << endl;
  cout << "in hex: " << hex << 20 << " " << 1024 << endl;
  cout << "in decimal: " << dec << 20 << " " << 1024 << endl;
  cout << noshowbase; // 关闭显式基底

  cout << uppercase << showbase << hex << "printed in hexadecimal: " << 20
       << " " << 1024 << nouppercase << noshowbase << dec << endl;

  double pi = 3.14;
  cout << pi << " " << hexfloat << pi << defaultfloat << " " << pi << endl;

  // 指定打印精度
  cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
  cout.precision(12); // 将打印精度设置为12为数字
  cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
  cout << setprecision(3); // iomanip头文件中定义的修改精度方式
  cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
  cout.precision(6); // 恢复默认

  // 指定浮点数计数法
  cout << "default format: " << 100 * sqrt(2.0) << "\n"
       << "scientific: " << scientific << 100 * sqrt(2.0) << "\n"
       << "fixed decimal: " << fixed << 100 * sqrt(2.0) << "\n"
       << "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << "\n"
       << "use default: " << defaultfloat << 100 * sqrt(2.0) << endl;

  cout << uppercase << "scientific: " << scientific << sqrt(2.0) << '\n'
       << "fixed decimal: " << fixed << sqrt(2.0) << '\n'
       << "hexadecimal: " << hexfloat << sqrt(2.0) << '\n'
       << nouppercase;

  // 未格式化IO操作
  // get()和put()将一个流当作一个无解释的字节序列来处理
  int ch; // 使用int而不是char来接收get()的返回值
  while ((ch = cin.get()) != EOF)
    cout.put(ch);
  cout << endl;

  // 流随机访问
  // ate(at the end)表示打开文档时流指向文件末尾
  // in、out分别表示文件可读可写
  fstream inOut("05_test.txt", fstream::ate | fstream::in | fstream::out);
  if (!inOut) {
    cerr << "Unable to open file!" << endl;
  }
  auto end_mark = inOut.tellg(); // 记录原始的文件尾(EOF)位置
  inOut.seekg(0, fstream::beg);  // 将读标记重定位到文件头
  size_t cnt = 0;
  string line;
  while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) {
    cnt += line.size() + 1; // 统计每行字符数量，加上一个换行符
    auto mark = inOut.tellg();    // 记录当前读取的位置
    inOut.seekp(0, fstream::end); // 将写标记设置到文件流末尾
    inOut << cnt;
    if (mark != end_mark)
      inOut << " ";
    inOut.seekg(mark);
  }
  inOut.seekp(0, fstream::end);
  inOut << "\n";
  inOut.close();

  return 0;
}

/*
                          单字节底层IO操作
    ————————————————————————————————————————————————————————————
    is.get(ch)     | 从istream is读取下一个字节存入字符ch中，返回is
    os.put(ch)     | 将字符ch输出到ostream os，返回os
    is.get()       | 将is的下一个字节作为int返回
    is.putback(ch) | 将字符ch放回is，返回is
    is.unget()     | 将is向后移动一个字节，返回is
    is.peek()      | 将下一个字节作为int返回，但不从流中删除它
    ————————————————————————————————————————————————————————————
*/

/*
                                多字节底层IO操作
    ——————————————————————————————————————————————————————————————————————————
    is.get(sink, size, delim)     |
        从is中读取最多size个字节，并保存在字符数组中，字符数组的起始地址由sink给出
        读取过程直至遇到字符delim或读取了size个字节或遇到文件尾时停止
        如果遇到了delim，则将其留在输入流中，不读取出来存入sink
    is.getline(sink, size, delim) | 与接受三个参数的get版本类似，
                                  | 但会读取并丢弃delim
    is.read(sink, size)           | 读取最多size个字节，
                                  | 存入字符数组sink中。返回is
    is.gcount()                   | 返回上一个未格式化读取操作从is读取的字节数
    os.write(source, size)        | 将字符数组source中的size个字节写入os。返回os
    is.ignore(size, delim)        | 读取并忽略最多size个字符，包括delim。
                                  | 与其他未格式化函数不同，ignore有默认参数：
                                  | size的默认值为1，delim的默认值为文件尾
    ——————————————————————————————————————————————————————————————————————————
    sink是char数组，用来保存数据
*/

/*
                                seek和tell函数
    —————————————————————————————————————————————————————————————————————
    tellg()          | 返回一个输入流中(tellg)或输出流中(tellp)标记的当前位置
    tellp()          |
    seekg(pos)       | 在一个输入流或输出流中将标记重定位到给定的绝对地址
    seekp(pos)       | pos通常是前一个tellg或tellp返回的值
    seekg(off, from) | 在一个输入流或输出流中将标记定位到
    seekp(off, from) | from之前或之后off个字符，from可以是下列值之一
                     | beg，偏移量相对于流开始位置
                     | cur，偏移量相对于流当前位置
                     | end，偏移量相对于流结尾位置
    —————————————————————————————————————————————————————————————————————

*/