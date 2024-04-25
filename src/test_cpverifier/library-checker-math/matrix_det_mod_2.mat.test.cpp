#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include "../../code/lalg/det_mat.hpp"
#include "../../code/lalg/ge_xor_mat.hpp"
#include "../../code/lalg/mat.hpp"

using mat = tifa_libs::math::matrix<bool>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  char c;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n) {
      std::cin >> c;
      a(i, j) = c & 1;
    }
  auto ge = [](mat &m, bool f) { return tifa_libs::math::ge_xor(m, fn_0, f); };
  std::cout << det(a, ge);
  return 0;
}
