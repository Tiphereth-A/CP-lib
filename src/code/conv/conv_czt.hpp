#ifndef TIFALIBS_CONV_CONV_CZT
#define TIFALIBS_CONV_CONV_CZT

#include "../math/proot_u64.hpp"
#include "../poly/poly_czt.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
poly<T> conv_czt(poly<T> l, poly<T> r, u32 ans_size = 0) {
  if (!ans_size) ans_size = u32(l.size() + r.size() - 1);
  using mint = typename T::value_type;
  constexpr u64 m = T::value_type::mod();
  u64 s = std::bit_ceil(l.size() + r.size() - 1);
  assert((m - 1) % s == 0);
  mint c = qpow(mint(proot_u64(m)), (m - 1) / s);
  l.resize(s);
  r.resize(s);
  l = poly_czt(l, c);
  r = poly_czt(r, c);
  for (u32 i = 0; i < s; ++i) l[i] *= r[i];
  l = poly_czt(l, c.inv());
  l.resize(ans_size);
  return l *= mint(s).inv();
}

}  // namespace tifa_libs::math

#endif