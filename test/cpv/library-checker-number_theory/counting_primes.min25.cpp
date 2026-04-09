// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/counting_primes
#include "../../../src/nt/mfsum/pi/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  std::cout << pi_min25(n) << '\n';
  return 0;
}
