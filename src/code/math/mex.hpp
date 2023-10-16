#ifndef TIFA_LIBS_MATH_MEX
#define TIFA_LIBS_MATH_MEX

#include "../util/util.hpp"

namespace tifa_libs::math {

inline u32 mex_uniqued(vec<u32> const& x) {
  for (u32 i = 0; i < x.size(); ++i)
    if (x[i] != i) return i;
  return (u32)x.size();
}
inline u32 mex(vec<u32> x) {
  std::sort(x.begin(), x.end());
  x.erase(std::unique(x.begin(), x.end()), x.end());
  return mex_uniqued(x);
}

}  // namespace tifa_libs::math

#endif