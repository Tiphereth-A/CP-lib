#ifndef TIFALIBS_DS_FENWICK
#define TIFALIBS_DS_FENWICK

#include "../bit/lowbit.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick {
  vec<T> a;

 public:
  //! [1, sz)
  explicit CEXP fenwick(u32 sz) : a(sz) { assert(sz > 1); }

  //! [pos, sz), pos > 0
  CEXP void add(u32 pos, cT_(T) x) {
    if (!pos) return;
    for (; pos < a.size(); pos += bit::lowbit(pos)) a[pos] += x;
  }
  //! [l, r], l > 0
  CEXP void add(u32 l, u32 r, cT_(T) x) { add(l, x), add(r + 1, -x); }
  //! [1, pos]
  CEXP T sum(u32 pos) {
    T ret = 0;
    for (pos = min(pos, (u32)a.size() - 1); pos; pos -= bit::lowbit(pos)) ret += a[pos];
    return ret;
  }
  //! [l, r]
  CEXP T sum(u32 l, u32 r) { return sum(r) - sum(l - 1); }
  //! for weighted fenwick
  CEXP T kth_max(u32 k) {
    const u32 n = std::bit_ceil(a.size());
    u32 now = 0;
    T s{};
    while (n) {
      const u32 to = now | n;
      if (to >= a.size()) continue;
      if (T x = s + a[to]; x < k) now = to, s = x;
    }
    return now + 1;
  }
};

}  // namespace tifa_libs::ds

#endif