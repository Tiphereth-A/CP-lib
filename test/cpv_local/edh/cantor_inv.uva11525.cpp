// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/11525

#include "../../../src/edh/cantor/inv/lib.hpp"

using namespace tifa_libs;
void solve() {
  u32 n;
  std::cin >> n;
  vecu a(n);
  for (auto& i : a) std::cin >> i;
  auto p = cantor_inv_seq(a);
  flt_ (u32, i, 0, n) std::cout << p[i] << " \n"[i == n - 1];
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) solve();
}
