#ifndef TIFALIBS_OPT_HOVERLINE
#define TIFALIBS_OPT_HOVERLINE

#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

// @return {l, r} s.t. $\forall x\in[l_i,r_i],~a_x\geq a_i$, $l_i$ leftmost, $r_i$ rightmost
template <class T, class C = std::less<T>>
CEXP ptt<vecu> hoverline(vec<T> CR a, C&& comp = C{}) NE {
  if (a.empty()) return {{}, {}};
  vecu l(a.size());
  std::iota(l.begin(), l.end(), 0_u32);
  auto r = l;
  flt_ (u32, i, 0, (u32)a.size())
    while (l[i] && !comp(a[l[i] - 1], a[i])) l[i] = l[l[i] - 1];
  for (u32 i = (u32)a.size() - 2; ~i; --i)
    while ((i32)r[i] < (i32)a.size() - 1 && !comp(a[r[i] + 1], a[i])) r[i] = r[r[i] + 1];
  return {l, r};
}

}  // namespace tifa_libs::opt

#endif