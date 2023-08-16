#include <iostream>
using namespace std;

// 因机器而异的特性，移植需要重新编译，例如算术类型
// 类可以将其(非静态)数据成员定义为位域(bit-field)
// 当一个程序需要向其他成员或硬件传递二进制数据时通常会用到位域

// 位域在内存中的布局与机器是相关的
// 位域必须是整型或枚举类型
// 取地址符不能用于位域，因此指针无法指向类的位域
typedef unsigned int Bit;
class File {
  // 指定每个变量的比特数
  Bit mode : 2;
  Bit modeified : 1;
  Bit prot_owner : 3;
  Bit prot_group : 3;
  Bit prot_world : 3;
  // 这5个位域可能会被压缩到同一个unsigned int中
  // 能否压缩到同一个unsigned int中，以及如何压缩是取决于机器的

public:
  enum modes { READ = 01, WRITE = 02, EXECUTE = 03 };
  File &open(modes);
  void close();
  void write();
  bool isRead() const;
  void setWrite();
  void execute();
  bool isExecute() const;
};
void File::write() { modeified = 1; }
void File::close() {
  if (modeified)
    cout << "save" << endl;
}
inline bool File::isRead() const { return mode & READ; }
inline void File::setWrite() { mode |= WRITE; }
File &File::open(File::modes m) {
  mode |= READ;
  if (m & WRITE)
    cout << "File mode WRITE is set." << endl;
  return *this;
}

// volatile限定符
// 告诉编译器不应对这样的对象进行优化
// 若一个变量被volatile修饰，编译器将不会把它保存到寄存器中
// 而是每次都去访问内存中实际保存该变量的位置
class Task {};
class Screen {};

volatile int display_register; // 该int值可能发生变化
volatile Task *curr_task;      // curr_task指向一个volatile对象
volatile int iax[10];          // iax的每个元素都是volatile的
volatile Screen bitmapBuf;     // bitmapBuf的每个成员都是volatile的

volatile int v;              // v是一个volatile int
int *volatile vip;           // vip是一个volatile指针，指向int
volatile int *ivp;           // ivp是一个指针，指向volatile int
volatile int *volatile vivp; // vivp是一个volatile指针，指向volatile int

// 合成的拷贝对volatile无效，需要手动编写
class Foo {
public:
  // 从一个volatile对象进行拷贝
  Foo(const volatile Foo &) {}
  // 将一个volatile对象赋值给一个非volatile对象
  Foo &operator=(volatile const Foo &) {}
  // 将一个volatile对象赋值给一个volatile对象
  Foo &operator=(volatile const Foo &) volatile {}
};

// 链接指示，extern "C"
// 指出任意非C++函数所用的语言

// 单语句链接指示
extern "C" size_t strlen(const char *);
// 符合语句链接指示
extern "C" {
int strcmp(const char *, const char *);
char *strcat(char *, const char *);
}

// 链接指示与头文件
extern "C" {
#include <string.h> // 操作C风格字符串的C函数
// 头文件中的所有普通函数声明都被认为是由链接指示的语言编写的
// 链接指示可以嵌套
}

// 指向extern "C"函数的指针
extern "C" void (*pf)(int); // pf指向一个C函数，该函数接受一个int返回void
void (*pf1)(int);           // 指向一个C++函数
extern "C" void (*pf2)(int); // 指向一个C函数

// 链接指示对整个声明都有效
// f1是一个C函数，它的形参是一个指向C函数的指针
extern "C" void f1(void (*)(int));
// FC是一个指向C函数的指针
extern "C" typedef void FC(int);
// f2是一个C++函数，该函数的形参是执行C函数的指针
void f2(FC *);

// 导出C++函数到其他语言
// 通过链接指示对函数进行定义
extern "C" double calc(double dparm) {}
// 编译器将为该函数生成适合于指定语言的代码

// 重载函数与链接指示
// 错误：两个extern "C"函数名称相同
// extern "C" void print(const char *);
// extern "C" void print(int);

class SmallInt {};
class BigNum {};
// C函数可以在C或C++程序中调用
// C++函数重载了该函数，可以在C++程序中调用
extern "C" double calc(double);
extern SmallInt calc(const SmallInt &);
extern BigNum calc(const BigNum &);

int main(int argc, char const *argv[]) {
  File myFile;
  myFile.open(File::WRITE);
  if (myFile.isRead())
    cout << "reading" << endl;

  // int *ip = &v; // 错误：必须使用指向volatile的指针
  ivp = &v;  // 正确：ivp是一个指向volatile的指针
  vivp = &v; // 正确：vivp是一个指向volatile的volatile指针

  // 指向extern "C"函数的指针
  // pf1 = pf2; // 错误：pf1和pf2类型不同
  return 0;
}