#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "../../code/io/fastin.hpp"
#include "../../code/io/fastout.hpp"
#include "../../code/poly/czt_fps.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_d31.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_d31, __LINE__>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  mint a, r;
  tifa_libs::fin >> n >> m >> a >> r;
  poly f(n);
  tifa_libs::fin >> f;
  tifa_libs::fout << tifa_libs::math::czt_fps(f, r, m, a) << '\n';
  return 0;
}
