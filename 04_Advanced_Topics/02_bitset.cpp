#include <bitset>
#include <iostream>
using namespace std;

// 标准库定义了bitset类(类模板，需固定大小)，使得位运算更容易

int main(int argc, char const *argv[]) {
  // unsigned值初始化bitset
  // 使用一个整型值初始化bitset时，将转化为unsigned long long
  // 并被当作位模式来处理
  // bitvec1比初始值小，初始值中的高位被丢弃，beef二进制1011 1110 1110 1111
  bitset<13> bitvec1(0xbeef); // 二进制：1 1110 1110 1111
  // betvec2比初始值大，高位被置0
  bitset<20> bitvec2(0xbeef); // 二进制：0000 1011 1110 1110 1111
  // 在64位机器中0ULL是64个0，故~0ULL是64个1
  bitset<128> bitvec3(~0ULL); // 二进制：0~63位为1，64~127位为0

  // 从string初始化bitset
  bitset<32> bitvec4("1100");
  string str("1111111000000011001101");
  bitset<32> bitvec5(str, 5, 4); // 从str[5]开始的四个二进制位，1100
  bitset<32> bitvec6(str, str.size() - 4); // 从str末尾的四个二进制位，1101

  // bitset操作
  bitset<32> bitvec(1U);
  bool is_set = bitvec.any();      // 判断是否有置1的位
  bool is_not_set = bitvec.none(); // 判断是否全为0
  bool all_set = bitvec.all();     // 判断是否全为1
  size_t onBits = bitvec.count();  // 计算1的个数
  size_t sz = bitvec.size();       // 统计位数
  bitvec.flip();                   // 翻转所有位
  bitvec.reset();                  // 所有位复位为0
  bitvec.set();                    // 所有位置1

  bitvec[0] = 0;          // 最低位复位
  bitvec[31] = bitvec[0]; // 最高位置为最低位的值
  bitvec[0].flip();       // 翻转最低位
  ~bitvec[0];             // 最低位取反
  bool b = bitvec[0];     // 将最低位转换为bool类型
  // 下标运算符对const属性进行了重载
  // - const版本返回true或false
  // - 非const版本允许指定位的值

  // 提取bitset值
  // unsigned long ulong = bitvec3.to_ulong();
  unsigned long long ullong = bitvec3.to_ullong();
  // bitset值的大小不能大于转换的类型，否则抛出overflow_error异常

  // bitset的IO运算
  bitset<16> bits;
  cin >> bits; // 从cin读取最多16个0或1，碰到非0或1的字符将停止读取
  cout << "bits: " << bits << endl;

  // 使用bitset
  bool status;
  // 使用位运算符的版本
  unsigned long quizA = 0;      // 此值当作bitset使用
  quizA |= 1UL << 27;           // 指出第27个学生通过了测试
  status = quizA & (1UL << 27); // 检查第27个学生是否通过了测试
  quizA &= ~(1UL << 27);        // 指出第27个学生没有通过测试

  // 使用标准库类bitset完成等价功能
  bitset<30> quizB;   // 每个学生分配一位，所有位初始化为0
  quizB.set(27);      // 指出第27个学生通过了测试
  status = quizB[27]; // 检查第27个学生是否通过了测试
  quizB.reset(27);    // 指出第27个学生没有通过测试
  return 0;
}

/*
                                初始化bitset的方法
    ————————————————————————————————————————————————————————————————————————
    bitset<n> b;    | b有n位，每一位均为0，此构造函数是一个constexpr
    bitset<n> b(u); | b是unsigned long long值u的低n位的拷贝
                    | 如果n大于unsigned long long的大小
                    | 则b中超出unsigned long long的高位被置为0
                    | 此构造函数是一个constexpr
    ————————————————————————————————————————————————————————————————————————
    bitset<n> b(s, pos, m,  | b是string s从位置pos开始m个字符的拷贝
                zero, one); | s只能包含字符zero或one，如果s包含任何其他字符
                            | 构造函数会抛出invalid argument异常
                            | 字符在b中分别保存为zero和one。
                            | pos默认为0，m默认为string::npos
                            | zero默认为'0'，one默认为'1'
    bitset<n> b(cp, pos, m, | 与上面相同，但从cp指向的字符数组中拷贝字符
                zero, one); | 如果未提供m，则cp必须指向一个C风格字符串
                            | 如果提供了m，则从cp开始必须至少有m个zero或one字符
    ————————————————————————————————————————————————————————————————————————
    接受一个string或一个字符指针的构造函数是explicit的
    在新标准中增加了为0和1指定其他字符的功能。
*/