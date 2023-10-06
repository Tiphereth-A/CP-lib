#ifndef TIFA_LIBS_DS_DSU_WEIGHTED
#define TIFA_LIBS_DS_DSU_WEIGHTED

#include "../util/util.hpp"

namespace tifa_libs::ds {

struct dsu_weighted {
  vec<u64> fa, dep, sz;

  explicit dsu_weighted(size_t n) : fa(n), dep(n), sz(n, 1) { std::iota(fa.begin(), fa.end(), 0); }

  size_t find(size_t x) {
    if (x == fa[x]) return x;
    size_t fx = find(fa[x]);
    dep[x] += dep[fa[x]];
    return fa[x] = fx;
  }
  bool in_same_group(size_t x, size_t y) { return find(x) == find(y); }
  void merge(size_t x, size_t y) {
    if (in_same_group(x = find(x), y = find(y))) return;
    if (sz[x] > sz[y]) std::swap(x, y);
    dep[x] += sz[y];
    sz[y] += sz[x];
    sz[x] = 0;
    fa[x] = y;
  }
};

}  // namespace tifa_libs::ds

#endif