#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../../src/comb/seq/derange/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  std::cout << gen_derange(n, m) << '\n';
  return 0;
}
