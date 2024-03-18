#ifndef TIFALIBS_EDH_DISCRETIZATION
#define TIFALIBS_EDH_DISCRETIZATION

#include "../util/util.hpp"

namespace tifa_libs {

template <class T = vec<int>>
constexpr T uniq(T const &v) {
  T _ = v;
  std::sort(_.begin(), _.end());
  _.erase(std::unique(_.begin(), _.end()), _.end());
  return _;
}
template <class T = vec<int>>
constexpr std::pair<T, vec<usz>> gen_id(T const &v) {
  T _ = uniq(v);
  vec<usz> _1;
  for (usz i = 0; i < v.size(); ++i) _1.push_back(usz(std::lower_bound(_.begin(), _.end(), v[i]) - _.begin()));
  return {_, _1};
}

}  // namespace tifa_libs

#endif