#pragma once

#include "../../../util/rand/lib.hpp"
#include "../inv/lib.hpp"

namespace tifa_libs {

template <class T, class Is0, class Ge>
requires requires(Is0 is0, Ge ge, T t, matrix<T> A, bool clear_u) {
  { is0(t) } -> std::same_as<bool>;
  { ge(A, clear_u) } -> std::same_as<i32>;
}
CEXP matrix<T> adj_mat(matrix<T> mat, Is0&& is0, Ge&& ge) NE {
  const u32 n = mat.row();
  assert(n == mat.col());
  rand_gen<u64> gen;
  flt_ (u32, i, 0, n) mat.data()[i].push_back((T)gen.next());
  mat.data().emplace_back(n + 1);
  flt_ (u32, i, 0, n) mat(n, i) = (T)gen.next();
  auto _ = inv_mat<T, Is0, Ge, true>(mat, is0, ge);
  if (!_) return matrix<T>(n, n);
  auto&& [det, inv] = _.value();
  matrix<T> ans(n, n);
  ans.apply([&](u32 i, u32 j, T& val) NE { val = inv(n, n) * inv(i, j) - inv(i, n) * inv(n, j); });
  return ans * det;
}

}  // namespace tifa_libs
