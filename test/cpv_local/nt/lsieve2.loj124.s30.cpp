// competitive-verifier: LOCALCASE test/cpv_local/_data/loj/124

#include "../../../src/math/ds/mint/lib.hpp"
#include "../../../src/math/mint/ms/lib.hpp"
#include "../../../src/math/qpow/basic/lib.hpp"
#include "../../../src/nt/lsieve/impl2/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using mint = math::mint<math::mint_ms, 1'000'000'000 + 7>;

int main() {
  u32 n, k;
  cin >> n >> k;
  math::lsieve2 ls(n);
  mint pk = 1, lst = 1;
  vec<mint> dk = ls.template run<mint>([&](u32 p, u32 e) {
    if (e == 1) pk = math::qpow<mint>(p, k), lst = 1 + pk;
    else lst = lst * pk + 1;
    return lst;
  });
  mint res = 0;
  flt_ (u32, i, 1, n + 1) res += dk[i];
  cout << res.val() << '\n';
}