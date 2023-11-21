#ifndef TIFA_LIBS_MATH_NTT_DOUBLING
#define TIFA_LIBS_MATH_NTT_DOUBLING

#include "qpow.hpp"

namespace tifa_libs::math {

template <class NTT_t, class mint>
void ntt_doubling(NTT_t const& ntt, vec<mint>& f) {
  u32 n = (u32)f.size();
  auto g = f;
  ntt.dit(g);
  mint r = 1, zeta = qpow(ntt.G, (mint::mod() - 1) / (n * 2));
  for (u32 i = 0; i < n; ++i) g[i] *= r, r *= zeta;
  ntt.dif(g);
  std::copy(g.begin(), g.end(), std::back_inserter(f));
}

}  // namespace tifa_libs::math

#endif