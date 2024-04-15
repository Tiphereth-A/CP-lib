#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "../../code/io/fastio.hpp"
#include "../../code/poly/tsh_fps.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polycntt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using poly = tifa_libs::math::polycntt<mint>;

int main() {
  u32 n;
  mint c;
  tifa_libs::fin >> n >> c;
  poly a(n);
  tifa_libs::fin >> a.data();
  tifa_libs::fout << tifa_libs::math::tsh_fps(a, c).data() << '\n';
  return 0;
}
