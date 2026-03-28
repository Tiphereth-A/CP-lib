#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod"

#include "../../../src/lalg/ds/mat/lib.hpp"
#include "../../../src/lalg/mat/det/lib.hpp"
#include "../../../src/lalg/mat/ge/lib.hpp"
#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;
using mat = matrix<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, MOD;
  std::cin >> n >> MOD;
  mint::set_mod(MOD);
  if (!n) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  auto ge = [&is_0](mat& m, bool f) { return ge_mat<mint, decltype(is_0), true>(m, is_0, f); };
  std::cout << det(a, ge);
  return 0;
}
