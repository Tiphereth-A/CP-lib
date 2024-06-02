#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_D"

#include "../../code/nt/euler_phi_u32.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  std::cout << tifa_libs::math::euler_phi_u32(n) << '\n';
  return 0;
}
