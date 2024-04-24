#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../code/comb/gen_derange.hpp"
#include "../../code/io/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin >> n >> m;
  std::cout << tifa_libs::math::gen_derange(n, m) << '\n';
  return 0;
}
