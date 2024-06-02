#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../code/nt/is_prime.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 n;
    std::cin >> n;
    std::cout << (tifa_libs::math::is_prime(n) ? "Yes" : "No") << '\n';
  }
  return 0;
}
