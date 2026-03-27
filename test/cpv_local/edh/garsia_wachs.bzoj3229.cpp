// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/3229

#include "../../../src/edh/garsia_wachs/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n;
  cin >> n;
  vecu v(n + 2);
  flt_ (u32, i, 1, n + 1) cin >> v[i];
  v[0] = v[n + 1] = 0x3f3f3f3f;
  u32 ans = 0;
  garsia_wachs(v, [&](u32, u32, u32, u32, u32 a) { ans += a; });
  cout << ans << '\n';
}