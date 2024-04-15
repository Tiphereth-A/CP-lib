#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/interp_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  u32 n;
  tifa_libs::fin >> n;
  poly a(n), b(n);
  tifa_libs::fin >> a.data() >> b.data();
  tifa_libs::fout << tifa_libs::math::interp_fps(a, b).data() << '\n';
  return 0;
}
