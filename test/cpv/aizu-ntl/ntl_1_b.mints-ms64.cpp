#define AUTO_GENERATED
// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B
#include "../../../src/math/qpow/basic/lib.hpp"

using namespace tifa_libs;
CEXP u64 MOD = 1'000'000'007;

#include "../../../src/math/ds/mint/ms64/lib.hpp"

using namespace tifa_libs;
using mint = mint_ms64<MOD>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  mint m;
  u64 n;
  std::cin >> m >> n;
  std::cout << tifa_libs::qpow(m, n).val() << '\n';
  return 0;
}
