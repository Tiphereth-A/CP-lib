#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n"

#include "../../code/comb/stirling1_smallp.hpp"
#include "../../code/math/mintdata_ds.hpp"
#include "../../code/math/mint.hpp"

using mintdata = tifa_libs::math::mintdata_ds<-1>;
using mint = tifa_libs::math::mint<mintdata>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t, p;
  std::cin >> t >> p;
  mintdata::set_mod(p);
  tifa_libs::math::Stirling1<mint> s;
  while (t--) {
    u64 n, k;
    std::cin >> n >> k;
    std::cout << s(n, k) << '\n';
  }
  return 0;
}
