#ifndef TIFA_LIBS_DS_ST_ARRAY_2D
#define TIFA_LIBS_DS_ST_ARRAY_2D

#include "../bit/log2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, class F>
class st_array_2d {
  vvvec<T> st;
  F f;

 public:
  st_array_2d(vvec<T> const &a, F func) : st((size_t)bit::log2(std::max(a.size(), a[0].size())) + 1, vvec<T>(a.size(), vec<T>(a[0].size()))), f(func) {
    size_t n = a.size(), n2 = a[0].size();
    st[0] = a;
    for (size_t j = 1, m = (size_t)bit::log2(std::max(n, n2)) + 1; j < m; ++j)
      for (size_t i = 0, i_; i < n; ++i) {
        i_ = std::min(n - 1, i + (1 << (j - 1)));
        for (size_t k = 0, k_; k < n2; ++k) {
          k_ = std::min(n2 - 1, k + (1 << (j - 1)));
          st[j][i][k] = f(f(st[j - 1][i][k], st[j - 1][i_][k]), f(st[j - 1][i][k_], st[j - 1][i_][k_]));
        }
      }
  }
  //! [x, x + l] * [y, y + l]
  T query(size_t x, size_t y, size_t l) const {
    size_t k = (size_t)bit::log2(l + 1), ofs = (1 << k) - 1;
    return f(f(st[k][x][y], st[k][x + l - ofs][y]), f(st[k][x][y + l - ofs], st[k][x + l - ofs][y + l - ofs]));
  }
};

}  // namespace tifa_libs::ds

#endif