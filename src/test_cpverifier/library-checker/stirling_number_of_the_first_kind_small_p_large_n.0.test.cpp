#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind_small_p_large_n"

#include "../../code/comb/stirling1_smallp.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 t, p;
  std::cin >> t >> p;
  tifa_libs::math::Stirling1 s(p);
  while (t--) {
    tifa_libs::u64 n, k;
    std::cin >> n >> k;
    std::cout << s(n, k) << '\n';
  }
  return 0;
}
