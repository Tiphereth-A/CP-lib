#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"
#include "../../../src/nt/lsieve/impl1/lib.hpp"

using namespace tifa_libs;
int main() {
  u32 n, a, b;
  fin_uint >> n >> a >> b;
  auto prime = math::lsieve<>(n + 1).primes;
  fout << prime.size() << ' ' << (prime.size() + a - 1 - b) / a << '\n';
  for (u32 i = b; i < prime.size(); i += a) fout << prime[i] << " \n"[i + a >= prime.size()];
  return 0;
}
