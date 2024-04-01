#ifndef TIFALIBS_CONV_LIS
#define TIFALIBS_CONV_LIS

#include "../util/util.hpp"

namespace tifa_libs::opt {

// @return INDEX of LIS in @a
template <class T, class C = std::less<T>>
constexpr vec<u32> lis(vec<T> const& a, T inf, C&& comp = C{}) {
  vec<T> f{inf};
  vec<u32> g;
  for (auto i : a) {
    auto it = std::lower_bound(f.begin(), f.end(), i, comp);
    g.push_back(u32(it - f.begin()));
    if (it == f.end()) f.push_back(i);
    else *it = i;
  }
  T val = inf;
  vec<u32> ret;
  for (usz i = g.size() - 1, now = f.size() - 1; ~i; --i)
    if (g[i] == now && val > a[i]) {
      ret.push_back((u32)i);
      --now;
      val = a[i];
    }
  std::reverse(ret.begin(), ret.end());
  return ret;
}

}  // namespace tifa_libs::opt

#endif