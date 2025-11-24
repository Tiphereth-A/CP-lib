#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_4_A"

#include "../../include/geo2d/aunion_pos.hpp"

using namespace tifa_libs;
using point = geo::point<f128>;
using polygon = geo::polygon<f128>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  u32 n;
  std::cin >> n;
  vec<polygon> pos;
  pos.reserve(n);
  flt_ (u32, i, 0, n) {
    point p1, p2;
    std::cin >> p1 >> p2;
    if (p1 > p2) swap(p1, p2);
    pos.push_back({p1, point{p2.x, p1.y}, p2, point{p1.x, p2.y}});
  }
  std::ranges::sort(pos, less{}, [](auto CR p) { return p.vs; });
  auto [l, r] = unique(pos, equal_to{}, [](auto CR p) { return p.vs; });
  pos.erase(l, r);
  auto res = geo::aunion_Pos(pos);
  std::cout << res[0] << '\n';
  return 0;
}
