#define AUTO_GENERATED
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include "../../include/math/qpow.hpp"

using namespace tifa_libs;
CEXP u64 MOD = 1'000'000'007;

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d31, __LINE__>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  mint m;
  u64 n;
  std::cin >> m >> n;
  std::cout << tifa_libs::math::qpow(m, n).val() << '\n';
  return 0;
}
