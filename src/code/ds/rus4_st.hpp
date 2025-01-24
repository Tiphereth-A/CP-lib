#ifndef TIFALIBS_DS_RUS4_ST
#define TIFALIBS_DS_RUS4_ST

#include "st_array.hpp"

namespace tifa_libs::ds {

template <class T, auto op>
class rus4_st {
  u32 sz, B;
  st_array<T, op> st;
  vec<st_array<T, op>> d;

 public:
  CEXPE rus4_st(spn<T> a) NE : rus4_st(a, (u32)std::bit_width(a.size())) {}
  CEXP rus4_st(spn<T> a, u32 block_size) NE { reset(a, block_size); }

  CEXP void reset(spn<T> a, u32 block_size) NE {
    sz = (u32)a.size(), B = block_size, d.clear();
    vec<T> ds;
    for (u32 l = 0; l < sz; l += B) {
      d.emplace_back(a.subspan(l, l + B > sz ? std::dynamic_extent : B));
      ds.push_back(d.back().query());
    }
    st.reset(ds);
  }
  CEXP u32 CR block_size() CNE { return B; }
  CEXP u32 CR size() CNE { return sz; }
  CEXP T query(u32 l = 0) CNE { return query(l, size()); }
  //! 0-indexed, [l, r)
  CEXP T query(u32 l, u32 r) CNE {
    assert(l < r && r <= size());
    if (u32 L = l / B, R = r / B; L == R) return d[L].query(l % B, r % B);
    else {
      T ret = d[L].query(l % B);
      if (L + 1 != R) ret = op(ret, st.query(L + 1, R));
      if (r % B) ret = op(ret, d[R].query(0, r % B));
      return ret;
    }
  }
};

}  // namespace tifa_libs::ds

#endif