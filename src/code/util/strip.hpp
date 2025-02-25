#ifndef TIFALIBS_UTIL_STRIP
#define TIFALIBS_UTIL_STRIP

#include "util.hpp"

namespace tifa_libs {

// pred(x) == true  ==>  drop
template <range R, class F>
CEXP R strip(R CR range, F&& pred) NE { return {find_if_not(range, std::forward<F>(pred)), std::next(find_if_not(range.rbegin(), range.rend(), std::forward<F>(pred)).base())}; }
// pred(x) == true  ==>  drop
template <range R, class F>
CEXP R lstrip(R CR range, F&& pred) NE { return {find_if_not(range, std::forward<F>(pred)), range.end()}; }
// pred(x) == true  ==>  drop
template <range R, class F>
CEXP R rstrip(R CR range, F&& pred) NE { return {range.begin(), std::next(find_if_not(range.rbegin(), range.rend(), std::forward<F>(pred)).base())}; }

}  // namespace tifa_libs

#endif