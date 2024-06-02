#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/nth_term_lrec.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_s63.hpp"
#include "../../code/poly/polyntt.hpp"

using mint = tifa_libs::math::mint_s63<MOD>;
using poly = tifa_libs::math::polyntt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 d;
  u64 k;
  std::cin >> d >> k;
  vec<mint> a(d), c(d + 1);
  std::cin >> a;
  c[0] = 1;
  fle_ (u32, i, 1, d) {
    std::cin >> c[i];
    c[i] = -c[i];
  }
  std::cout << tifa_libs::math::nth_term_lrec<poly>(k, a, c) << '\n';
  return 0;
}
