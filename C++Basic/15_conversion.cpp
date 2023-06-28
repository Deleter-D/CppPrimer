using namespace std;
#include <iostream>
#include <string>

int main()
{
    // 类型转换
    // 隐式转换
    int ival = 3.514 + 3; // 为了避免损失精度，编译器先执行3.541 + 3.0，然后再进行类型转换
    // 隐式转换之算术转换
    bool flag;
    char cval;
    short sval;
    unsigned short usval;
    int ival;
    unsigned int uival;
    long lval;
    unsigned long ulval;
    float fval;
    double dval;

    3.14159L + 'a'; // 'a'提升成int，然后该int值转换为long double
    dval + ival;    // ival转换成double
    dval + fval;    // fval转换成double
    ival = dval;    // dval(切除小数部分后)转换成int
    flag = dval;    // 若dval是0，则flag为false，否则为true
    cval + fval;    // cval提升成int，然后该int值转换成float
    sval + cval;    // sval和cval都提升成int
    cval + lval;    // cval转换成long
    ival + ulval;   // ival转换成unsigned long
    usval + ival;   // 根据unsigned short和int所占空间的大小进行提升
    uival + lval;   // 根据unsigned int和long所占空间的大小进行提升

    // 其他隐式类型转换
    // 数组转换成指针
    int ia[10];
    int *ip = ia; // ia转换成指向数组首元素的指针

    // 转换成布尔类型
    char *cp = "string";
    if (cp) // 如果指针cp不是0，条件为true
    {
        // TODO
    }
    while (*cp) // 如果*cp不是空字符，条件为true
    {
        // TODO
    }

    // 转换成常量
    int ival2;
    const int &jval = ival2;  // 非常量转换成const int的引用
    const int *cptr = &ival2; // 非常量的地址转换成const的地址
    // int &r = j, *q = cptr; // 错误：不允许const转换成非常量，试图删除底层const

    // 类类型定义的转换
    string s, t = "a value"; // 字符串字面值转换成string类型
    while (cin >> s)         // while的条件部分把cin转换成布尔值
    {
        // TODO
    }

    // 关于指针的转换
    /* 0或字面值nullptr能够转换成任意指针类型
       指向任意非常量的指针能够转换成void*
       指向任意对象的指针能够转换成const void*
    */

    // 显式转换
    // 强制转换 cast-name<type>(expression)
    // cast-name是static_cast、dynamic_cast、const_cast和reinterpret_cast中的一种

    // static_cast：只要不包含底层const，都可以使用
    int i, j;
    double slope = static_cast<double>(j) / i;
    double d;
    void *p = &d; // 任何非常量对象的地址都能存入void*
    double *dp = static_cast<double *>(p);

    // const_cast：只能改变运算对象的底层const
    const char *pc;
    char *p = const_cast<char *>(pc); // 如果对象本身是const，通过p写值是未定义的行为
    // *p = "string"; // 该行为未定义
    int a = 5;
    const int *ciptr = &a;
    int *iptr = const_cast<int *>(ciptr); // 对象本身不是const，通过iptr写值是允许的
    *iptr = 4;

    const char *cp;
    char *q = static_cast<char *>(cp); // static_cast不能转换掉const性质
    // const_cast<string>(cp);  // 错误：const_cast只改变常量属性，不能改变类型
    static_cast<string>(cp); // 正确：字符串字面值转换成string类型

    // reinterpret_cast：为运算对象的位模式提供较低层次上的重新解释
    int *ip;
    char *pc = reinterpret_cast<char *>(ip); // 效果类似C风格的强制转换
    // 旧式的强制转换
    // 旧式强制转换在不同的情况下可能是上述强制转换中的不同种类，容易出现不可控的情况，故不建议使用
    char *opc = (char *)ip; // ip是指向int的指针，在这里与reinterpret_cast一样
}