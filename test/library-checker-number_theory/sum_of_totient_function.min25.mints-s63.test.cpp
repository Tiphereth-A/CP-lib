#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../include/nt/min25_sieve.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;

mint f(u64 p, u64 c) {
  u64 res = 1;
  while (--c) res = res * p;
  return res * (p - 1);
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;

  tifa_libs::math::min25_sieve<mint, f> min25(n);
  auto h0 = min25.sum_pk(0), h1 = min25.sum_pk(1);
  flt_ (u32, i, 0, (u32)h1.size()) h1[i] -= h0[i];
  std::cout << min25.run(h1) << '\n';
  return 0;
}
