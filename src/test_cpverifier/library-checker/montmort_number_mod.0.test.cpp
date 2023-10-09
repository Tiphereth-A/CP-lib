#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../code/math/derange_mod_gen.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, m;
  std::cin >> n >> m;
  auto ans = tifa_libs::math::derange_mod_gen(n, m);
  for (size_t i = 0; i < n; ++i) std::cout << ans[i] << " \n"[i == n - 1];
  return 0;
}
