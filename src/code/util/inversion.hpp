#ifndef TIFALIBS_UTIL_INVERSION
#define TIFALIBS_UTIL_INVERSION

#include "../ds/fenwick.hpp"
#include "discretization.hpp"
#include "util.hpp"

namespace tifa_libs {

template <class T>
constexpr u64 inversion(vec<T> const& v) {
  u64 ans = 0;
  auto id = gen_id(v).second;
  ds::fenwick<u64> tr(v.size() + 1);
  for (u32 i = 0; i < v.size(); ++i) {
    tr.add(id[i] + 1, 1);
    ans += i + 1 - tr.sum(id[i] + 1);
  }
  return ans;
}

}  // namespace tifa_libs

#endif