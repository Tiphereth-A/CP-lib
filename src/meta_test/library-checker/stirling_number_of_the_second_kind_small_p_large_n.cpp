#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n"

#include "../../code/comb/stirling2_smallp.hpp"
//
#ifdef GENTC_d31
#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
#endif
#ifdef GENTC_ds
#include "../../code/math/mint_ds.hpp"

using mint = tifa_libs::math::mint_ds<-1>;
#endif

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t, MOD;
  std::cin >> t >> MOD;
#ifdef GENTC_d31
  mint::set_mod(MOD);
#endif
#ifdef GENTC_ds
  mint::set_mod(MOD);
#endif
  tifa_libs::math::Stirling2<mint> S;
  while (t--) {
    u64 n, k;
    std::cin >> n >> k;
    std::cout << S(n, k) << '\n';
  }
  return 0;
}
