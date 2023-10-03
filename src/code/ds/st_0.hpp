#ifndef TIFA_LIBS_DS_STMIN
#define TIFA_LIBS_DS_STMIN

#include "../util/util.hpp"

#include "../bit/log2.hpp"

namespace tifa_libs::ds {

template <class T, class F>
class sparse_table {
  size_t n;
  vec<vec<T>> st;
  F f;

public:
  sparse_table(size_t N, vec<T> a, F func):
    n(N), st(N, vec<T>(size_t(bit::log2(N)) + 1)), f(func) {
    for (size_t i = 0; i < n; ++i) st[i][0] = a[i];
    size_t m = size_t(bit::log2(N)) + 1;
    for (size_t j = 1; j < m; ++j)
      for (size_t i = 0; i < n; ++i) {
        st[i][j] = f(st[i][j - 1], st[f(n - 1, i + (1 << (j - 1)))][j - 1]);
      }
  }
  T query(size_t l, size_t r) {
    size_t k = size_t(bit::log2(1 + r - l));
    return f(st[l][k], st[r - (1 << k) + 1][k]);
  }
};

}  // namespace tifa_libs::ds

#endif