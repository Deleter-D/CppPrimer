#include <iostream>
#include <cstdlib>

bool boolean = true;

char character = 'c';                // 8位
wchar_t wide_character = 'c';        // 16位
char16_t unicode_character_16 = 'c'; // 16位
char32_t unicode_character_32 = 'c'; // 32位
// char有三种类型，char、signed char、unsigned char
// 但表现形式只有两种：带符号和无符号的
// char的实际类型根据编译器的不同，实际表现为char或signed char
signed char signed_charater = 'c';
unsigned char unsigned_charater = 'c';

// 以下类型均可用unsigned修饰，表示无符号类型
short short_integer = 1;               // 16位
int integer = 1;                       // 16位
long long_integer = 1;                 // 32位
long long long_long_integer = 1;       // 64位
float decimal_float = 1.1;             // 32位，6位有效数字
double decimal_double = 1.1;           // 64位，10位有效数字
long double decimal_long_double = 1.1; // 96或128位，10位有效数字

/* 初始化与赋值不同
   初始化：创建变量时赋予其一个初始值
   赋值：把对象的当前值擦除，以一个新值来替代 */
// 初始化的四种方式
int a = 0;
int b = {0}; // 该方式称为列表初始化
int c{0};
int d(0);

// 变量只能被定义一次，但可以声明多次
// 声明就是引入其他源文件中定义的非static全局变量
// 若要声明一个变量，但不定义，可以用extern关键字
extern int i; // 声明但不定义
int j;        // 声明且定义
// 但若在使用了extern关键字的前提下，将变量初始化，则extern失去作用
extern int k = 0; // 声明且定义

int main()
{
   // 引用必须初始化，int &ref_val;会报错
   // 引用一旦绑定对象后，则不可再重新绑定到另一个对象
   // 因为引用本身不是对象，所以不可以定义引用的引用
   int ival = 1024;
   int &ref_val = ival;     // ref_val指向ival，是ival的别名，本身并没有空间存储ival的数据
   ref_val = 2;             // 赋值给引用指向的对象，相当于ival = 2;
   int ii = ref_val;        // 相当于ii = ival;
   int $ref_val2 = ref_val; // 将ref_val2绑定到ref_val绑定的对象上，即绑定了ival

   // 指针本身就是对象，是对地址的封装
   int *p = &ival;               // 用取地址符&获取ival的地址
   std::cout << *p << std::endl; // 用解引用符*利用指针访问对象
   std::cout << p << std::endl;  // 不用解引用符则输出地址

   // 空指针不指向任何对象
   int *p1 = nullptr; // C++11以后推荐初始化为nullptr
   int *p2 = 0;       // 初始化为0也相当于空指针
   int *p3 = NULL;    // 需要#include <cstdlib>，其中有一个名为NULL的预处理变量

   // void*指针是纯粹的地址封装，与类型无关，可以存放任意对象的地址
   // 这种指针常用于回调函数中，因为回调函数有时候无法确定返回值的类型
   double obj = 3.14;
   double *pd = &obj;
   void *pv = &obj;
   pv = pd;

   // 指向指针的指针
   int *pi = &ival;
   int **ppi = &pi; // ppi指向int型的指针pi

   // 指针本身就是对象，故可以定义引用
   int i = 100;
   int *p;
   int *&r = p; // r是一个引用，引用一个int型的指针，即r是p的别名
   r = &i;      // 等同于p = &i
   *r = 0;      // 等同于*p = 0，即将i赋值为0

   return 0;
}
