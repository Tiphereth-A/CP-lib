#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../../code/math/pi_34log.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u64 n;
  std::cin >> n;
  std::cout << tifa_libs::math::pi_34log(n) << '\n';
  return 0;
}
