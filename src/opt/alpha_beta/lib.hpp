#pragma once

#include "../../tree/ds/lib.hpp"
#include "../../util/traits/math/lib.hpp"

namespace tifa_libs {

template <arithm_c T>
CEXP T alpha_beta(tree_c auto CR tr, vec<T> CR v_weight) NE {
  auto dfs = [&](auto&& dfs, u32 u, T a, T b, bool is_max = true) NE -> T {
    if (tr[u].empty()) return v_weight[u];
    if (is_max) {
      flt_ (u32, i, 0, tr.vsize())
        if ((a = max(a, dfs(dfs, i, a, b, !is_max))) >= b) break;
      return a;
    } else {
      flt_ (u32, i, 0, tr.vsize())
        if ((b = min(b, dfs(dfs, i, a, b, !is_max))) <= a) break;
      return b;
    }
  };
  return dfs(dfs, tr.root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

}  // namespace tifa_libs
