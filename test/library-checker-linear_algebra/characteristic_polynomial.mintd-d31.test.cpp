#define AUTO_GENERATED
#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "../../include/io/ios_container.hpp"
#include "../../include/lalg/charpoly_mat.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d31, __LINE__>;
using mat = tifa_libs::math::matrix<mint>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  if (n == 0) {
    std::cout << "1\n";
    return 0;
  }
  mat a(n, n);
  std::cin >> a;
  auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
  std::cout << tifa_libs::math::charpoly(a, is_0) << '\n';
  return 0;
}
