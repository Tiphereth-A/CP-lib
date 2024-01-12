#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_s63.hpp"
#include "../../code/poly/poly.hpp"
#include "../../code/poly/poly_divmod.hpp"
#include "../../code/poly/polydata_scntt.hpp"
#include "../../code/util/fastio.hpp"

using mintdata = tifa_libs::math::mintdata_s63<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using poly_t = tifa_libs::math::poly<tifa_libs::math::polydata_scntt<mint>>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly_t f(n), g(m);
  tifa_libs::fin >> f.data() >> g.data();
  auto [q, r] = tifa_libs::math::poly_divmod(f, g);
  if (q.size() == 1 && q[0].val() == 0) q.resize(0);
  if (r.size() == 1 && r[0].val() == 0) r.resize(0);
  tifa_libs::fout << q.size() << ' ' << r.size() << '\n';
  tifa_libs::fout << q.data() << '\n';
  tifa_libs::fout << r.data() << '\n';
  return 0;
}
