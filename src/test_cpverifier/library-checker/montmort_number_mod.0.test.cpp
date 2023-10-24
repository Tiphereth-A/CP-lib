#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../code/comb/derange_mod_gen.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  std::cout << tifa_libs::math::derange_mod_gen(n, m) << '\n';
  return 0;
}
