// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primality_test
#include "../../../src/nt/is_prime/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 n;
    std::cin >> n;
    std::cout << (is_prime(n) ? "Yes" : "No") << '\n';
  }
  return 0;
}
