#pragma once

#include "../../lalg/ds/mat/lib.hpp"
#include "../../lalg/mat/det/lib.hpp"
#include "../ds/graph_c/lib.hpp"

namespace tifa_libs {

template <bool outer, graph_c G, class Ge>
requires requires(Ge ge, matrix<TPN G::Et> A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP TPN G::Et kirchhoff(G CR g, u32 r, Ge&& ge) {
  using T = TPN G::Et;
  const u32 n = g.vsize();
  retif_((n <= 1) [[unlikely]], n);
  matrix<T> mat(n - 1, n - 1);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n)
      if (i != j) {
        auto _ = g.val(i, j);
        if (i != r && j != r) mat(i - (i > r), j - (j > r)) -= _;
        if CEXP (outer) {
          if (j != r) mat(j - (j > r), j - (j > r)) += _;
        } else if (i != r) mat(i - (i > r), i - (i > r)) += _;
      }
  return det(mat, ge);
}

}  // namespace tifa_libs
