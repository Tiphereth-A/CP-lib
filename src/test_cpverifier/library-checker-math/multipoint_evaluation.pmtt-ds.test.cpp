#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/mpe_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_ds.hpp"
#include "../../code/poly/polymtt.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
using poly = tifa_libs::math::polymtt<mint>;

int main() {
  mint::set_mod(MOD);
  u32 n, m;
  tifa_libs::fin >> n >> m;
  poly a(n), p(m);
  tifa_libs::fin >> a.data() >> p.data();
  tifa_libs::fout << tifa_libs::math::mpe_fps(a, p).data() << '\n';
  return 0;
}
