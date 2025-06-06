#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include "../../include/geo2d/min_dis_ps.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
using point = geo::point<i64>;

void solve() {
  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  std::cin >> vp;
  auto [l, r] = geo::min_dis_Ps(vp);
  std::cout << l << ' ' << r << '\n';
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
