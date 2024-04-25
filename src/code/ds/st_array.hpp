#ifndef TIFALIBS_DS_ST_ARRAY
#define TIFALIBS_DS_ST_ARRAY

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T)>
class st_array {
  vvec<T> st;

 public:
  explicit CEXP st_array(vec<T> CR a) : st((u32)std::bit_width(a.size()), vec<T>(a.size())) {
    u32 n = a.size();
    st[0] = a;
    for (u32 j = 1, m = (u32)std::bit_width(n); j < m; ++j)
      flt_ (u32, i, 0, n) st[j][i] = op(st[j - 1][i], st[j - 1][min(n - 1, i + (1 << (j - 1)))]);
  }

  //! [l, r]
  CEXP T query(u32 l, u32 r) const {
    u32 k = (u32)(std::bit_width(1 + r - l) - 1);
    return op(st[k][l], st[k][r + 1 - (1 << k)]);
  }
};

}  // namespace tifa_libs::ds

#endif