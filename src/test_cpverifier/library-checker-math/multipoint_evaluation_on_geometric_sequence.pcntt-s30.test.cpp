#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/czt_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  u32 n, m;
  mint a, r;
  tifa_libs::fin >> n >> m >> a >> r;
  poly f(n);
  tifa_libs::fin >> f.data();
  tifa_libs::fout << tifa_libs::math::czt_fps(f, r, m, a).data() << '\n';
  return 0;
}
