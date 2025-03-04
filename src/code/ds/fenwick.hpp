#ifndef TIFALIBS_DS_FENWICK
#define TIFALIBS_DS_FENWICK

#include "../bit/lowbit.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick {
  vec<T> a;

 public:
  //! [1, sz)
  CEXPE fenwick(u32 sz) NE : a(sz) { assert(sz > 1); }
  //! [1, sz)
  CEXP fenwick(spn<T> data) NE : fenwick((u32)data.size()) {
    const u32 sz = (u32)data.size();
    flt_ (u32, i, 1, sz) {
      a[i] += data[i];
      if (u32 j = i + bit::lowbit(i); j < sz) a[j] += a[i];
    }
  }

  //! [pos, sz), pos > 0
  CEXP void add(u32 pos, cT_(T) x) NE {
    if (!pos) return;
    for (; pos < a.size(); pos += bit::lowbit(pos)) a[pos] += x;
  }
  //! [l, r], l > 0
  CEXP void add(u32 l, u32 r, cT_(T) x) NE { add(l, x), add(r + 1, -x); }
  //! [1, pos]
  CEXP T sum(u32 pos) NE {
    T ret = 0;
    for (pos = min(pos, (u32)a.size() - 1); pos; pos -= bit::lowbit(pos)) ret += a[pos];
    return ret;
  }
  //! [l, r]
  CEXP T sum(u32 l, u32 r) NE { return sum(r) - sum(l - 1); }
  //! for weighted fenwick
  CEXP T kth_max(u32 k) NE {
    const u32 n = std::bit_ceil(a.size());
    u32 now = 0;
    T s{};
    while (n)
      if (const u32 to = now | n; to >= a.size()) continue;
      else if (T x = s + a[to]; x < k) now = to, s = x;
    return now + 1;
  }
};

}  // namespace tifa_libs::ds

#endif