#ifndef TIFALIBS_CONV_CONV_MVAL_DFT
#define TIFALIBS_CONV_CONV_MVAL_DFT

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::math {

// @param l l[j]=$\sum l_j \prod_i x_i^{j_i}$, where $j=\sum_i j_i n_i$
// @param r similar as {@code l} with same length
// @param base base[x]=$n_i$
template <dft_c DFT_t, std::same_as<TPN DFT_t::data_t> DFT_data_t>
CEXP vec<DFT_data_t> conv_mval_dft(DFT_t& dft, vec<DFT_data_t> CR l, vec<DFT_data_t> CR r, vecu CR base) NE {
  assert(l.size() == r.size());
  u32 k = (u32)base.size();
  retif_((!k) [[unlikely]], {l[0] * r[0]});
  dft.bzr((u32)l.size() * 2 - 1);
  u32 n = dft.size();
  vecu chi(n);
  flt_ (u32, i, 0, n, x) {
    x = i;
    for (auto b : base) chi[i] += (x /= b);
    chi[i] %= k;
  }
  vvec<DFT_data_t> f(k, vec<DFT_data_t>(n)), g(k, vec<DFT_data_t>(n));
  flt_ (u32, i, 0, (u32)l.size()) f[chi[i]][i] = l[i];
  flt_ (u32, i, 0, (u32)l.size()) g[chi[i]][i] = r[i];
  for (auto& i : f) dft.dif(i);
  for (auto& i : g) dft.dif(i);
  vec<DFT_data_t> _(k);
  flt_ (u32, l, 0, n) {
    fill(_, DFT_data_t{});
    flt_ (u32, i, 0, k)
      flt_ (u32, j, 0, k) _[i + j - (i + j >= k ? k : 0)] += f[i][l] * g[j][l];
    flt_ (u32, i, 0, k) f[i][l] = _[i];
  }
  for (auto& i : f) dft.dit(i);
  vec<DFT_data_t> ans(l.size());
  flt_ (u32, i, 0, (u32)ans.size()) ans[i] = f[chi[i]][i];
  return ans;
}
template <class DFT_t, class mint, class T = u64>
CEXP vec<mint> conv_mval_dft_um(DFT_t& dft, vec<T> CR l, vec<T> CR r, vecu CR base) NE {
  vec<mint> l_, r_;
  for (l_.reserve(l.size()); auto CR i : l) l_.push_back(i);
  for (r_.reserve(r.size()); auto CR i : r) r_.push_back(i);
  return conv_mval_dft(dft, l_, r_, base);
}

}  // namespace tifa_libs::math

#endif