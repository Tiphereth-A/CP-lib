#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include "../../code/geo2d/min_dis_ps.hpp"
#include "../../code/io/ios_container.hpp"

using point = tifa_libs::geo::point<f128>;

void solve() {
  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  std::cin >> vp;
  std::map<point, u32> mp;
  fle_ (u32, i, 1, n)
    if (mp[vp[i - 1]]) {
      std::cout << mp[vp[i - 1]] - 1 << ' ' << i - 1 << '\n';
      return;
    } else mp[vp[i - 1]] = i;
  std::ranges::sort(vp);
  auto [dis, l, r] = tifa_libs::geo::min_dis_Ps<f128, true>(vp, 0, n);
  std::cout << mp[vp[l]] - 1 << ' ' << mp[vp[r]] - 1 << '\n';
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
