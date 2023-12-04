#ifndef TIFALIBS_DS_FENWICK
#define TIFALIBS_DS_FENWICK

#include "../bit/bceil.hpp"
#include "../bit/lowbit.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick {
  vec<T> a;

 public:
  //! [1, sz)
  explicit constexpr fenwick(u32 sz) : a(sz) { assert(sz > 1); }

  //! [pos, sz), pos > 0
  constexpr void add(u32 pos, T const &x) {
    if (!pos) return;
    for (; pos < a.size(); pos += bit::lowbit(pos)) a[pos] += x;
  }
  //! [1, pos)
  constexpr T sum(u32 pos) {
    T ret = 0;
    for (pos = std::min(pos, (u32)a.size() - 1); pos; pos -= bit::lowbit(pos)) ret += a[pos];
    return ret;
  }
  //! for weighted fenwick
  constexpr T kth_max(u32 k) {
    u32 now = 0, n = bit::bceil(a.size());
    T s{};
    while (n) {
      u32 to = now | n;
      if (to >= a.size()) continue;
      if (T x = s + a[to]; x < k) {
        now = to;
        s = x;
      }
    }
    return now + 1;
  }
};

}  // namespace tifa_libs::ds

#endif