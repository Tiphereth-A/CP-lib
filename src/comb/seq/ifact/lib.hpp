#ifndef TIFALIBS_COMB_SEQ_IFACT_LIB
#define TIFALIBS_COMB_SEQ_IFACT_LIB

#include "../../../math/mul_mod/lib.hpp"
#include "../inv/lib.hpp"

namespace tifa_libs::math {

// (i!)^{-1} from i=0..n-1
CEXP vecuu gen_ifact(u32 n, u64 mod, vecuu inv) NE {
  flt_ (u32, i, 2, n) inv[i] = mul_mod_u(inv[i], inv[i - 1], mod);
  return inv;
}
// (i!)^{-1} from i=0..n-1
CEXP vecuu gen_ifact(u32 n, u64 mod) NE { return gen_ifact(n, mod, gen_inv(n, mod)); }
// (i!)^{-1} from i=0..n-1
template <class mint>
CEXP vec<mint> gen_ifact(u32 n, vec<mint> inv) NE {
  flt_ (u32, i, 2, n) inv[i] *= inv[i - 1];
  return inv;
}
// (i!)^{-1} from i=0..n-1
template <class mint>
CEXP vec<mint> gen_ifact(u32 n) NE { return gen_ifact(n, gen_inv<mint>(n)); }

}  // namespace tifa_libs::math

#endif