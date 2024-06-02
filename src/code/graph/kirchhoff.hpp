#ifndef TIFALIBS_GRAPH_KIRCHHOFF
#define TIFALIBS_GRAPH_KIRCHHOFF

#include "../lalg/det_mat.hpp"
#include "../lalg/mat.hpp"
#include "amat.hpp"

namespace tifa_libs::graph {

template <bool inner, class T, bool with_deg, class Ge>
requires requires(Ge ge, math::matrix<T> A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP T kirchhoff(amat<T, with_deg> CR g, u32 r, Ge &&ge) {
  const u32 n = (u32)g.g.size();
  if (n <= 1) return n;
  math::matrix<T> mat(n - 1, n - 1);
  flt_ (u32, i, 0, n)
    flt_ (u32, j, 0, n)
      if (i != j) {
        auto _ = g.g[i][j];
        if (i != r && j != r) mat(i - (i > r), j - (j > r)) -= _;
        if CEXP (inner) {
          if (j != r) mat(j - (j > r), j - (j > r)) += _;
        } else if (i != r) mat(i - (i > r), i - (i > r)) += _;
      }
  return math::det(mat, ge);
}

}  // namespace tifa_libs::graph

#endif