#ifndef TIFALIBS_EDH_DISCRETIZATION_LIB
#define TIFALIBS_EDH_DISCRETIZATION_LIB

#include "../../fast/rsort32/lib.hpp"

namespace tifa_libs {

template <common_range T>
CEXP T uniq(T v) NE {
  tifa_libs::sort(v);
  auto r = unique(begin(v), end(v));
  return {begin(v), begin(r)};
}
template <common_range T>
CEXP std::pair<T, vecu> gen_id(T CR v) NE {
  const T _ = uniq(v);
  vecu _1;
  _1.reserve(v.size());
  flt_ (u32, i, 0, (u32)v.size()) _1.push_back(u32(lower_bound(_, v[i]) - begin(_)));
  return {_, _1};
}

}  // namespace tifa_libs

#endif