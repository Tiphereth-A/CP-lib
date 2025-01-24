#ifndef TIFALIBS_DS_DSU_WEIGHTED
#define TIFALIBS_DS_DSU_WEIGHTED

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_weighted {
  veci p;
  vecii dep;

 public:
  CEXPE dsu_weighted(u32 n) NE : p(n, -1), dep(n) {}

  CEXP i32 find(u32 x) NE {
    if (p[x] < 0) return (i32)x;
    const auto _ = find((u32)p[x]);
    dep[x] += dep[(u32)p[x]], p[x] = _;
    return _;
  }
  CEXP u32 size(u32 x) NE { return (u32)-p[(u32)find(x)]; }
  CEXP i64 depth(u32 x) NE {
    find(x);
    return dep[x];
  }
  CEXP bool same(u32 x, u32 y) NE { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y, i64 d = 1) NE {
    (d += depth(y) - depth(x)) *= -1;
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) swap(x, y), d *= -1;
    p[x] += p[y], p[y] = (i32)x, dep[y] = d;
    return true;
  }
};

}  // namespace tifa_libs::ds

#endif