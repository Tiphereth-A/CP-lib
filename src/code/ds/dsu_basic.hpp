#ifndef TIFALIBS_DS_DSU_BASIC
#define TIFALIBS_DS_DSU_BASIC

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <bool union_by_size = true>
class dsu_basic {
  veci p;

 public:
  CEXPE dsu_basic(u32 sz) : p(sz, -1) {}

  CEXP i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }
  CEXP u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  CEXP bool same(u32 x, u32 y) { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if CEXP (union_by_size)
      if (p[x] > p[y]) swap(x, y);
    return p[x] += p[y], p[y] = (i32)x, true;
  }
};

}  // namespace tifa_libs::ds

#endif