#ifndef TIFALIBS_MATH_MEX
#define TIFALIBS_MATH_MEX

#include "../edh/discretization.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

constexpr u32 mex_uniqued(vecu const& x) {
  for (u32 i = 0; i < x.size(); ++i)
    if (x[i] != i) return i;
  return (u32)x.size();
}
constexpr u32 mex(vecu const& x) { return mex_uniqued(uniq(x)); }

}  // namespace tifa_libs::math

#endif