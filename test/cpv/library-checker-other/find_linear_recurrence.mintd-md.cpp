#define AUTO_GENERATED
// competitive-verifier: PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../../src/io/container/lib.hpp"
#include "../../../src/math/lrec/berlekamp_massey/lib.hpp"

using namespace tifa_libs;
CEXP u32 MOD = 998244353;

#include "../../../src/math/ds/mint/md/lib.hpp"

using namespace tifa_libs;
using mint = mint_md<__LINE__>;

int main() {
  mint::set_mod(MOD);
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<mint> a(n);
  std::cin >> a;
  auto b = tifa_libs::berlekamp_massey(a);
  std::cout << b.size() - 1 << '\n';
  flt_ (u32, i, 1, (u32)b.size()) std::cout << -b[i] << " \n"[i + 1 == b.size()];
  return 0;
}
