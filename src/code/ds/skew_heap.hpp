#ifndef TIFALIBS_DS_SKEW_HEAP
#define TIFALIBS_DS_SKEW_HEAP

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class C = std::less<T>>
class SkewHeap {
  static constexpr C comp_{};
  struct YYZ {
    T k, lz;
    u32 l, r, idx;
    YYZ() {}
    YYZ(T const &key, u32 i = -1_u32) : k(key), lz(0), l(-1_u32), r(-1_u32), idx(i) {}
  };

  constexpr bool comp(u32 idxl, u32 idxr) const { return comp_(weight(idxl), weight(idxr)); }
  constexpr void pd(u32 idx) {
    if (d[idx].lz == 0) return;
    if (~d[idx].l) d[d[idx].l].lz += d[idx].lz;
    if (~d[idx].r) d[d[idx].r].lz += d[idx].lz;
    d[idx].k += d[idx].lz;
    d[idx].lz = 0;
  }

 public:
  vec<YYZ> d;

  constexpr T weight(u32 idx) const { return d[idx].k + d[idx].lz; }
  constexpr u32 newheap(T const &key, u32 idx = -1_u32) {
    d.emplace_back(key, idx);
    return u32(d.size() - 1);
  }
  constexpr u32 merge(u32 x, u32 y) {
    if (!~x || !~y) return ~(x ^ y);
    if (!comp(x, y)) std::swap(x, y);
    pd(x), std::swap(d[x].l, d[x].r = merge(d[x].r, y));
    return x;
  }
  constexpr void apply(u32 x, T const &lz) { d[x].lz += lz, pd(x); }
  constexpr u32 push(u32 x, T const &key, u32 idx = -1_u32) { return merge(x, newheap(key, idx)); }
  constexpr u32 pop(u32 x) {
    pd(x);
    return merge(d[x].l, d[x].r);
  }
};

}  // namespace tifa_libs::ds

#endif