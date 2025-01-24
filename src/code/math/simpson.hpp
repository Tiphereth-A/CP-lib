#ifndef TIFALIBS_MATH_SIMPSON
#define TIFALIBS_MATH_SIMPSON

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::floating_point FP, FP (*f)(FP)>
class simpson_impl {
  static CEXP FP sps(FP l, FP r, FP fl, FP fmid, FP fr) NE { return (fl + 4 * fmid + fr) * (r - l) / 6; }
  CEXP FP asr(FP l, FP r, FP area, FP eps, i64 dep) CNE {
    const FP mid = r - (r - l) * .5, lmid = mid - (mid - l) * .5, rmid = r - (r - mid) * .5;
    const FP fl = f(l), flmid = f(lmid), fmid = f(mid), frmid = f(rmid), fr = f(r);
    const FP ls = sps(l, mid, fl, flmid, fmid), rs = sps(mid, r, fmid, frmid, fr);
    if (abs(ls + rs - area) <= 15 * eps && dep <= 0) return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5, dep - 1) + asr(mid, r, rs, eps * .5, dep - 1);
  }

 public:
  CEXP FP operator()(FP l, FP r, FP eps = eps_v<FP>, i64 min_dep = -1) CNE { return asr(l, r, sps(l, r, f(l), f(r - (r - l) * .5), f(r)), eps, min_dep); }
};

}  // namespace tifa_libs::math

#endif