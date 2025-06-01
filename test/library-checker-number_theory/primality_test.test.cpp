#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../include/nt/is_prime.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 n;
    std::cin >> n;
    std::cout << (math::is_prime(n) ? "Yes" : "No") << '\n';
  }
  return 0;
}
