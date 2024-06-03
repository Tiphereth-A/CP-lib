#ifndef TIFALIBS_DS_RUS4_ST
#define TIFALIBS_DS_RUS4_ST

#include "st_array.hpp"

namespace tifa_libs::ds {

template <class T, T (*op)(T, T), T (*e)()>
class rus4_st {
  u32 sz, B;
  st_array<T, op, e> st;
  vec<st_array<T, op, e>> d;

 public:
  CEXP rus4_st(spn<T> a, u32 block_size) { reset(a, block_size); }

  CEXP void reset(spn<T> a, u32 block_size) {
    sz = (u32)a.size(), B = block_size, d.clear();
    vec<T> ds;
    for (u32 l = 0; l < sz; l += B) d.emplace_back(a.subspan(l, l + B > sz ? std::dynamic_extent : B)), ds.push_back(d.back().query());
    st.reset(ds);
  }
  CEXP u32 CR block_size() const { return B; }
  CEXP u32 CR size() const { return sz; }
  //! 0-indexed
  CEXP T query(u32 l = 0) const { return query(l, sz); }
  //! 0-indexed, [l, r]
  CEXP T query(u32 l, u32 r) const {
    if (r <= l) return e();
    if (u32 L = l / B, R = r / B; L == R) return d[L].query(l % B, r % B);
    else return op(op(d[L].query(l % B), st.query(L + 1, R)), d[R].query(0, r % B));
  }
};

}  // namespace tifa_libs::ds

#endif