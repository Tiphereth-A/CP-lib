#ifndef TIFA_LIBS_DS_DSU_WEIGHTED
#define TIFA_LIBS_DS_DSU_WEIGHTED

#include "../util/util.hpp"

namespace tifa_libs::ds {

struct dsu_weighted {
  struct node {
    size_t fa, dep, sz;
    explicit node(size_t fa) : fa(fa), dep(0), sz(1) {}
  };

  vec<node> data;

  explicit dsu_weighted(size_t n) : data(n) {
    for (size_t i = 0; i < n; ++i) data[i].fa = i;
  }

  size_t find(size_t x) {
    if (x == data[x].fa) return x;
    size_t fx = find(data[x].fa);
    data[x].dep += data[data[x].fa].dep;
    return data[x].fa = fx;
  }
  void merge(size_t x, size_t y) {
    if (data[x = find(x)].sz > data[y = find(y)].sz) std::swap(x, y);
    data[x].dep += data[y].sz;
    data[y].sz += data[x].sz;
    data[x].sz = 0;
    data[x].fa = y;
  }
  bool in_same_group(size_t x, size_t y) { return find(x) == find(y); }
};

}  // namespace tifa_libs::ds

#endif