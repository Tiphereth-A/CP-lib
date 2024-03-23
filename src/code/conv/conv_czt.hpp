#ifndef TIFALIBS_CONV_CONV_CZT
#define TIFALIBS_CONV_CONV_CZT

#include "../math/qpow.hpp"
#include "../nt/proot_u32.hpp"
#include "../poly/poly_czt.hpp"

namespace tifa_libs::math {

template <class poly>
constexpr auto conv_czt(poly l, poly r, u32 ans_size = 0) {
  using mint = typename poly::value_type;
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  assert(mint::mod() <= u64(-1_u32));
  const u32 m = (u32)mint::mod();
  u32 s = (u32)std::bit_ceil(l.size() + r.size() - 1);
  assert((m - 1) % s == 0);
  mint c = qpow(mint(proot_u32(m)), (m - 1) / s);
  l.resize(s);
  r.resize(s);
  l = poly_czt(l, c);
  r = poly_czt(r, c);
  for (u32 i = 0; i < s; ++i) l[i] *= r[i];
  l = poly_czt<poly, mint>(l, c.inv());
  l.resize(ans_size);
  return (l *= mint(s).inv()).data();
}

}  // namespace tifa_libs::math

#endif