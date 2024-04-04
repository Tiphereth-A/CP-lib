#ifndef TIFALIBS_EDH_DISCRETIZATION
#define TIFALIBS_EDH_DISCRETIZATION

#include "../util/traits.hpp"

namespace tifa_libs {

template <iterable_c T = vec<int>>
constexpr T uniq(T const &v) {
  T _ = v;
  std::sort(_.begin(), _.end());
  _.erase(std::unique(_.begin(), _.end()), _.end());
  return _;
}
template <iterable_c T = vec<int>>
constexpr std::pair<T, vec<u32>> gen_id(T const &v) {
  T _ = uniq(v);
  vec<u32> _1;
  for (u32 i = 0; i < v.size(); ++i) _1.push_back(u32(std::lower_bound(_.begin(), _.end(), v[i]) - _.begin()));
  return {_, _1};
}

}  // namespace tifa_libs

#endif