#ifndef TIFALIBS_GEO2D_FEMWEBP
#define TIFALIBS_GEO2D_FEMWEBP

#include "massp.hpp"

namespace tifa_libs::geo {

template <class FP>
point<FP> femwebp(vec<point<FP>> CR vp) {
  auto Tl = [&](point<FP> CR y) {
    point<FP> y2;
    math::kahan<FP> sd = 0;
    for (auto&& p : vp)
      if (p != y) {
        FP d = (y - p).norm();
        y2 += p / d, sd += 1 / d;
      }
    return y2 / (FP)sd;
  };
  auto r = [&](point<FP> CR y) {
    point<FP> r;
    for (auto&& p : vp)
      if (p != y) r += (y - p).do_unit();
    return r.norm();
  };
  auto T = [&](point<FP> CR y) {
    if (!std::ranges::count(vp, y)) return Tl(y);
    FP er = 1 / r(y);
    return max((FP)0, 1 - er) * Tl(y) + min((FP)1, er) * y;
  };
  point<FP> y0 = massp(vp), y = T(y0);
  while (y != y0) y0 = y, y = T(y0);
  return y;
}

}  // namespace tifa_libs::geo

#endif