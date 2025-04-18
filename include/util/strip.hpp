#ifndef TIFALIBS_UTIL_STRIP
#define TIFALIBS_UTIL_STRIP

#include "util.hpp"

namespace tifa_libs {

// pred(x) == true  ==>  drop
template <common_range R, class F>
CEXP auto lstrip_view(R CR range, F&& pred) NE {
  auto v = range | views::drop_while(std::forward<F>(pred));
  return subrange{v.begin(), v.end()};
}
// pred(x) == true  ==>  drop
template <common_range R, class F>
CEXP auto rstrip_view(R CR range, F&& pred) NE {
  auto v = range | views::reverse | views::drop_while(std::forward<F>(pred));
  return subrange{v.end().base(), v.begin().base()};
}
// pred(x) == true  ==>  drop
template <common_range R, class F>
CEXP auto strip_view(R CR range, F&& pred) NE {
  auto v = range | views::drop_while(std::forward<F>(pred)) | views::reverse | views::drop_while(std::forward<F>(pred));
  return subrange{v.end().base(), v.begin().base()};
}

}  // namespace tifa_libs

#endif