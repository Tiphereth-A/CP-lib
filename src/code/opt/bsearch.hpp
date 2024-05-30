#ifndef TIFALIBS_OPT_BSEARCH
#define TIFALIBS_OPT_BSEARCH

#include "../util/util.hpp"

namespace tifa_libs::opt {

template <class F>
requires requires(F pred, u32 x) {
  { pred(x) } -> std::same_as<bool>;
}
CEXP u32 bsearch(F&& pred) {
  u32 ok = 0, ng = 1;
  while (pred(ng)) ng *= 2;
  while (abs(i32(ok - ng)) > 1) {
    const u32 mid = ok + (ng - ok) / 2;
    (pred(mid) ? ok : ng) = mid;
  }
  return ok;
}

}  // namespace tifa_libs::opt

#endif