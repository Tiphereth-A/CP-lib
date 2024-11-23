#ifndef TIFALIBS_OPT_LCS_CIRC
#define TIFALIBS_OPT_LCS_CIRC

#include "../util/traits.hpp"

namespace tifa_libs::opt {

template <iterable_c T>
CEXP u32 lcs_circ(cT_(T) a, cT_(T) b) {
  T b_(b.size() * 2);
  std::ranges::copy(b, b_.begin()), std::ranges::copy(b, std::back_inserter(b_));
  vvecb left(a.size() + 1, vecb(b_.size() + 1)), up = left;
  auto f = [&](u32 x, u32 y) {
    assert(x && y);
    bool _ = (a[x - 1] == b_[y - 1]) || up[x][y - 1] || left[x - 1][y];
    left[x][y] = _ ^ up[x][y - 1], up[x][y] = _ ^ left[x - 1][y];
  };
  u32 ret = 0;
  flt_ (u32, i, 1, (u32)a.size() + 1)
    flt_ (u32, j, 1, (u32)b_.size() + 1) f(i, j);
  flt_ (u32, i, 0, (u32)b.size()) {
    if (i)
      for (u32 x = 1, y = i; x <= a.size() && y <= b_.size();) {
        bool _ = up[x][y];
        if (y == i) up[x][y] = 0;
        else f(x, y);
        ++(_ == up[x][y] ? x : y);
      }
    u32 now = 0;
    flt_ (u32, x, 1, (u32)a.size() + 1) now += up[x][i + b.size()];
    ret = max(ret, now);
  }
  return ret;
}

}  // namespace tifa_libs::opt

#endif