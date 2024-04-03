#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation/"

#include "../../code/io/ios_pair.hpp"
#include "../../code/math/rational_approx.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    ptt<u64> r;
    std::cin >> n >> r;
    std::cout << tifa_libs::math::rational_approx(n, r) << '\n';
  }
  return 0;
}