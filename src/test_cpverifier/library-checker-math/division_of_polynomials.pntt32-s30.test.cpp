#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/divmod_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly f(n), g(m);
  tifa_libs::fin >> f.data() >> g.data();
  auto [q, r] = tifa_libs::math::divmod_fps(f, g);
  if (q.size() == 1 && q[0].val() == 0) q.resize(0);
  if (r.size() == 1 && r[0].val() == 0) r.resize(0);
  tifa_libs::fout << q.size() << ' ' << r.size() << '\n';
  tifa_libs::fout << q.data() << '\n';
  tifa_libs::fout << r.data() << '\n';
  return 0;
}
