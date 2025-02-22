#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/nt/lsieve.hpp"

int main() {
  u32 n, a, b;
  tifa_libs::fin >> n >> a >> b;
  auto prime = tifa_libs::math::lsieve<>(n + 1).primes;
  tifa_libs::fout << prime.size() << ' ' << (prime.size() + a - 1 - b) / a << '\n';
  for (u32 i = b; i < prime.size(); i += a) tifa_libs::fout << prime[i] << " \n"[i + a >= prime.size()];
  return 0;
}
