#ifndef TIFALIBS_DS_DSU_PD
#define TIFALIBS_DS_DSU_PD

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_pd {
  veci p;
  vecp<u32, i32> edges;

 public:
  CEXPE dsu_pd(u32 sz) : p(sz, -1) {}

  CEXP i32 find(u32 x) { return p[x] < 0 ? (i32)x : find((u32)p[x]); }
  CEXP u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  CEXP u32 time() { return (u32)edges.size(); }
  CEXP bool same(u32 x, u32 y) { return find(x) == find(y); }
  CEXP bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) swap(x, y);
    return edges.emplace_back(y, p[y]), p[x] += p[y], p[y] = (i32)x, true;
  }
  CEXP void rollback(u32 t) {
    while (edges.size() > t) {
      const auto [i, pi] = edges.back();
      edges.pop_back(), assert(p[(u32)p[i]] < 0), p[(u32)p[i]] -= pi, p[i] = pi;
    }
  }
};

}  // namespace tifa_libs::ds

#endif