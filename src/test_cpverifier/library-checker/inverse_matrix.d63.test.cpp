#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "../../code/lalg/ge_basic_mat.hpp"
#include "../../code/lalg/inv_mat.hpp"
#include "../../code/lalg/mat.hpp"

constexpr u32 MOD = 998244353;

#include "../../code/math/mint_d63.hpp"

using mint = tifa_libs::math::mint_d63<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](mint const &x) { return x.val() == 0; };
  auto ge = [&is_0](mat &m, bool f) { return tifa_libs::math::ge_basic(m, is_0, f); };
  auto res = tifa_libs::math::inv_mat(a, is_0, ge);
  if (res)
    std::cout << res.value();
  else
    std::cout << "-1\n";
  return 0;
}
