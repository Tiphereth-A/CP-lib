#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../include/geo2d/argsort.hpp"
#include "../../include/geo2d/point.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
using point = geo::point<i64>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vec<point> vp(n);
  std::cin >> vp;
  geo::argsort(vp);
  std::cout << vp << '\n';
  return 0;
}
