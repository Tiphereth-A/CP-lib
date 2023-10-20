#ifndef TIFA_LIBS_UTIL_DISCRETIZATION
#define TIFA_LIBS_UTIL_DISCRETIZATION

#include "util.hpp"

namespace tifa_libs {

template <class T = vec<int>>
T uniq(T const &v) {
  T _ = v;
  std::sort(_.begin(), _.end());
  _.erase(std::unique(_.begin(), _.end()), _.end());
  return _;
}
template <class T = vec<int>>
std::pair<T, vec<usz>> gen_id(T const &v) {
  T _ = uniq(v);
  vec<usz> _1;
  for (usz i = 0; i < v.size(); ++i) _1.push_back(usz(std::lower_bound(_.begin(), _.end(), v[i]) - _.begin()));
  return {_, _1};
}

}  // namespace tifa_libs

#endif