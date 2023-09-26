#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "../../code/math/is_prime.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::i64 q;
  std::cin >> q;
  while (q--) {
    tifa_libs::u64 n;
    std::cin >> n;
    std::cout << (tifa_libs::math::is_prime(n) ? "Yes" : "No") << '\n';
  }
  return 0;
}
