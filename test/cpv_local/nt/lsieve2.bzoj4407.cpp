// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/4407

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/nt/lsieve/impl2/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using mint = math::mint<math::mint_ms, 1'000'000'000 + 7>;

int main() {
  u32 t, k;
  cin >> t >> k;
  vecu ns(t), ms(t);
  flt_ (u32, i, 0, t) {
    cin >> ns[i] >> ms[i];
    if (ns[i] > ms[i]) std::swap(ns[i], ms[i]);
  }
  u32 n = std::ranges::max(ns);
  math::lsieve2 ls(n);
  static mint pk, lst;
  vec<mint> g = ls.template run<mint>(
      [&](u32 p, u32 e) -> mint {
        if (e == 1) return lst = (pk = math::qpow<mint>(p, k)) - 1;
        else return lst *= pk;
      });
  std::inclusive_scan(begin(g), end(g), begin(g));
  flt_ (u32, i, 0, t) {
    mint res = 0;
    for (u32 n = ns[i], m = ms[i], l = 1, r, d1, d2; l <= n; l = r + 1) {
      r = std::min(n / (d1 = n / l), m / (d2 = m / l));
      res += (g[r] - g[l - 1]) * d1 * d2;
    }
    cout << res.val() << '\n';
  }
}