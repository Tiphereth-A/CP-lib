#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "../../code/lalg/ge_basic_mat.hpp"
#include "../../code/lalg/mat.hpp"

CEXP u32 MOD = 998244353;

#include "../../code/math/mint_d31.hpp"

using mint = tifa_libs::math::mint_d31<-1>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  if (!n || !m) {
    std::cout << "0\n";
    return 0;
  }
  mat a(n, m);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  std::cout << abs(tifa_libs::math::ge_basic(a, is_0, false));
  return 0;
}
