#define PROBLEM "https://judge.yosupo.jp/problem/furthest_pair"

#include "../../code/geo2d/cvh.hpp"

using point = tifa_libs::geo::point<f128>;
using cvh = tifa_libs::geo::cvh<f128>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n;
    std::cin >> n;
    cvh poly(n);
    std::cin >> poly;
    std::map<point, vecu> mp;
    flt_ (u32, i, 0, n) mp[poly.vs[i]].push_back(i);
    poly.init();
    auto [dis, i, j] = poly.template diameter<true>();
    u32 l = mp[poly.vs[i]][0], r = mp[poly.vs[j]][0];
    if (l == r) r = mp[poly.vs[j]][1];
    std::cout << l << ' ' << r << '\n';
  }
  return 0;
}
