#ifndef TIFALIBS_EDH_BWT_INV
#define TIFALIBS_EDH_BWT_INV

#include "../util/util.hpp"

namespace tifa_libs {

inline strn bwt_inv(strnv t) {
  vecu nxt(t.size());
  std::iota(nxt.begin(), nxt.end(), 0);
  std::ranges::stable_sort(nxt, [&t](u32 a, u32 b) { return t[a] < t[b]; });
  strn ret{t[nxt[0]]};
  for (u32 i = nxt[0]; i;) ret += t[i = nxt[i]];
  return ret;
}

}  // namespace tifa_libs

#endif