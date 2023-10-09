#ifndef TIFA_LIBS_DS_LICHAO_WEIGHTED_SEGTREE
#define TIFA_LIBS_DS_LICHAO_WEIGHTED_SEGTREE

#include <cstddef>
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class weighted_segtree {
  size_t n;
  vec<T> t;
  public:   
  void add(size_t x, size_t l, size_t r, size_t pos) {
    if(l == r) t[x] += 1;
    size_t mid = l + (r - l) / 2;
    if(pos <= mid) add(x << 1, l, mid, pos);
    else add(x << 1 | 1, mid + 1, r, pos);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }
  explicit constexpr weighted_segtree(vec<T> const &a) : t(a.size() * 4), n(a.size()) { for(auto x: a) add(1, 0, n - 1, x); }
};
}  // namespace tifa_libs::ds

#endif