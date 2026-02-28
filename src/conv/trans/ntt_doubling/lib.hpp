#ifndef TIFALIBS_CONV_TRANS_NTT_DOUBLING_LIB
#define TIFALIBS_CONV_TRANS_NTT_DOUBLING_LIB

#include "../../../math/qpow/basic/lib.hpp"
#include "../../../util/alias/others/lib.hpp"
#include "../../../util/traits/math/lib.hpp"

namespace tifa_libs::math {

template <ntt_c NTT_t, std::same_as<TPN NTT_t::data_t> mint>
CEXP void ntt_doubling(NTT_t CR ntt, vec<mint>& f, u32 n = 0) NE {
  if (!n) n = (u32)f.size() / 2;
  assert(std::has_single_bit(n) && f.size() >= n * 2);
  vec<mint> g(begin(f), begin(f) + n);
  ntt.dit(g);
  mint r = 1;
  const mint zeta = qpow(ntt.G, (mint::mod() - 1) / (n * 2));
  flt_ (u32, i, 0, n) g[i] *= r, r *= zeta;
  ntt.dif(g), copy(g, begin(f) + n);
}

}  // namespace tifa_libs::math

#endif