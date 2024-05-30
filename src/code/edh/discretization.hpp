#ifndef TIFALIBS_EDH_DISCRETIZATION
#define TIFALIBS_EDH_DISCRETIZATION

#include "../util/traits.hpp"

namespace tifa_libs {

template <iterable_c T = vec<int>>
CEXP T uniq(T v) {
  std::sort(v.begin(), v.end());
  auto [f, l] = std::ranges::unique(v);
  v.erase(f, l);
  return v;
}
template <iterable_c T = vec<int>>
CEXP std::pair<T, vec<u32>> gen_id(T CR v) {
  const T _ = uniq(v);
  vec<u32> _1;
  _1.reserve(v.size());
  flt_ (u32, i, 0, (u32)v.size()) _1.push_back(u32(std::ranges::lower_bound(_, v[i]) - _.begin()));
  return {_, _1};
}

}  // namespace tifa_libs

#endif