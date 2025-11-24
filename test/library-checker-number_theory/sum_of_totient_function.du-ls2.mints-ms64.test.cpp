#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../include/math/isqrt.hpp"
#include "../../include/nt/du_sieve.hpp"
#include "../../include/nt/lsieve2.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_ms64.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_ms64, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  vec<mint> sphi;
  {
    mint lst = 1;
    sphi = tifa_libs::math::lsieve2(tifa_libs::math::isqrt(n)).template run<mint>([&lst](u32 p, u32 e) {
      if (e == 1) return lst = p - 1;
      else return lst = lst * p;
    });
    std::inclusive_scan(begin(sphi), end(sphi), begin(sphi));
  }
  auto sf = [sphi](u64 x) -> mint { return sphi[x]; };
  auto sg = [](u64 x) -> mint { return x; };
  auto sh = [](u64 x) -> mint { return mint{x} * (x + 1) * ((mint::mod() + 1) / 2); };
  std::cout << tifa_libs::math::du_sieve<mint, decltype(sf), decltype(sg), decltype(sh)>(sphi.size() - 1, sf, sg, sh)(n) << '\n';
  return 0;
}
