#ifndef TIFA_LIBS_MATH_LEQS_SOLVER
#define TIFA_LIBS_MATH_LEQS_SOLVER

#include "../util/util.hpp"

#include "../util/abs_constexpr.hpp"
#include "mat.hpp"
#include "mat_merge_lr.hpp"
#include "mat_trans.hpp"
#include <valarray>

namespace tifa_libs::math {

template <class T, class Is0, class Ge>
std::optional<matrix<T>> leqs_solver(matrix<T> const &A, matrix<T> const &b, Is0 is_0, Ge ge) {
  size_t r_ = A.row(), c_ = A.col();
  assert(b.col() == 1 && r_ == b.row());
  matrix<T> Ab = merge_lr(A, b);
  u64 rk = (u64)abs(ge(Ab, false));
  vec<bool> used(c_, false);
  vec<size_t> idxs;
  for (size_t i = 0, _ = 0; i < r_; ++i) {
    while (i + _ < c_ && is_0(Ab(i, i + _))) ++_;
    if (i + _ >= c_) break;
    used[i + _] = true;
    idxs.push_back(i + _);
  }
  for (size_t i = rk; i < r_; ++i)
    if (Ab(i, c_)) return {};
  matrix<T> sol(c_ - rk + 1, c_);
  {
    auto &v = sol.data()[0];
    for (size_t y = rk - 1; ~y; --y) {
      size_t f = idxs[y];
      v[f] = Ab(y, c_);
      for (size_t x = f + 1; x < c_; x++) v[f] -= Ab(y, x) * v[x];
      v[f] /= Ab(y, f);
    }
  }
  for (size_t s = 0, _ = 0; s < c_; ++s) {
    if (used[s]) continue;
    auto &v = sol.data()[++_];
    v[s] = 1;
    for (size_t y = rk - 1; ~y; --y) {
      size_t f = idxs[y];
      for (size_t x = f + 1; x < c_; x++) v[f] -= Ab(y, x) * v[x];
      v[f] /= Ab(y, f);
    }
  }
  return transpose(sol);
}

}  // namespace tifa_libs::math

#endif