#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../code/geo2d/argsort.hpp"
#include "../../code/geo2d/point.hpp"
#include "../../code/io/ios_container.hpp"

using point = tifa_libs::geo::point<i64>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  std::cin >> vp;
  tifa_libs::geo::argsort(vp);
  std::cout << vp << '\n';
  return 0;
}
