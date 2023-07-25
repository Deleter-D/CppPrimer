#include "11_Basket.h"
#include "11_Bulk_quote2.h"
#include "11_Quote.h"
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
  // 使用容器存放继承体系中的对象时，通常采用间接存储的方式
  // 若采用直接存储方式
  vector<Quote> basket;
  basket.push_back(Quote("0-201-1", 50));
  // 正确：但只能把对象的Quote部分拷贝给basket
  basket.push_back(Bulk_quote2("0-201-8", 50, 10, .25));
  // 调用Quote定义的版本
  cout << basket.back().net_price(15) << endl;

  // 而采用间接存储方式，在容器中放置(智能)指针而非对象
  vector<shared_ptr<Quote>> basket2;
  basket2.push_back(make_shared<Quote>("0-201-1", 50));
  basket2.push_back(make_shared<Bulk_quote2>("0-201-8", 50, 10, .25));
  // 调用Bulk_quote2定义的版本
  cout << basket2.back()->net_price(15) << endl;

  Basket bsk;
  bsk.add_item(make_shared<Quote>("123", 45));
  bsk.add_item(make_shared<Quote>("123", 45));
  bsk.add_item(make_shared<Bulk_quote2>("345", 45, 3, .15));
  bsk.add_item(make_shared<Bulk_quote2>("345", 45, 3, .15));
  bsk.add_item(make_shared<Bulk_quote2>("345", 45, 3, .15));
  bsk.total_receipt(cout);
  // 这样使用时候需要传入指针，比较麻烦

  // 隐藏指针
  // 为此需要给Quote类添加一个虚函数clone，该虚函数返回当前对象的一分动态分配的拷贝
  // 详见11_Quote.h与11_Bulk_quote2.h
  // 并重新定义add_item，使得其接受一个Quote对象而非指针，详见11_Basket.h
  // 这样可以使得容器中的静态类型均为Quote
  // 但在add_item函数中实际调用时会根据动态类型调用对应的版本
  Basket bsk2;
  bsk2.add_item(Quote("123", 45));
  bsk2.add_item(Quote("123", 45));
  bsk2.add_item(Bulk_quote2("345", 45, 3, .15));
  bsk2.add_item(Bulk_quote2("345", 45, 3, .15));
  bsk2.add_item(Bulk_quote2("345", 45, 3, .15));
  bsk2.total_receipt(cout);

  return 0;
}