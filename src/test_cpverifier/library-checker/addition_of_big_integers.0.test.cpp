#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"

#include "../../code/math/mpi.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::math::mpi a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
  }
  return 0;
}
