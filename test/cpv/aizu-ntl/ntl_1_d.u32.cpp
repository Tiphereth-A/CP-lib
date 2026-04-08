// competitive-verifier: PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_D"

#include "../../../src/nt/euler_phi/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  std::cout << euler_phi(n) << '\n';
  return 0;
}
