#ifndef TIFALIBS_LALG_LEQS_SOLVER
#define TIFALIBS_LALG_LEQS_SOLVER

#include "mat.hpp"
#include "merge_lr_mat.hpp"
#include "rk_mat.hpp"
#include "trans_mat.hpp"

namespace tifa_libs::math {

template <class T, class Is0, class Ge>
requires requires(Is0 is0, Ge ge, T t, matrix<T> A, bool clear_u) {
  { is0(t) } -> std::same_as<bool>;
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP std::optional<matrix<T>> leqs_solver(matrix<T> CR A, matrix<T> CR b, Is0 &&is0, Ge &&ge) {
  const u32 r_ = A.row(), c_ = A.col();
  assert(b.col() == 1 && r_ == b.row());
  matrix<T> Ab = merge_lr_mat(A, b);
  const u32 rk = (u32)do_rank(Ab, std::forward<Ge>(ge));
  if (rk > c_) return {};
  if (!is0(Ab(rk - 1, c_))) {
    bool f = true;
    flt_ (u32, i, 0, c_)
      if (!is0(Ab(rk - 1, i))) {
        f = false;
        break;
      }
    if (f) return {};
  }
  flt_ (u32, i, rk, r_)
    if (!is0(Ab(i, c_))) return {};
  vecb used(c_, false);
  vecu idxs;
  for (u32 i = 0, _ = 0; i < r_; ++i) {
    while (i + _ < c_ && is0(Ab(i, i + _))) ++_;
    if (i + _ >= c_) break;
    used[i + _] = true;
    idxs.push_back(i + _);
  }
  matrix<T> sol(c_ - rk + 1, c_);
  {
    auto &v = sol.data()[0];
    for (u32 y = rk - 1; ~y; --y) {
      const u32 f = idxs[y];
      v[f] = Ab(y, c_);
      flt_ (u32, x, f + 1, c_) v[f] -= Ab(y, x) * v[x];
      v[f] /= Ab(y, f);
    }
  }
  for (u32 s = 0, _ = 0; s < c_; ++s) {
    if (used[s]) continue;
    auto &v = sol.data()[++_];
    v[s] = 1;
    for (u32 y = rk - 1; ~y; --y) {
      u32 f = idxs[y];
      for (u32 x = f + 1; x < c_; x++) v[f] -= Ab(y, x) * v[x];
      v[f] /= Ab(y, f);
    }
  }
  return transpose(sol);
}

}  // namespace tifa_libs::math

#endif