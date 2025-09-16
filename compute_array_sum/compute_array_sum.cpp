#include <compute_array_sum/compute_array_sum.hpp>

int compute_array_sum(const std::array<int, 10> arr) {
  int sum=0;
  for (auto v : arr) { sum+=v; }
  return sum;
}