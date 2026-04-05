#pragma once

#include "../../util/alias/others/lib.hpp"

namespace tifa_libs {

inline strn bwt_inv(strnv t) NE {
  vecu nxt(t.size());
  std::iota(begin(nxt), end(nxt), 0);
  stable_sort(nxt, [&t](u32 a, u32 b) NE { return t[a] < t[b]; });
  strn ret{t[nxt[0]]};
  for (u32 i = nxt[0]; i;) ret += t[i = nxt[i]];
  return ret;
}

}  // namespace tifa_libs
