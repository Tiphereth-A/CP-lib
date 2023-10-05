#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"

#include "../../code/geo2d/argsort.hpp"
#include "../../code/geo2d/point.hpp"

using point = tifa_libs::geo::point<tifa_libs::i64>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::cin >> n;
  tifa_libs::vec<point> vp(n);
  for (auto& i : vp) std::cin >> i;
  tifa_libs::geo::argsort(vp);
  size_t idx = 0;
  for (size_t i = 0; i < n; ++i)
    if (vp[i] < vp[idx]) idx = i;
  for (size_t i = idx; i < n; ++i) std::cout << vp[i] << '\n';
  for (size_t i = 0; i < idx; ++i) std::cout << vp[i] << '\n';
  return 0;
}
