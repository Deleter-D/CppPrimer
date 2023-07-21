#include <iostream>
// 只取出所需的库函数
// using std::cin;
// using std::cout;
// using std::endl;

// 或直接使用整个命名空间
using namespace std;
// 头文件中不应该包含using声明，因为会被拷贝到引用该头文件的文件中

int main() {
  cout << "Enter two numbers:" << endl;

  int v1, v2;
  cin >> v1 >> v2;

  cout << "The sum of " << v1 << " and " << v2 << " is " << v1 + v2 << endl;

  return 0;
}