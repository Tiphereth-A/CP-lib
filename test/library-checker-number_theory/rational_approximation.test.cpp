#define PROBLEM "https://judge.yosupo.jp/problem/rational_approximation/"

#include "../../include/io/ios_pair.hpp"
#include "../../include/math/rational_approx.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    pttuu r;
    std::cin >> n >> r;
    std::cout << tifa_libs::math::rational_approx(n, r) << '\n';
  }
  return 0;
}