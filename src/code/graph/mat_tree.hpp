#ifndef TIFALIBS_GRAPH_MAT_TREE
#define TIFALIBS_GRAPH_MAT_TREE

#include "../lalg/mat.hpp"
#include "../lalg/mat_det.hpp"
#include "amat.hpp"

namespace tifa_libs::graph {

// @return sum of spanning trees of undirected graph g
template <class T, class Ge>
requires requires(Ge ge, math::matrix<T> A, bool clear_u) {
  { ge(A, clear_u) } -> std::same_as<i32>;
}
constexpr T mat_tree(amat<T> const &g, Ge &&ge) {
  u32 n = g.g.size();
  math::matrix<T> mat(n - 1, n - 1);
  for (u32 i = 0; i < n; ++i)
    for (u32 j = i + 1; j < n; ++j) {
      auto _ = g.g[i][j];
      mat(i, i) += _;
      if (j != n - 1) mat(j, j) += _, mat(i, j) -= _, mat(j, i) -= _;
    }
  return math::det(mat, ge);
}

}  // namespace tifa_libs::graph

#endif