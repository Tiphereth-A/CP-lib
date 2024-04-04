#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../code/lalg/det_mat.hpp"
#include "../../code/lalg/ge_basic_mat.hpp"
#include "../../code/lalg/mat.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<MOD>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  std::cout << det(a, ge);
  return 0;
}
