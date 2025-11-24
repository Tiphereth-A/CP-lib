#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"

#include "../../include/lalg/ge_mat.hpp"
#include "../../include/lalg/mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_md.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_md, __LINE__>;
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
  std::cout << abs(tifa_libs::math::ge_mat(a, is_0, false));
  return 0;
}
