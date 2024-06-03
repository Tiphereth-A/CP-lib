#ifndef TIFALIBS_DS_ST_ARRAY
#define TIFALIBS_DS_ST_ARRAY

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T), T (*e)()>
class st_array {
  vvec<T> st;

 public:
  explicit CEXP st_array() {}
  explicit CEXP st_array(spn<T> a) { reset(a); }

  CEXP void reset(spn<T> a) {
    const u32 n = (u32)a.size();
    st = vvec<T>((u32)std::bit_width(n), vec<T>(n, e()));
    std::ranges::copy(a, st[0].begin());
    flt_ (u32, j, 1, (u32)std::bit_width(n))
      flt_ (u32, i, 0, n) st[j][i] = op(st[j - 1][i], st[j - 1][min(n - 1, i + (1 << (j - 1)))]);
  }
  CEXP u32 height() const { return (u32)st.size(); }
  CEXP u32 size() const { return (u32)st[0].size(); }
  CEXP T query(u32 l = 0) const { return query(l, size()); }
  CEXP T query(u32 l, u32 r) const {
    if (r <= l) return e();
    const u32 k = (u32)(std::bit_width(r - l) - 1);
    return op(st[k][l], st[k][r - (1 << k)]);
  }
};

}  // namespace tifa_libs::ds

#endif