#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../code/math/linear_seive.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, a, b;
  std::cin >> n >> a >> b;
  auto prime = tifa_libs::math::linear_seive(
    n + 1, []([[maybe_unused]] tifa_libs::u32 p) {}, []([[maybe_unused]] tifa_libs::u32 i, [[maybe_unused]] tifa_libs::u32 j) {}, []([[maybe_unused]] tifa_libs::u32 i, [[maybe_unused]] tifa_libs::u32 j) {});
  std::cout << prime.size() << ' ' << (prime.size() + a - 1 - b) / a << '\n';
  for (size_t i = b; i < prime.size(); i += a) std::cout << prime[i] << " \n"[i + a >= prime.size()];
  return 0;
}
