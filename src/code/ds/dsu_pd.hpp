#ifndef TIFA_LIBS_DS_DSU_PD
#define TIFA_LIBS_DS_DSU_PD

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_pd {
  vec<i32> p;
  vec<std::pair<u32, i32>> joins;

 public:
  explicit dsu_pd(size_t sz) : p(sz, -1) {}

  i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }
  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }
  u32 time() { return (u32)joins.size(); }
  bool same(u32 x, u32 y) { return find(x) == find(y); }
  bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) std::swap(x, y);
    joins.emplace_back(y, p[y]);
    p[x] += p[y];
    p[y] = (i32)x;
    return true;
  }
  void rollback(u32 t) {
    while (joins.size() > t) {
      auto [i, pi] = joins.back();
      joins.pop_back();
      assert(p[(u32)p[i]] < 0);
      p[(u32)p[i]] -= pi;
      p[i] = pi;
    }
  }
};

}  // namespace tifa_libs::ds

#endif