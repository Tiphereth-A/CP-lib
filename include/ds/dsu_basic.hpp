#ifndef TIFALIBS_DS_DSU_BASIC
#define TIFALIBS_DS_DSU_BASIC

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <bool union_by_size = true>
class dsu_basic {
  veci p;

 public:
  CEXPE dsu_basic(u32 sz) NE : p(sz, -1) {}

  CEXP i32 find(u32 x) NE { retif_((p[x] < 0), (i32)x, p[x] = find((u32)p[x])); }
  CEXP u32 size() CNE { return (u32)p.size(); }
  CEXP u32 size(u32 x) NE { return (u32)-p[(u32)find(x)]; }
  CEXP bool same(u32 x, u32 y) NE { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y) NE {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if CEXP (union_by_size)
      if (p[x] > p[y]) swap(x, y);
    p[x] += p[y], p[y] = (i32)x;
    return true;
  }
};

}  // namespace tifa_libs::ds

#endif