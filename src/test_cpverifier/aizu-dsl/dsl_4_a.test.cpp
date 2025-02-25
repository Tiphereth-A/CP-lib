#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_4_A"

#include "../../code/geo2d/aunion_pos.hpp"

using point = tifa_libs::geo::point<f128>;
using polygon = tifa_libs::geo::polygon<f128>;

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
  auto res = tifa_libs::geo::aunion_Pos(pos);
  std::cout << res[0] << '\n';
  return 0;
}
