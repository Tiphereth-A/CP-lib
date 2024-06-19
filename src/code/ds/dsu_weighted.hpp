#ifndef TIFALIBS_DS_DSU_WEIGHTED
#define TIFALIBS_DS_DSU_WEIGHTED

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_weighted {
  veci p;
  vecii dep;

 public:
  CEXPE dsu_weighted(u32 n) : p(n, -1), dep(n) {}

  CEXP i32 find(u32 x) {
    if (p[x] < 0) return (i32)x;
    const auto _ = find((u32)p[x]);
    return dep[x] += dep[(u32)p[x]], p[x] = _;
  }
  CEXP u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  CEXP i64 depth(u32 x) { return find(x), dep[x]; }
  CEXP bool same(u32 x, u32 y) { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y, i64 d = 1) {
    if ((d += depth(y) - depth(x)) *= -1; (x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) swap(x, y), d *= -1;
    return p[x] += p[y], p[y] = (i32)x, dep[y] = d, true;
  }
};

}  // namespace tifa_libs::ds

#endif