#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../include/comb/gen_derange.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  std::cout << math::gen_derange(n, m) << '\n';
  return 0;
}
