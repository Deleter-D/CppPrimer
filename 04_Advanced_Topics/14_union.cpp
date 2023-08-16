#include <iostream>
using namespace std;

// union：一种节省空间的类

union Token {
  // 默认情况下成员是公有的
  char cval;
  int ival;
  double dval;
};

// 全局或命名空间范围的匿名union必须静态声明
static union {
  char cval;
  int ival;
  double dval;
}; // 定义一个未命名的对象，可以直接访问它的成员

class Token2 {
public:
  Token2() : tok(INT), ival(0) {}
  Token2(const Token2 &t) : tok(t.tok) {
    // 根据判别式的不同做出不同行为
    copyUnion(t);
  }
  Token2 &operator=(const Token2 &);
  ~Token2() {
    if (tok == STR)
      // 如果当前union中的类类型成员有值，则需要析构
      sval.~string();
  }
  Token2 &operator=(const string &);
  Token2 &operator=(char);
  Token2 &operator=(int);
  Token2 &operator=(double);

private:
  // 判别式：追踪union的状态
  enum { INT, CHAR, DBL, STR } tok;
  union {
    char cval;
    int ival;
    double dval;
    string sval;
  };
  // 控制union的拷贝
  void copyUnion(const Token2 &);
};

// 管理判别式并销毁string
Token2 &Token2::operator=(int i) {
  if (tok == STR)   // 如union中当前是string
    sval.~string(); // 则析构string
  ival = i;         // 指定合适的union成员
  tok = INT;        // 更新判别式状态
  return *this;
} // char，double版本基本一致
Token2 &Token2::operator=(const string &s) {
  if (tok == STR) // 若union已经是string了
    sval = s;     // 则直接赋值
  else
    new (&sval) string(s); // 否则就需要构造一个string
  tok = STR;               // 更新判别式状态
  return *this;
}

// 管理需要拷贝控制的union成员
void Token2::copyUnion(const Token2 &t) {
  switch (t.tok) {
  case Token2::INT:
    ival = t.ival;
    break;
  case Token2::CHAR:
    cval = t.cval;
    break;
  case Token2::DBL:
    dval = t.dval;
    break;
  case Token2::STR:
    // 拷贝类类型，可以直接利用当前已经存在的内存空间构造新的对象
    new (&sval) string(t.sval);
    break;
  }
}
Token2 &Token2::operator=(const Token2 &t) {
  // 若本对象持有string但t不持有string
  if (tok == STR && t.tok != STR)
    // 则需先析构旧的string
    sval.~string();
  // 若双方均持有string
  if (tok == STR && t.tok == STR)
    // 则直接赋值
    sval = t.sval;
  else
    copyUnion(t); // 否则使用union的拷贝控制
  tok = t.tok;
  return *this;
}

int main(int argc, char const *argv[]) {
  // union可以有多个数据成员，但在任意时刻只有一个数据成员可以有值
  // union不能含有虚函数
  // 见上方定义的Token
  Token first_token = {'a'}; // 初始化union的第一个成员
  Token last_token;          // 未初始化的Token对象
  Token *pt = new Token;     // 指向一个未初始化的Token对象的指针

  last_token.cval = 'z';
  pt->ival = 42;

  delete pt;

  // 未命名的union：编译器会自动地为其创建一个未命名的对象
  // 匿名union不能包含受保护的成员或私有成员，也不能定义成员函数
  cval = 'c'; // 为未命名的对象赋值
  ival = 42;  // 该对象状态改变

  // 含有类类型成员的union
  // 通常把含有类类型的union内嵌在另一个类中
  // 见上方定义的Token2

  // 管理判别式并销毁string
  // 见Token2::operator=的重载

  // 管理需要拷贝控制的union成员
  // 见copyUnion的实现

  return 0;
}