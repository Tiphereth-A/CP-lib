#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_E"

#include "../../code/math/mpi.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::math::mpi a, b;
  std::cin >> a >> b;
  std::cout << a % b << '\n';
  return 0;
}
