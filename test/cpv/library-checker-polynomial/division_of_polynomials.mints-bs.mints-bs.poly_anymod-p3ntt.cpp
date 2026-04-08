#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../../src/fps/divmod/lib.hpp"
#include "../../../src/io/fastin/lib.hpp"
#include "../../../src/io/fastout/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/fps/ds/ntt3/lib.hpp"
#include "../../../src/math/ds/mint/bs/lib.hpp"

using namespace tifa_libs;
using mint = mint_bs<MOD>;
using namespace tifa_libs;
using mint_p3ntt1 = mint_bs<167772161>;
using mint_p3ntt2 = mint_bs<469762049>;
using mint_p3ntt3 = mint_bs<754974721>;
using poly = poly3ntt<mint, mint_p3ntt1, mint_p3ntt2, mint_p3ntt3>;

int main() {
  u32 n, m;
  tifa_libs::fin_uint >> n >> m;
  poly f(n), g(m);
  tifa_libs::fin_uint >> f >> g;
  auto [q, r] = tifa_libs::divmod_fps(f, g);
  if (q.size() == 1 && q[0].val() == 0) q.resize(0);
  if (r.size() == 1 && r[0].val() == 0) r.resize(0);
  tifa_libs::fout << q.size() << ' ' << r.size() << '\n';
  tifa_libs::fout << q << '\n';
  tifa_libs::fout << r << '\n';
  return 0;
}
