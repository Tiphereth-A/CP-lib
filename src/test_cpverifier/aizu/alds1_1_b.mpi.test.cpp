#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../code/math/gcd_mpi.hpp"
using tifa_libs::math::mpi;
using std::operator""s;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  mpi x, y;
  std::cin >> x >> y;
  const mpi C = "214748364799824435319711451419198103141592653589793238462643"s;
  std::cout << gcd_mpi(x * C, y * C) / C << '\n';
  return 0;
}
