#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/mpe_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ss.hpp"
#include "../../code/poly/polyntt32.hpp"

using mint = tifa_libs::math::mint_ss<MOD>;
using poly = tifa_libs::math::polyntt32<mint>;

int main() {
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly a(n), p(m);
  tifa_libs::fin >> a.data() >> p.data();
  tifa_libs::fout << tifa_libs::math::mpe_fps(a, p).data() << '\n';
  return 0;
}
