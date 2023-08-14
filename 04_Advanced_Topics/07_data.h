#include <iostream>
#include <string>

namespace dataspace {
class Data {
  friend Data operator+(const Data &, const Data &);
  friend std::ostream &operator<<(std::ostream &, const Data &);

public:
  Data();
  Data(const int &, const int &);
  Data(const Data &);

private:
  int a, b;
};

Data operator+(const Data &, const Data &);
std::ostream &operator<<(std::ostream &, const Data &);
} // namespace dataspace