#ifndef TIFALIBS_COMB_GEN_STIRLING2_COL
#define TIFALIBS_COMB_GEN_STIRLING2_COL

#include "../poly/inv_fps.hpp"
#include "../poly/shl_fps.hpp"
#include "../poly/tsh_fps.hpp"

namespace tifa_libs::math {

// stirling2[i] = {i \\brack k}, i=0,1,...,n
template <class poly>
constexpr poly gen_stirling2_col(u32 n, u32 k, vecu64 const& fact, vecu64 const& ifact) {
  using mint = typename poly::value_type;
  if (k > n) return poly(n + 1);

  auto dfs = [&](auto&& dfs, poly& f, u32 n) -> void {
    if (n == 1) return;
    if (n & 1) {
      dfs(dfs, f, n - 1);
      f.data().push_back(0);
      for (u32 i = n; i; --i) f[i] = f[i - 1] - (n - 1) * f[i];
      f[0] = (-f[0]) * (n - 1);
      return;
    }
    dfs(dfs, f, n / 2);
    f.data().push_back(0);
    f *= tsh_fps(f, mint(mint::mod() - n / 2), fact, ifact);
    f.resize(n + 1);
  };

  poly f{0, 1};
  dfs(dfs, f, k + 1);
  f.resize(k + 2);
  for (u32 i = 0; i < k + 1; ++i) f[i] = f[i + 1];
  f.reverse(k + 1);
  f[k + 1] = 0;
  f.resize(n - k + 1);
  f = inv_fps(f).pre(n + 1);
  return shl_fps(f, k);
}
// stirling2[i] = {i \\brack k}, i=0,1,...,n
template <class poly>
constexpr poly gen_stirling2_col(u32 n, u32 k) {
  using mint = typename poly::value_type;
  return gen_stirling2_col<poly>(n, k, gen_fact(n + 1, mint::mod()), gen_ifact(n + 1, mint::mod()));
}

}  // namespace tifa_libs::math

#endif