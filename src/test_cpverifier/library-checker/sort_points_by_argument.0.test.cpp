#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../code/geo2d/argsort.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo::point<i64>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n;
  std::cin >> n;
  vec<point> vp(n);
  for (auto& i : vp) std::cin >> i;
  tifa_libs::geo::argsort(vp);
  for (auto& i : vp) std::cout << i << '\n';
  return 0;
}
