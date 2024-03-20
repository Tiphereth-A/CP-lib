#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../../code/lalg/mat.hpp"

using mat = tifa_libs::math::matrix<bool>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, k;
  std::cin >> n >> m >> k;
  mat a(n, m), b(m, k);
  char ch;
  for (u32 i = 0; i < n; ++i)
    for (u32 j = 0; j < m; ++j) {
      std::cin >> ch;
      a(i, j) = ch & 1;
    }
  for (u32 i = 0; i < m; ++i)
    for (u32 j = 0; j < k; ++j) {
      std::cin >> ch;
      b(i, j) = ch & 1;
    }
  auto c = a * b;
  for (auto& i : c.data()) {
    for (auto j : i) std::cout << j;
    std::cout << '\n';
  }
  return 0;
}
