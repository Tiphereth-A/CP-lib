#ifndef TIFALIBS_EDH_DISCRETIZATION
#define TIFALIBS_EDH_DISCRETIZATION

#include "../util/traits.hpp"

namespace tifa_libs {

template <iterable_c T>
CEXP T uniq(T v) { return std::sort(v.begin(), v.end()), v.erase(std::unique(v.begin(), v.end()), v.end()), v; }
template <iterable_c T>
CEXP std::pair<T, vecu> gen_id(T CR v) {
  const T _ = uniq(v);
  vecu _1;
  _1.reserve(v.size());
  flt_ (u32, i, 0, (u32)v.size()) _1.push_back(u32(std::ranges::lower_bound(_, v[i]) - _.begin()));
  return {_, _1};
}

}  // namespace tifa_libs

#endif