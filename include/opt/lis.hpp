#ifndef TIFALIBS_OPT_LIS
#define TIFALIBS_OPT_LIS

#include "../util/alias_others.hpp"

namespace tifa_libs::opt {

// @return INDEX of LIS in @a
template <class T, class C = std::less<T>>
CEXP vecu lis(vec<T> CR a, T inf = std::numeric_limits<T>::max(), C&& comp = C{}) NE {
  vec<T> f{inf};
  vecu g;
  for (auto i : a) {
    auto it = lower_bound(f, i, comp);
    g.push_back(u32(it - f.begin()));
    if (it == f.end()) f.push_back(i);
    else *it = i;
  }
  T val = inf;
  vecu ret;
  for (u32 i = u32(g.size() - 1), now = u32(f.size() - 1); ~i; --i)
    if (g[i] == now && val > a[i]) ret.push_back((u32)i), --now, val = a[i];
  reverse(ret);
  return ret;
}

}  // namespace tifa_libs::opt

#endif