#include <iostream>

// const限定符
// 由const限定的变量不可被更改，即将变量定义为一个常量
// const对象必须初始化
// 默认情况下const对象仅在文件内有效，编译器编译时会将有buf_size的地方全部替换为512
const int buf_size = 512;

// const int j = get_size();是运行时初始化
// const int j = 42;是编译时初始化
// const int k;是不被允许的，k是一个未初始化的常量

int func() { return 0; } // 模拟有返回值的函数

// 若想在多文件中共享const对象，则需在变量的定义之前加上extern关键字
// 通常情况不建议这样做
// 假设该常量值由函数返回，在本文件中如此定义
extern const int buf_size_2 = func();
// 在别的文件中并没有定义func()函数，故无法用该函数初始化，此时就可以通过extern获取
extern const int buf_size_2; // 在其他文件中如此获取

// const的引用只能是经过const修饰的
// 若int &r = ci则存在通过r修改ci的风险，故不允许
const int ci = 1024;
const int &r1 = ci;

// 普通变量也可以使用const修饰的引用
int i = 1;
const int &ref1 = i; // 不可通过ref1修改i，但i可通过其他途径修改，故允许
// int &ref2 = ref1; // 不允许通过非常量引用指向一个常量

double dval = 3.14;
// int &rdval2 = dval;   //这种情况是不允许的
/*对于int &rdval2 = dval有一些中间过程
  编译器会使用一个临时变量temp将dval转换类型后对rdval2进行初始化
  故该引用实际上指向的是临时变量temp，并没有真正指向dval
  因此这条语句没有实际意义，故而从语法层面限制了这种情况 */
const int &rdval = dval; // 这种情况是允许的

// 指向常量的指针
const double pi = 3.14;
// double *ptr = &pi; // 存在通过ptr修改常量pi的风险，故不允许
const double *cptr = &pi; // 常量指针可以指向常量

// 指向变量的常量指针
double pi2 = 3.14;
// 不能通过cptr2修改pi2的值，但可以利用这一特性限制指针的权限
const double *cptr2 = &pi2;

// const指针必须初始化，若未初始化，后续不可以对它进行赋值
// 不变的是const指针本身，而不是指向的对象
// 通过cur_err可以修改err_num，因为err_num本身是变量
int err_num = 0;               // 变量
int *const cur_err = &err_num; // 指向变量的常量指针
// 通过pip不可以修改pi3，因为pi3本身是常量
const double pi3 = 3.1415926;   // 常量
const double *const pip = &pi3; // 指向常量的常量指针

// 顶层const：表示指针本身是一个常量
// 底层const：表示指针所指向的对象是一个常量
int num = 0;
int *const ptr_num = &num;   // 顶层
const int num2 = 42;         // 顶层
const int *ptr_num2 = &num2; // 底层
const int *const ptr_num3 = ptr_num2; // 第一个const是底层，第二个const是顶层

constexpr int size() { return 1; }
// C++11标准规定，可将变量声明为constexpr类型，由编译器验证变量的值是否为一个常量表达式
// 初始化的值需要在编译时就得到计算，声明constexpr时用到的类型必须显而易见，容易得到
// 自定义类型、IO库、string等类型不能被定义为constexpr
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size(); // 只有当size()是constexpr函数时才正确

// constexpr修饰指针时，仅对指针有效，与指针所指的对象无关
const int *p = nullptr; // p是一个指向整型常量的指针，const将p修饰为底层
constexpr int *q = nullptr; // q是一个指向整数的常量指针，constexpr将q修饰为顶层
// constexpr指针可以指向常量，也可以指向非常量
int j = 0;
constexpr int cj = 42; // 整型常量
// 上述j与cj在实际中必须定义在函数体外，否则当函数结束，下列两个指针将变成野指针
constexpr const int *p = &cj; // p是常量指针，指向常量cj
constexpr int *p1 = &j;       // p1是常量指针，指向变量j