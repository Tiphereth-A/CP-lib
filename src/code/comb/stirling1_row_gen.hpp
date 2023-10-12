#ifndef TIFA_LIBS_MATH_STIRLING1_ROW_GEN
#define TIFA_LIBS_MATH_STIRLING1_ROW_GEN

#include "../poly/poly.hpp"
#include "../poly/poly_tsh.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

namespace stirling1_row_gen_detail_ {

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
    for (size_t i = n; i > 0; --i) (f[i] *= (n - 1)) += f[i - 1];
    f[0] *= (n - 1);
    return;
  }
  solve(f, n / 2, fact, ifact);
  f.resize(n / 2 + 1);
  f *= poly_tsh(f, n / 2, fact, ifact);
  f.resize(n + 1);
}

}  // namespace stirling1_row_gen_detail_

// stirling1[i] = {n \\brace i}, i=0,1,...,m
template <class T>
inline poly<T> stirling1_row_gen(u64 m, u64 n, vec<u64> const& fact, vec<u64> const& ifact) {
  poly<T> ans;
  stirling1_row_gen_detail_::solve(ans, n, fact, ifact);
  ans.resize(m + 1);
  return ans;
}
// stirling1[i] = {n \\brace i}, i=0,1,...,m
template <class T>
inline poly<T> stirling1_row_gen(u64 m, u64 n) { return stirling1_row_gen<T>(m, n, fact_mod_gen(n + 1, T::value_type::mod()), ifact_mod_gen(n + 1, T::value_type::mod())); }

}  // namespace tifa_libs::math

#endif