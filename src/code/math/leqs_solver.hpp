#ifndef TIFA_LIBS_MATH_LEQS_SOLVER
#define TIFA_LIBS_MATH_LEQS_SOLVER

#include "../util/util.hpp"

#include "matrix.hpp"
//

namespace tifa_libs::math {

template <class T, class Isz = std::function<bool(T)>>
class LeqsSolver {
  using mat = matrix<T, Isz>;

  mat argmat;
  size_t rk;
  std::vector<size_t> fe_list;

public:
  // using guass method to solve linear equations Ax=b
  LeqsSolver(mat const &A, mat const &b):
    argmat(merge_lr(A, b)) {
    assert(b.col_size() == 1 && A.row_size() == b.row_size());
    // std::cout << __LINE__ << ": \n"
    //           << argmat << std::endl;
    rk = (size_t)std::abs(argmat.do_gauss());
    // std::cerr << __LINE__ << ": \n"
    //           << argmat << std::endl;
    if (argmat.row_size() > argmat.col_size()) argmat = argmat.submatrix(0, rk - 1, 0, argmat.col_size());
    // std::cerr << __LINE__ << ": \n"
    //           << argmat << std::endl;
    if (argmat.row_size() + 1 >= argmat.col_size()) {
      argmat.col(argmat.col_size() - 1) /= argmat.diag_const(0);
      argmat.diag(0) = 1;
      return;
    }
    // std::cerr << __LINE__ << ": \n"
    //           << argmat << std::endl;
    argmat = merge_ud(argmat, mat(argmat.col_size() - argmat.row_size() - 1, argmat.col_size(), argmat.iszero_func()));
    // std::cerr << __LINE__ << ": \n"
    //           << argmat << std::endl;
    for (size_t i = 0, j = rk; i < argmat.row_size(); ++i) {
      if (argmat(i, i) != 0) continue;
      if (j < argmat.row_size()) argmat.swap_row(i, j++);
      fe_list.push_back(i);
      argmat(i, i) = 1;
    }
    // std::cerr << __LINE__ << ": \n"
    //           << argmat << std::endl;
    for (auto i : fe_list) argmat.col(i) /= argmat.diag_const(0);
    argmat.col(argmat.col_size() - 1) /= argmat.diag_const(0);
    argmat.diag(0) = 1;
    // std::cerr << __LINE__ << ": \n"
    //           << argmat << std::endl;
  }

  constexpr size_t rank() const { return rk; }
  // @return -1 of no solution, else number of free elements
  constexpr ptrdiff_t fe_cnt() const { return (ptrdiff_t)(argmat.col_size() - rk) - 1; }
  // values of free elements is 0
  mat solution() const { return argmat.submatrix(0, argmat.row_size(), argmat.col_size() - 1, argmat.col_size()); }
  // only for infinite solution, need set values of free elements
  mat solution(mat const &fe_val) const {
    const size_t fec = (size_t)fe_cnt();
    assert(fe_val.col_size() == 1 && fe_val.row_size() == fec);
    mat _ = argmat;
    for (size_t i = 0; i < fec; ++i) _(fe_list[i], _.col_size() - 1) = fe_val(i, 0);
    // std::cerr << __LINE__ << ": \n"
    //           << _ << std::endl;
    _.do_gauss();
    // std::cerr << __LINE__ << ": \n"
    //           << _ << std::endl;
    return _.submatrix(0, _.row_size(), _.col_size() - 1, _.col_size());
  }
};

}  // namespace tifa_libs::math

#endif