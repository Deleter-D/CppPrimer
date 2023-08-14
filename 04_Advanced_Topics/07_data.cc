#include "07_data.h"

namespace dataspace {
Data::Data() : a(0), b(0) {}

Data::Data(const int &v1, const int &v2) : a(v1), b(v2) {}

Data::Data(const Data &d) : a(d.a), b(d.b) {}

Data operator+(const Data &lhs, const Data &rhs) {
  return Data(lhs.a + rhs.a, lhs.b + rhs.b);
}

std::ostream &operator<<(std::ostream &os, const Data &d) {
  os << "(" << d.a << "," << d.b << ")";
  return os;
}
} // namespace dataspace