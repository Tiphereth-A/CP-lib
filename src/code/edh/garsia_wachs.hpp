#ifndef TIFALIBS_EDH_GARSIA_WACHS
#define TIFALIBS_EDH_GARSIA_WACHS

#include "../util/alias_others.hpp"

namespace tifa_libs {

//! v.front() == inf && v.back() == inf
template <class T, class F>
requires requires(F f, u32 m0, u32 m1, u32 r, u32 j, T a) { f(m0, m1, r, j, a); }
void garsia_wachs(vec<T>& v, F&& f) NE {
  u32 n = (u32)v.size() - 2, cnt = n + 1, k, j;
  vecu idx(n + 1);
  std::iota(idx.begin(), idx.end(), 0);
  while (n-- > 1) {
    for (k = 1; k <= n; ++k)
      if (v[k - 1] < v[k + 1]) break;
    T a = v[k] + v[k - 1];
    for (j = k - 1; ~j; --j)
      if (v[j] > v[k] + v[k - 1]) break;
    v.erase(v.begin() + k - 1), v.erase(v.begin() + k - 1), v.insert(v.begin() + j + 1, a);
    f(idx[k - 1], idx[k], ++cnt, j + 1, a);
    idx.erase(idx.begin() + k - 1), idx.erase(idx.begin() + k - 1);
    idx.insert(idx.begin() + j + 1, cnt);
  }
}

}  // namespace tifa_libs

#endif