#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include "../../code/math/mpi.hpp"
#include "../../code/io/ios_pair.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    tifa_libs::math::mpi a, b;
    std::cin >> a >> b;
    std::cout << divmod(a, b) << '\n';
  }
  return 0;
}
