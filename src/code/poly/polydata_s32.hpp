#ifndef TIFALIBS_POLY_POLYDATA_S32
#define TIFALIBS_POLY_POLYDATA_S32

#include "../conv/conv_naive.hpp"
#include "../conv/conv_ntt32.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
struct polydata_s32 {
  static_assert(mint::mod() > 1 && (mint::mod() & 3) == 1, "MOD must be prime with 4k+1");

  using value_type = mint;

  vec<mint> d;

  explicit constexpr polydata_s32(usz sz = 1) : d(sz) {}
  explicit constexpr polydata_s32(std::initializer_list<mint> v) : d(v) {}
  explicit constexpr polydata_s32(vec<mint> const &v) : d(v) {}

  void conv(polydata_s32 const &r, usz ans_size) { d = ans_size < 32 ? conv_naive(d, r.d, ans_size) : conv_ntt32(d, r.d, ans_size); }
  void conv(polydata_s32 const &r) { conv(r, d.size() + r.d.size() - 1); }
};

}  // namespace tifa_libs::math

#endif