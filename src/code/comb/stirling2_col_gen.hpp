#ifndef TIFA_LIBS_MATH_STIRLING2_COL_GEN
#define TIFA_LIBS_MATH_STIRLING2_COL_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_inv.hpp"
#include "../poly/poly_tsh.hpp"
#include "../poly/poly_shr.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

namespace stirling2_col_gen_detail_ {

template <class T>
void solve(poly<T>& f, size_t n, vec<u64> const& fact, vec<u64> const& ifact) {
  if (n == 1) {
    f[0] = 0;
    f[1] = 1;
    return;
  }
  if (n & 1) {
    solve(f, n - 1, fact, ifact);
    f.resize(n + 1);
    for (size_t i = n; i > 0; --i) f[i] = f[i - 1] - (n - 1) * f[i];
    f[0] = (-f[0]) * (n - 1);
    return;
  }
  solve(f, n / 2, fact, ifact);
  f.resize(n / 2 + 1);
  f *= poly_tsh(f, n / 2, fact, ifact);
  f.resize(n + 1);
}

}  // namespace stirling2_col_gen_detail_

// stirling2[i] = {i \\brack k}, i=0,1,...,n
template <class T>
inline poly<T> stirling2_col_gen(u64 n, u64 k) {
  if (k > n) return poly<T>(n + 1);
  u64 mod = T::value_type::mod();
  vec<u64> fact = fact_mod_gen(n + 1, mod), ifact = ifact_mod_gen(n + 1, mod);
  poly<T> ans;
  stirling2_col_gen_detail_::solve(ans, k + 1, fact, ifact);
  ans.resize(k + 1);
  ans.reverse();
  for (size_t i = n - k + 1; i < k + 1; ++i) ans[i] = 0;
  for (size_t i = k + 1; i < n - k + 1; ++i) ans[i] = 0;
  ans.resize(n - k + 1);
  ans = poly_inv(ans);
  ans.resize(n + 1);
  return poly_shr(ans, k);
}

}  // namespace tifa_libs::math

#endif