#ifndef TIFALIBS_MATH_INVERSION_LIB
#define TIFALIBS_MATH_INVERSION_LIB

#include "../../ds/fenwick/d1/lib.hpp"
#include "../../edh/discretization/lib.hpp"

namespace tifa_libs::math {

template <class T>
CEXP u64 inversion(vec<T> CR v) NE {
  u64 ans = 0;
  auto id = gen_id(v).second;
  ds::fenwick<u64> tr((u32)v.size() + 1);
  flt_ (u32, i, 0, (u32)v.size()) tr.add(id[i] + 1, 1), ans += i + 1 - tr.sum(id[i] + 1);
  return ans;
}

}  // namespace tifa_libs::math

#endif