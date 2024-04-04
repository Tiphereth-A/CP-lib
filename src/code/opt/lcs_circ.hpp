#ifndef TIFALIBS_OPT_LCS_CIRC
#define TIFALIBS_OPT_LCS_CIRC

#include "../util/traits.hpp"

namespace tifa_libs::opt {

template <iterable_c T>
constexpr u32 lcs_circ(T const& a, T const& b) {
  T b_(b.size() * 2);
  std::copy(b.begin(), b.end(), b_.begin()), std::copy(b.begin(), b.end(), b_.begin() + b.size());
  vvecb left(a.size() + 1, vecb(b_.size() + 1)), up = left;
  auto f = [&](u32 x, u32 y) {
    assert(x && y);
    bool _ = (a[x - 1] == b_[y - 1]) || up[x][y - 1] || left[x - 1][y];
    left[x][y] = _ ^ up[x][y - 1], up[x][y] = _ ^ left[x - 1][y];
  };
  u32 ret = 0;
  for (u32 i = 1; i <= a.size(); ++i)
    for (u32 j = 1; j <= b_.size(); ++j) f(i, j);
  for (u32 i = 0; i < b.size(); ++i) {
    if (i)
      for (u32 x = 1, y = i; x <= a.size() && y <= b_.size();) {
        bool _ = up[x][y];
        if (y == i) up[x][y] = 0;
        else f(x, y);
        ++(_ == up[x][y] ? x : y);
      }
    u32 now = 0;
    for (u32 x = 1; x <= a.size(); ++x) now += up[x][i + b.size()];
    ret = std::max(ret, now);
  }
  return ret;
}

}  // namespace tifa_libs::opt

#endif