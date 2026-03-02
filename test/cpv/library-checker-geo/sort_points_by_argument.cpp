#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../../src/geo2d/argsort/lib.hpp"
#include "../../../src/geo2d/ds/p/lib.hpp"
#include "../../../src/io/container/lib.hpp"

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
