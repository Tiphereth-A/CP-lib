#ifndef TIFA_LIBS_MATH_PROOT_GINT
#define TIFA_LIBS_MATH_PROOT_GINT

#include "gauss_int.hpp"
#include "pfactors.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

template <class mint, i64 M = -1>
inline GaussInt<mint, M> proot_gint() {
  using gint = GaussInt<mint, M>;
  const auto m = mint::mod();
  if (m == 998244353) return {1, 1};
  if (m == 999292927) return {1, 8};
  if (m == 1000000007) return {1, 4};
  gint r = {1, 1};
  const u64 ord = (((m + 1) & 3) ? (u64)m : (u64)m * m) - 1;
  auto pf = pfactors(ord);
  while (true) {
    bool ok = 1;
    for (auto [q, k] : pf)
      if (qpow(r, ord / q) == gint{1}) {
        ok = 0;
        break;
      }
    if (ok) break;
    r.imag(r.imag() + 1);
  }
  return r;
}

}  // namespace tifa_libs::math

#endif