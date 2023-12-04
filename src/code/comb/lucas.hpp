#ifndef TIFALIBS_COMB_LUCAS
#define TIFALIBS_COMB_LUCAS

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
class Lucas {
  Binom<mint> mCn;

  template <class T, std::enable_if_t<is_uint<T>::value>* = nullptr>
  mint lucas__(T m, T n) const { return n == 0 ? 1 : mCn.mCn(m % mod(), n % mod()) * lucas__(m / mod(), n / mod()); }

 public:
  // @param p MUSU be prime
  explicit Lucas() : mCn(mint::mod()) { assert(mint::mod() > 1 && mint::mod() < 10'000'000); }

  constexpr static u64 mod() { return mint::mod(); }
  template <class T, std::enable_if_t<is_sint<T>::value>* = nullptr>
  mint operator()(T m, T n) const { return m < n || n < 0 ? 0 : lucas__(to_uint_t<T>(m), to_uint_t<T>(n)); }
};

}  // namespace tifa_libs::math

#endif