#ifndef TIFALIBS_CONV_CONV_CZT
#define TIFALIBS_CONV_CONV_CZT

#include "../math/qpow.hpp"
#include "../nt/proot.hpp"
#include "../poly/czt_fps.hpp"

namespace tifa_libs::math {

template <class poly>
CEXP auto conv_czt(poly l, poly r, u32 ans_size = 0) {
  using mint = TPN poly::value_type;
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  assert(mint::mod() <= u64(-1_u32));
  const u32 m = (u32)mint::mod(), s = (u32)std::bit_ceil(l.size() + r.size() - 1);
  assert((m - 1) % s == 0);
  const mint c = qpow(mint(proot(m)), (m - 1) / s);
  l.resize(s), r.resize(s);
  l = czt_fps(l, c), r = czt_fps(r, c);
  flt_ (u32, i, 0, s) l[i] *= r[i];
  (l = czt_fps<mint, TPN poly::ccore_type>(l, c.inv())).resize(ans_size);
  return (l *= mint(s).inv()).data();
}

}  // namespace tifa_libs::math

#endif