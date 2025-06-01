#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../include/io/fastin.hpp"
#include "../../include/io/fastout.hpp"
#include "../../include/nt/lsieve.hpp"

using namespace tifa_libs;
int main() {
  u32 n, a, b;
  fin >> n >> a >> b;
  auto prime = math::lsieve<>(n + 1).primes;
  fout << prime.size() << ' ' << (prime.size() + a - 1 - b) / a << '\n';
  for (u32 i = b; i < prime.size(); i += a) fout << prime[i] << " \n"[i + a >= prime.size()];
  return 0;
}
