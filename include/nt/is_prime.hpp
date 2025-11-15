#ifndef TIFALIBS_MATH_IS_PRIME
#define TIFALIBS_MATH_IS_PRIME

#include "../math/mul_mod.hpp"
#include "../math/qpow_mod.hpp"

namespace tifa_libs::math {

CEXP bool is_prime(u64 n) NE {
  retif_((n <= 2) [[unlikely]], n == 2);
  if (~n & 1) return false;
  if (n < 8 || n == 61) return true;
  if (!(n % 3) || !(n % 5) || !(n % 7)) return false;
  if (n < 121) return true;
  auto f = [n, d = (n - 1) >> std::countr_zero(n - 1)](auto&& bases) NE -> bool {
    for (u64 i : bases) {
      if (!(i % n)) continue;
      u64 t = d, y = qpow_mod(i, t, n);
      while (t != n - 1 && y != 1 && y != n - 1) y = mul_mod_u(y, y, n), t *= 2;
      if (y != n - 1 && (~t & 1)) return false;
    }
    return true;
  };
  CEXP u64 THRES1 = 341531, BASE1[]{9345883071009581737u};
  CEXP u64 THRES2 = 1050535501, BASE2[]{336781006125, 9639812373923155};
  CEXP u64 THRES3 = 350269456337, BASE3[]{4230279247111683200, 14694767155120705706u, 16641139526367750375u};
  CEXP u64 THRES4 = 55245642489451, BASE4[]{2, 141889084524735, 1199124725622454117, 11096072698276303650u};
  CEXP u64 THRES5 = 7999252175582851, BASE5[]{2, 4130806001517, 149795463772692060, 186635894390467037, 3967304179347715805};
  CEXP u64 THRES6 = 585226005592931977, BASE6[]{2, 123635709730000, 9233062284813009, 43835965440333360, 761179012939631437, 1263739024124850375};
  CEXP u64 BASE7[]{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  if (n < THRES1) return f(BASE1);
  if (n < THRES2) return f(BASE2);
  if (n < THRES3) return f(BASE3);
  if (n < THRES4) return f(BASE4);
  if (n < THRES5) return f(BASE5);
  if (n < THRES6) return f(BASE6);
  return f(BASE7);
}

}  // namespace tifa_libs::math

#endif