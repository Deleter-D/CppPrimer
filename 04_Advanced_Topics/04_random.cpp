#include <iostream>
#include <random>
#include <time.h>
#include <vector>
using namespace std;

vector<unsigned> bad_randVec();
vector<unsigned> randVec();

int main(int argc, char const *argv[]) {
  // 若采用相同的引擎，生成的随机数是一样的
  default_random_engine e; // 生成随机无符号数
  for (size_t i = 0; i < 5; ++i)
    cout << e() << " ";
  cout << endl;
  default_random_engine e2;
  for (size_t i = 0; i < 5; ++i)
    cout << e2() << " ";
  cout << endl;

  // 均匀分布
  // 生成0~9之间的均匀分布随机数
  uniform_int_distribution<unsigned> u(0, 9);
  default_random_engine e3;
  for (size_t i = 0; i < 5; ++i)
    // 将u作为随机数发生器
    // 每个调用返回执行范围内并服从均匀分布的值
    cout << u(e3) << " ";
  cout << endl;

  // 引擎生成一个数值序列
  // 每次调用bad_randVec()都会生成相同的100个数
  vector<unsigned> v1 = bad_randVec();
  vector<unsigned> v2 = bad_randVec();
  cout << ((v1 == v2) ? "equal" : "not equal") << endl;
  // 只需要将引擎设置为static的就可以解决
  // 随机数源设不设置static对此处没有影响
  vector<unsigned> v3 = randVec();
  vector<unsigned> v4 = randVec();
  cout << ((v3 == v4) ? "equal" : "not equal") << endl;

  // 设置随机数发生器种子
  default_random_engine e4;          // 使用默认种子
  default_random_engine e5(3147442); // 使用给定种子
  default_random_engine e6;          // 使用默认种子
  e6.seed(32767);                    // 调用seed设置一个新种子
  default_random_engine e7(32767);   // 将种子设置为32767
  for (size_t i = 0; i != 100; ++i) {
    if (e4() == e5())
      cout << "unseeded match at literation: " << i << endl;
    if (e6() != e7())
      cout << "seeded differs at literation: " << i << endl;
  }
  // 以时间为种子：只适合于间隔为秒级或更长的应用
  default_random_engine e8(time(0));

  // 生成随机实数
  default_random_engine e9;
  uniform_real_distribution<double> u2(0, 1);
  for (size_t i = 0; i < 10; ++i)
    cout << u2(e9) << " ";
  cout << endl;
  // 使用分布的默认结果类型
  uniform_real_distribution<> u3(0, 1);
  for (size_t i = 0; i < 10; ++i)
    cout << u3(e9) << " ";
  cout << endl;

  // 生成正态分布的随机数
  default_random_engine e10;
  normal_distribution<> n(4, 1.5); // 均值为4，标准差为1.5
  vector<unsigned> vals(9);
  for (size_t i = 0; i != 200; ++i) {
    unsigned v = lround(n(e10)); // 舍入到最接近的整数
    if (v < vals.size())
      ++vals[v];
  }
  for (size_t i = 0; i != vals.size(); ++i)
    cout << i << ": " << string(vals[i], '*') << endl;

  // 生成伯努利分布的随机数
  string resp;
  default_random_engine e11;
  bernoulli_distribution b;
  do {
    bool flag = b(e11);
    cout << (flag ? "You win" : "You lose") << endl;
    cout << "play again? (y/n)" << endl;
  } while (cin >> resp && resp[0] == 'y');
  return 0;
}

vector<unsigned> bad_randVec() {
  default_random_engine e;
  uniform_int_distribution<unsigned> u(0, 9);
  vector<unsigned> ret;
  for (size_t i = 0; i < 100; ++i)
    ret.push_back(u(e));
  return ret;
}

vector<unsigned> randVec() {
  static default_random_engine e;
  static uniform_int_distribution<unsigned> u(0, 9);
  vector<unsigned> ret;
  for (size_t i = 0; i < 100; ++i)
    ret.push_back(u(e));
  return ret;
}

/*
                            随机数引擎操作
    ——————————————————————————————————————————————————————————————
    Engine e;           | 默认构造函数，使用该引擎类型默认的种子
    Engine e(s);        | 使用整型值s作为种子
    e.seed(s)           | 使用种子s重置引擎状态
    e.min()             | 此引擎可以生成的最小值
    e.max()             | 此引擎可以生成的最大值
    Engine::result_type | 此引擎生产的unsigned整型类型
    e.discard(u)        | 将引擎推进u步，u的类型为unsigned long long
    ——————————————————————————————————————————————————————————————
*/
