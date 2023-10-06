#ifndef TIFA_LIBS_DS_ST_ARRAY
#define TIFA_LIBS_DS_ST_ARRAY

#include "../bit/log2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class F>
class st_array {
  vvec<T> st;
  F f;

 public:
  st_array(vec<T> const &a, F func) : st(a.size(), vec<T>(size_t(bit::log2(a.size())) + 1)), f(func) {
    size_t n = a.size();
    for (size_t i = 0; i < n; ++i) st[i][0] = a[i];
    for (size_t j = 1, m = (size_t)bit::log2(n) + 1; j < m; ++j)
      for (size_t i = 0; i < n; ++i) st[i][j] = f(st[i][j - 1], st[std::min(n - 1, i + (1 << (j - 1)))][j - 1]);
  }
  T query(size_t l, size_t r) const {
    size_t k = (size_t)bit::log2(1 + r - l);
    return f(st[l][k], st[r - (1 << k) + 1][k]);
  }
};

}  // namespace tifa_libs::ds

#endif