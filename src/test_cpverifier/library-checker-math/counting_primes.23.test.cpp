#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../../code/nt/pi_23.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::pi_23(n) << '\n';
  return 0;
}
