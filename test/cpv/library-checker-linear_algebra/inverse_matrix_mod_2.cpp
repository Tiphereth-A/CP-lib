#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix_mod_2"

#include "../../../src/lalg/bmat/inv/lib.hpp"

using namespace tifa_libs;
using mat = bitmat<1 << 24>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;

  mat bm(n, n);
  std::cin >> bm;
  if (auto res = inv_bmat(bm, n); !res) std::cout << "-1\n";
  else std::cout << res.value() << '\n';

  return 0;
}
