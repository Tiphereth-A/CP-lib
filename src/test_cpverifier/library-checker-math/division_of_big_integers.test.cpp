#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include "../../code/io/ios_pair.hpp"
#include "../../code/math/mpi.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::math::mpi a, b;
    std::cin >> a >> b;
    std::cout << divmod(a, b) << '\n';
  }
  return 0;
}
