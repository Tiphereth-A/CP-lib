#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../code/math/prime_seq.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, a, b;
  std::cin >> n >> a >> b;
  auto prime = tifa_libs::math::prime_seq(n);
  std::cout << prime.size() << ' ' << (prime.size() + a - 1 - b) / a << '\n';
  for (usz i = b; i < prime.size(); i += a) std::cout << prime[i] << " \n"[i + a >= prime.size()];
  return 0;
}
