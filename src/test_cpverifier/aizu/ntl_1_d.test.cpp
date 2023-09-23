#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_D"

#include "../../code/math/euler_phi_u64.hpp"

int main() {
  tifa_libs::u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::euler_phi_u64(n) << '\n';
  return 0;
}
