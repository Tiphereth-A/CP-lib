#ifndef TIFALIBS_TREE_PRUFER
#define TIFALIBS_TREE_PRUFER

#include "../util/util.hpp"

namespace tifa_libs::graph {

//! vertex ID starts at 1
//! tree root = n
// father ID of i is fa[i], fa[0] = 0
inline vec<u32> prufer(vec<u32> const& fa) {
  u32 n = (u32)fa.size();
  vec<u32> deg(n + 1);
  for (u32 i = 1; i < n; ++i) ++deg[fa[i]];
  vec<u32> code(n);
  for (u32 i = 1, j = 1; i <= n - 2; ++i, ++j) {
    while (deg[j]) ++j;
    code[i] = fa[j];
    while (i <= n - 2 && !--deg[code[i]] && code[i] < j) code[i + 1] = fa[code[i]], ++i;
  }
  code.pop_back();
  return code;
}

}  // namespace tifa_libs::graph

#endif