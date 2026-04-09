// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/rational_approximation/
#include "../../../src/io/pair/lib.hpp"
#include "../../../src/math/rational_approx/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 n;
    pttuu r;
    std::cin >> n >> r;
    std::cout << rational_approx(n, r) << '\n';
  }
  return 0;
}