#ifndef TIFALIBS_DS_ST_ARRAY
#define TIFALIBS_DS_ST_ARRAY

#include "../bit/log2.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T)>
class st_array {
  vvec<T> st;

 public:
  explicit st_array(vec<T> const &a) : st((u32)bit::log2(a.size()) + 1, vec<T>(a.size())) {
    u32 n = a.size();
    st[0] = a;
    for (u32 j = 1, m = (u32)bit::log2(n) + 1; j < m; ++j)
      for (u32 i = 0; i < n; ++i) st[j][i] = op(st[j - 1][i], st[j - 1][std::min(n - 1, i + (1 << (j - 1)))]);
  }

  //! [l, r]
  T query(u32 l, u32 r) const {
    u32 k = (u32)bit::log2(1 + r - l);
    return op(st[k][l], st[k][r + 1 - (1 << k)]);
  }
};

}  // namespace tifa_libs::ds

#endif