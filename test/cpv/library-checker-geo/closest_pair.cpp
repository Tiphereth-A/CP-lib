// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/closest_pair
#include "../../../src/geo2d/min_dis_ps/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using point_t = point<i64>;

void solve() {
  u32 n;
  std::cin >> n;
  vec<point_t> vp(n);
  std::cin >> vp;
  auto [l, r] = min_dis_Ps(vp);
  std::cout << l << ' ' << r << '\n';
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
