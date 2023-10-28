#ifndef TIFA_LIBS_DS_FENWICK
#define TIFA_LIBS_DS_FENWICK

#include "../bit/bceil.hpp"
#include "../bit/lowbit.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick {
  vec<T> a;

 public:
  //! [1, sz)
  explicit constexpr fenwick(usz sz) : a(sz) { assert(sz > 1); }
  //! [pos, sz), pos > 0
  constexpr void add(usz pos, T const &x) {
    if (!pos) return;
    for (; pos < a.size(); pos += bit::lowbit(pos)) a[pos] += x;
  }
  //! [1, pos)
  constexpr T sum(usz pos) {
    T ret = 0;
    for (pos = std::min(pos, a.size() - 1); pos; pos -= bit::lowbit(pos)) ret += a[pos];
    return ret;
  }
  //! for weighted fenwick
  constexpr T kth_max(usz k) {
    usz now = 0, n = bit::bceil(a.size());
    T s{};
    while (n) {
      usz to = now | n;
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