#ifndef TIFA_LIBS_MATH_LEQS_SOLVER
#define TIFA_LIBS_MATH_LEQS_SOLVER

#include "../util/util.hpp"

#include "../util/abs_constexpr.hpp"
#include "mat.hpp"
#include "mat_merge_lr.hpp"
#include "mat_merge_ud.hpp"

namespace tifa_libs::math {

template <class T>
class LeqsSolver {
  using mat = matrix<T>;

  mat argmat;
  size_t rk;
  std::vector<size_t> fe_list;

public:
  // using guass method to solve linear equations Ax=b
  template <class Ge>
  LeqsSolver(mat const &A, mat const &b, Ge ge):
    argmat(merge_lr(A, b)) {
    assert(b.col_size() == 1);
    rk = (u64)abs(ge(argmat, true));
    argmat = argmat.submat(0, rk, 0, argmat.col_size());
    if (rk + 1 < argmat.col_size()) {
      argmat = merge_ud(argmat, mat(argmat.col_size() - rk - 1, argmat.col_size()));
      for (size_t i = 0, j = rk; i < argmat.row_size(); ++i) {
        if (argmat(i, i) != 0) continue;
        if (j < argmat.row_size()) argmat.swap_row(i, j++);
        fe_list.push_back(i);
        argmat(i, i) = 1;
      }
      for (auto i : fe_list) argmat.col(i) /= argmat.cdiag(0);
    }
    argmat.col(argmat.col_size() - 1) /= argmat.cdiag(0);
    argmat.diag(0) = 1;
  }

  constexpr size_t rank() const { return rk; }
  // @return -1 of no solution, else number of free elements
  constexpr ptrdiff_t fe_cnt() const { return (ptrdiff_t)(argmat.col_size() - rk) - 1; }
  // values of free elements is 0
  mat solution() const { return argmat.submat(0, argmat.row_size(), argmat.col_size() - 1, argmat.col_size()); }
  // only for infinite solution, need set values of free elements
  template <class Ge>
  mat solution(mat const &fe_val, Ge ge) const {
    const size_t fec = (size_t)fe_cnt();
    assert(fe_val.col_size() == 1 && fe_val.row_size() == fec);
    mat _ = argmat;
    for (size_t i = 0; i < fec; ++i) _(fe_list[i], _.col_size() - 1) = fe_val(i, 0);
    ge(_, true);
    return _.submat(0, _.row_size(), _.col_size() - 1, _.col_size()) - solution();
  }
};

}  // namespace tifa_libs::math

#endif