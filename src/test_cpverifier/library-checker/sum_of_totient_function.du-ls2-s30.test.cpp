#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../code/math/du_sieve.hpp"
#include "../../code/math/isqrt.hpp"
#include "../../code/math/lsieve2.hpp"
#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s30.hpp"

using mintdata = tifa_libs::math::mintdata_s30<998244353>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u64 n;
  std::cin >> n;
  vec<mint> sphi;
  {
    mint lst = 1;
    sphi = tifa_libs::math::lsieve2(tifa_libs::math::isqrt(n)).template run<mint>([&lst](u32 p, u32 e) {
      if (e == 1) return lst = p - 1;
      else return lst = lst * p;
    });
    std::partial_sum(sphi.begin(), sphi.end(), sphi.begin());
  }
  auto sf = [sphi](u64 x) -> mint { return sphi[x]; };
  auto sg = [](u64 x) -> mint { return x; };
  auto sh = [](u64 x) -> mint { return mint{x} * (x + 1) * ((mint::mod() + 1) / 2); };
  std::cout << tifa_libs::math::du_sieve<mint, decltype(sf), decltype(sg), decltype(sh)>(sphi.size() - 1, sf, sg, sh)(n) << '\n';
  return 0;
}
