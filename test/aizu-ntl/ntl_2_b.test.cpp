#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_B"

#include "../../include/math/mpi.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  math::mpi a, b;
  std::cin >> a >> b;
  std::cout << a - b << '\n';
  return 0;
}
