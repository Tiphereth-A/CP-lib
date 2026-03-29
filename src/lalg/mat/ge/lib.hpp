#pragma once

#include "../../../util/traits/math/lib.hpp"
#include "../../ds/mat/lib.hpp"

namespace tifa_libs {

template <class T, class Is0, bool euclid = int_c<T>>
requires(!euclid || !std::is_floating_point_v<T>) && requires(Is0 is0, T t) {
  { is0(t) } -> std::same_as<bool>;
}
CEXP i32 ge_mat(matrix<T>& mat, Is0 is0, bool clear_u = true) NE {
  const u32 R = mat.row(), C = mat.col(), rk_max = min(R, C);
  u32 rk = 0;
  bool neg = false;
  auto swapr = [&](u32 i, u32 c) NE {
    u32 i2 = i;
    flt_ (u32, r, i + 1, R) {
      bool better = false;
      flt_ (u32, k, c, C) {
        if (mat(r, k) == mat(i2, k)) continue;
        better = mat(i2, k) < mat(r, k);
        break;
      }
      if (better) i2 = r;
    }
    if (i != i2) {
      mat.swap_row(i, i2);
      return true;
    }
    return false;
  };
  for (u32 i = 0, c = 0; i < R; c = max(c, ++i)) {
    if CEXP (!euclid && !mint_c<T>) neg ^= swapr(i, c);
    else if (is0(mat(i, c))) neg ^= swapr(i, c);
    while (c < C && is0(mat(i, c))) ++c;
    if (c == C) break;
    flt_ (u32, j, clear_u ? 0 : i + 1, R) {
      if (i == j || is0(mat(j, c))) continue;
      if CEXP (std::same_as<T, bool>)
        flt_ (u32, k, c, C) mat(j, k) = !mat(j, k);
      else if CEXP (euclid) {
        while (1) {
          if (is0(mat(j, c))) break;
          T _;
          if CEXP (mint_c<T>) _ = mat(i, c).val() / mat(j, c).val();
          else _ = mat(i, c) / mat(j, c);
          flt_ (u32, k, c, C) mat(i, k) -= _ * mat(j, k);
          mat.swap_row(i, j), neg ^= 1;
        }
      } else {
        T _ = mat(j, c) / mat(i, c);
        mat(j, c) = 0;
        flt_ (u32, k, c + 1, C) mat(j, k) -= mat(i, k) * _;
      }
    }
    if (++rk >= rk_max) break;
  }
  retif_((neg), -((i32)rk), (i32)rk);
}

}  // namespace tifa_libs
