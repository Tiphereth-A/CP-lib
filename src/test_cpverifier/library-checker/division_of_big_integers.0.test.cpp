#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include "../../code/math/mpi.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::math::mpi a, b;
    std::cin >> a >> b;
    auto [q, r] = divmod(a, b);
    std::cout << q << ' ' << r << '\n';
  }
  return 0;
}
