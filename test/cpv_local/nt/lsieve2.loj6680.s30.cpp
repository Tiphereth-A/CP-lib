// competitive-verifier: LOCALCASE test/cpv_local/_data/loj/6680

// clang-format off
#include "../../../src/util/op/pair/lib.hpp"
// clang-format on

#include "../../../src/math/ds/mint/ms/lib.hpp"
#include "../../../src/nt/lsieve/impl2/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using mint = mint_ms<998244353>;

int main() {
  u32 n;
  cin >> n;
  lsieve2 ls(n);
  ptt<mint> lst;
  vecpt<mint> g = ls.run([&](u32 p, u32 e) {
    if (e == 1) return lst = ptt<mint>(p + (p ^ 1), 1 + (p ^ 1));
    else return lst = ptt<mint>((lst.first * p + (p ^ e)), (lst.second + (p ^ e)));
  },
                         ptt<mint>{1, 1});

  vec<mint> f(n + 1);
  f[1] = 1;
  flt_ (u32, i, 2, n + 1) f[i] = f[i - 1] + g[i].first + g[i].first - g[i].second;
  u64 ans = f[1].val();
  flt_ (u32, i, 2, n + 1) ans ^= f[i].val();
  cout << ans << '\n';
}