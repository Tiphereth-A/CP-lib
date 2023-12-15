#ifndef TIFALIBS_DS_ST_ARRAY_2D
#define TIFALIBS_DS_ST_ARRAY_2D

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T)>
class st_array_2d {
  vvvec<T> st;

 public:
  explicit st_array_2d(vvec<T> const &a) : st((u32)std::bit_width(std::max(a.size(), a[0].size())), vvec<T>(a.size(), vec<T>(a[0].size()))) {
    u32 n = a.size(), n2 = a[0].size();
    st[0] = a;
    for (u32 j = 1, m = (u32)std::bit_width(std::max(n, n2)); j < m; ++j)
      for (u32 i = 0, i_; i < n; ++i) {
        i_ = std::min(n - 1, i + (1 << (j - 1)));
        for (u32 k = 0, k_; k < n2; ++k) {
          k_ = std::min(n2 - 1, k + (1 << (j - 1)));
          st[j][i][k] = op(op(st[j - 1][i][k], st[j - 1][i_][k]), op(st[j - 1][i][k_], st[j - 1][i_][k_]));
        }
      }
  }

  //! [x, x + l] * [y, y + l]
  T query(u32 x, u32 y, u32 l) const {
    u32 k = (u32)(std::bit_width(l + 1) - 1), ofs = (1 << k) - 1;
    return op(op(st[k][x][y], st[k][x + l - ofs][y]), op(st[k][x][y + l - ofs], st[k][x + l - ofs][y + l - ofs]));
  }
};

}  // namespace tifa_libs::ds

#endif