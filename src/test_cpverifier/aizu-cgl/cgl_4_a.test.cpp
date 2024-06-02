#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_4_A"

#include "../../code/geo2d/cvh.hpp"

using cvh = tifa_libs::geo::cvh<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  u32 n;
  std::cin >> n;
  cvh p(n);
  std::cin >> p;
  p.template init<false>();
  std::cout << p.size() << '\n';
  u32 now = 0;
  flt_ (u32, i, 1, (u32)p.size())
    if (tifa_libs::is_lt(p[i].y, p[now].y) || (tifa_libs::is_eq(p[i].y, p[now].y) && tifa_libs::is_lt(p[i].x, p[now].x))) now = i;
  flt_ (u32, i, now, (u32)p.size()) std::cout << p[i] << '\n';
  if (now)
    flt_ (u32, i, 0, now) std::cout << p[i] << '\n';
  return 0;
}
