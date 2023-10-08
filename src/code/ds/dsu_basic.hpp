#ifndef TIFA_LIBS_DS_DSU_BASIC
#define TIFA_LIBS_DS_DSU_BASIC

#include "../util/util.hpp"

namespace tifa_libs::ds {

class dsu_basic {
  vec<i32> p;

 public:
  explicit dsu_basic(size_t sz) : p(sz, -1) {}

  i32 find(size_t x) { return p[x] < 0 ? (i32)x : p[x] = find((size_t)p[x]); }
  u32 size(size_t x) { return (u32)-p[(size_t)find(x)]; }
  bool same(size_t x, size_t y) { return find(x) == find(y); }
  bool merge(size_t x, size_t y) {
    x = (size_t)find(x);
    y = (size_t)find(y);
    if (x == y) return false;
    if (p[x] > p[y]) std::swap(x, y);
    p[x] += p[y];
    p[y] = (i32)x;
    return true;
  }
};

}  // namespace tifa_libs::ds

#endif