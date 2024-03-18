#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../code/io/fastio.hpp"
#include "../../code/nt/prime_seq.hpp"

int main() {
  u32 n, a, b;
  tifa_libs::fin >> n >> a >> b;
  auto prime = tifa_libs::math::prime_seq(n);
  tifa_libs::fout << prime.size() << ' ' << (prime.size() + a - 1 - b) / a << '\n';
  for (usz i = b; i < prime.size(); i += a) tifa_libs::fout << prime[i] << " \n"[i + a >= prime.size()];
  return 0;
}
