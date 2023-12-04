#ifndef TIFALIBS_CONV_NTT_DOUBLING
#define TIFALIBS_CONV_NTT_DOUBLING

#include "../bit/ispow2.hpp"
#include "../math/qpow.hpp"

namespace tifa_libs::math {

template <class NTT_t, class mint>
void ntt_doubling(NTT_t const& ntt, vec<mint>& f, u32 n = 0) {
  if (!n) n = (u32)f.size() / 2;
  assert(n > 1 && bit::ispow2(n) && f.size() >= n * 2);
  vec<mint> g(f.begin(), f.begin() + n);
  ntt.dit(g);
  mint r = 1, zeta = qpow(ntt.G, (mint::mod() - 1) / (n * 2));
  for (u32 i = 0; i < n; ++i) g[i] *= r, r *= zeta;
  ntt.dif(g);
  std::copy(g.begin(), g.end(), f.begin() + n);
}

}  // namespace tifa_libs::math

#endif