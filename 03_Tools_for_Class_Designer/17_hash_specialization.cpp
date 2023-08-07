#include "17_hash_specialization.h"
#include "17_Sales_data.h"


namespace std {
size_t hash<Sales_data>::operator()(const Sales_data &s) const {
  std::cout << "[Special Hash]" << std::endl;
  return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^
         hash<double>()(s.revenue);
}
} // namespace std