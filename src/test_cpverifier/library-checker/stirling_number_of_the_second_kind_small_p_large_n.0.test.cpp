#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_small_p_large_n"

#include "../../code/comb/stirling2_smallp.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t, p;
  std::cin >> t >> p;
  tifa_libs::math::Stirling2 S(p);
  while (t--) {
    u64 n, k;
    std::cin >> n >> k;
    std::cout << S(n, k) << '\n';
  }
  return 0;
}
