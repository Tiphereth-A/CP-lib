#ifndef TIFALIBS_MATH_MEX
#define TIFALIBS_MATH_MEX

#include "../util/util.hpp"

namespace tifa_libs::math {

constexpr u32 mex_uniqued(vecu const& x) {
  for (u32 i = 0; i < x.size(); ++i)
    if (x[i] != i) return i;
  return (u32)x.size();
}
constexpr u32 mex(vecu x) {
  std::sort(x.begin(), x.end());
  x.erase(std::unique(x.begin(), x.end()), x.end());
  return mex_uniqued(x);
}

}  // namespace tifa_libs::math

#endif