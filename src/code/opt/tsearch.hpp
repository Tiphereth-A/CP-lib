#ifndef TIFALIBS_OPT_TSEARCH
#define TIFALIBS_OPT_TSEARCH

#include "../util/traits.hpp"

namespace tifa_libs::opt {

// @return $\argmin_{l\leq x\leq r}\{f\}$
template <arithm_c I, class F>
CEXP auto tsearch(I l, I r, F&& f) NE {
  using T = decltype(f(l));
  assert(l <= r);
  I ml, mr;
  T fl = f(l), fr = f(r), fml, fmr;
  using PT = std::conditional_t<std::is_floating_point_v<I>, I, f64>;
  fml = f(ml = l + (r - l) * (1 - std::numbers::phi_v<PT>));
  fmr = f(mr = r - (r - l) * (1 - std::numbers::phi_v<PT>));
  do {
    if CEXP (is_int_v<I>) {
      if (r - l < 8) {
        I x = l, fx = fl;
        if (fr < fx) x = r, fx = fr;
        if (fml < fx) x = ml, fx = fml;
        if (fmr < fx) x = mr, fx = fmr;
        flt_ (I, i, l + 1, r) {
          if (i == ml || i == mr) continue;
          if (T fi = f(i); fi < fx) x = i, fx = fi;
        }
        return std::make_pair(x, fx);
      }
    } else if ((r - l) / max({l, r, (I)1}) < eps_v<I>) return std::make_pair(l, fl);
    if (fml < fmr) r = mr, fr = fmr, mr = ml, fmr = fml, fml = f(ml = l - mr + r);
    else l = ml, fl = fml, ml = mr, fml = fmr, fmr = f(mr = r - ml + l);
  } while (1);
}

}  // namespace tifa_libs::opt

#endif