#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../include/math/isqrt.hpp"
#include "../../include/nt/du_sieve.hpp"
#include "../../include/nt/lsieve.hpp"
#include "../../include/nt/lsieve_func.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_s63.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_s63, MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  vec<mint> sphi;
  {
    auto _ = tifa_libs::math::lsieve<tifa_libs::math::ls_phi>(tifa_libs::math::isqrt(n)).phi;
    sphi.reserve(_.size());
    for (auto i : _) sphi.push_back(i);
    std::inclusive_scan(sphi.begin(), sphi.end(), sphi.begin());
  }
  auto sf = [sphi](u64 x) -> mint { return sphi[x]; };
  auto sg = [](u64 x) -> mint { return x; };
  auto sh = [](u64 x) -> mint { return mint{x} * (x + 1) * ((mint::mod() + 1) / 2); };
  std::cout << tifa_libs::math::du_sieve<mint, decltype(sf), decltype(sg), decltype(sh)>(sphi.size() - 1, sf, sg, sh)(n) << '\n';
  return 0;
}
