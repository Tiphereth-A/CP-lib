#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../code/nt/is_prime.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  i64 q;
  std::cin >> q;
  while (q--) {
    u64 n;
    std::cin >> n;
    std::cout << (tifa_libs::math::is_prime(n) ? "Yes" : "No") << '\n';
  }
  return 0;
}
