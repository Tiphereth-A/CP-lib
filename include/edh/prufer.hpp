#ifndef TIFALIBS_EDH_PRUFER
#define TIFALIBS_EDH_PRUFER

#include "../util/alias_others.hpp"

namespace tifa_libs {

//! vertex ID starts at 1
//! tree root = n
// father ID of i is fa[i], fa[0] = 0
CEXP vecu prufer(spnu fa) NE {
  const u32 n = (u32)fa.size();
  vecu deg(n + 1);
  flt_ (u32, i, 1, n) ++deg[fa[i]];
  vecu code(n);
  for (u32 i = 1, j = 1; i <= n - 2; ++i, ++j) {
    while (deg[j]) ++j;
    code[i] = fa[j];
    while (i <= n - 2 && !--deg[code[i]] && code[i] < j) code[i + 1] = fa[code[i]], ++i;
  }
  code.pop_back();
  return code;
}

}  // namespace tifa_libs

#endif