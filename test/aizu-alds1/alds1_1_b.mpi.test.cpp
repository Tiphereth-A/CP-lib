#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_B"

#include "../../include/nt/gcd_mpi.hpp"
#include "../../include/rand/gen.hpp"

using namespace tifa_libs;
using math::mpi;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  mpi x, y;
  std::cin >> x >> y;
  rand::Gen<u32> g('0', '9');
  strn s = "1145141919810";
  flt_ (u32, i, 0, 1000) s += (char)g();
  const mpi C = s;
  std::cout << gcd_mpi(x * C, y * C) / C << '\n';
  return 0;
}
