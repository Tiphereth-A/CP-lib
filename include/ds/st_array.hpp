#ifndef TIFALIBS_DS_ST_ARRAY
#define TIFALIBS_DS_ST_ARRAY

#include "../util/alias_others.hpp"

namespace tifa_libs::ds {

template <class T, auto op>
requires std::same_as<std::remove_cvref_t<decltype(op(T(), T()))>, T>
class st_array {
  vvec<T> st;

 public:
  CEXPE st_array() = default;
  CEXPE st_array(spn<T> a) NE { reset(a); }

  CEXP void reset(spn<T> a) NE {
    const u32 n = (u32)a.size(), lbn = (u32)std::bit_width(n);
    st = vvec<T>(lbn, vec<T>(n)), copy(a, st[0].begin());
    flt_ (u32, j, 1, lbn)
      flt_ (u32, i, 0, n) st[j][i] = op(st[j - 1][i], st[j - 1][(u32)max(0, i32(i - (1 << (j - 1))))]);
  }
  CEXP void push_back(cT_(T) x) NE {
    if (!height()) {
      st = vvec<T>{{x}};
      return;
    }
    const u32 n = size() + 1, lbn = (u32)std::bit_width(n);
    if (st[0].push_back(x); std::has_single_bit(n)) {
      st.emplace_back(n - 1);
      flt_ (u32, i, 0, n - 1) st.back()[i] = op(st[lbn - 2][i], st[lbn - 2][(u32)max(0, i32(i - (1 << (lbn - 2))))]);
    }
    flt_ (u32, j, 1, lbn) st[j].push_back(op(st[j - 1].back(), st[j - 1][n - 1 - (1 << (j - 1))]));
  }
  CEXP u32 height() CNE { return (u32)st.size(); }
  CEXP u32 size() CNE { return height() ? (u32)st[0].size() : 0; }
  CEXP T query(u32 l = 0) CNE { return query(l, size()); }
  //! 0-indexed, [l, r)
  CEXP T query(u32 l, u32 r) CNE {
    assert(l < r && r <= size());
    const u32 k = (u32)(std::bit_width(r - l) - 1);
    return op(st[k][l + (1 << k) - 1], st[k][r - 1]);
  }
};

}  // namespace tifa_libs::ds

#endif