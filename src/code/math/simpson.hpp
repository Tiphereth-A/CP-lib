#ifndef TIFALIBS_MATH_SIMPSON
#define TIFALIBS_MATH_SIMPSON

#include "../util/util.hpp"

namespace tifa_libs::math {

// Func = FP(FP)
template <class FP, class Func>
class simpson_impl {
  Func f;

  constexpr static FP sps(FP l, FP r, FP fl, FP fmid, FP fr) { return (fl + 4 * fmid + fr) * (r - l) / 6; }
  FP asr(FP l, FP r, FP area, FP eps, i64 dep) const {
    FP mid = r - (r - l) * .5;
    FP lmid = mid - (mid - l) * .5, rmid = r - (r - mid) * .5;
    FP fl = f(l), flmid = f(lmid), fmid = f(mid), frmid = f(rmid), fr = f(r);
    FP ls = sps(l, mid, fl, flmid, fmid), rs = sps(mid, r, fmid, frmid, fr);
    if (std::abs(ls + rs - area) <= 15 * eps && dep <= 0) return ls + rs + (ls + rs - area) / 15;
    return asr(l, mid, ls, eps * .5, dep - 1) + asr(mid, r, rs, eps * .5, dep - 1);
  }

 public:
  explicit simpson_impl(Func func) : f(func) {}
  FP operator()(FP l, FP r, FP eps, i64 min_dep) const { return asr(l, r, sps(l, r, f(l), f(r - (r - l) * .5), f(r)), eps, min_dep); }
  FP operator()(FP l, FP r, FP eps) const { return asr(l, r, sps(l, r, f(l), f(r - (r - l) * .5), f(r)), eps, -1); }
};

}  // namespace tifa_libs::math

#endif