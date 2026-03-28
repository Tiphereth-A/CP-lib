#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../../src/math/iroot/sqrt/lib.hpp"
#include "../../../src/nt/lsieve/func/lib.hpp"
#include "../../../src/nt/lsieve/impl1/lib.hpp"
#include "../../../src/nt/mfsum/du/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u64 n;
  std::cin >> n;
  vec<mint> sphi;
  {
    auto _ = tifa_libs::lsieve<tifa_libs::ls_phi>(tifa_libs::isqrt(n)).phi;
    sphi.reserve(_.size());
    for (auto i : _) sphi.push_back(i);
    std::inclusive_scan(begin(sphi), end(sphi), begin(sphi));
  }
  auto sf = [sphi](u64 x) -> mint { return sphi[x]; };
  auto sg = [](u64 x) -> mint { return x; };
  auto sh = [](u64 x) -> mint { return mint{x} * (x + 1) * ((mint::mod() + 1) / 2); };
  std::cout << tifa_libs::du_sieve<mint, decltype(sf), decltype(sg), decltype(sh)>(sphi.size() - 1, sf, sg, sh)(n) << '\n';
  return 0;
}
