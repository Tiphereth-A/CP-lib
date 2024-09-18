#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../../code/lalg/mat.hpp"

using mat = tifa_libs::math::matrix<bool>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, k;
  std::cin >> n >> m >> k;
  mat a(n, m), b(m, k);
  char ch;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, m) {
      std::cin >> ch;
      a(i, j) = ch & 1;
    }
  flt_ (u32, i, 0, m)
    flt_ (u32, j, 0, k) {
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
