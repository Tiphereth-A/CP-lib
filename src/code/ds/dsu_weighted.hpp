#ifndef TIFA_LIBS_DS_DSU_WEIGHTED
#define TIFA_LIBS_DS_DSU_WEIGHTED

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_weighted {
  vec<i32> p;
  vec<i64> dep;

 public:
  explicit dsu_weighted(u32 n) : p(n, -1), dep(n) {}

  i32 find(u32 x) {
    if (p[x] < 0) return (i32)x;
    auto _ = find((u32)p[x]);
    dep[x] += dep[(u32)p[x]];
    return p[x] = _;
  }
  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  i64 depth(u32 x) { return find(x), dep[x]; }
  bool same(u32 x, u32 y) { return find(x) == find(y); }
  bool merge(u32 x, u32 y, i64 d = 1) {
    (d += depth(y) - depth(x)) *= -1;
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) {
      std::swap(x, y);
      d *= -1;
    }
    p[x] += p[y];
    p[y] = (i32)x;
    dep[y] = d;
    return true;
  }
};

}  // namespace tifa_libs::ds

#endif