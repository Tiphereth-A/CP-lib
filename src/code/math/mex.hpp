#ifndef TIFALIBS_MATH_MEX
#define TIFALIBS_MATH_MEX

#include "../edh/discretization.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

CEXP u32 mex_uniqued(spnu x) NE {
  flt_ (u32, i, 0, (u32)x.size())
    if (x[i] != i) return i;
  return (u32)x.size();
}
CEXP u32 mex(vecu x) NE { return mex_uniqued(uniq(x)); }

}  // namespace tifa_libs::math

#endif