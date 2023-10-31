#ifndef TIFA_LIBS_MATH_LUCAS
#define TIFA_LIBS_MATH_LUCAS

#include "binom.hpp"

namespace tifa_libs::math {

template <class mint>
class Lucas {
  Binom<mint> mCn;

  mint lucas__(u64 m, u64 n) const { return n == 0 ? 1 : mCn.mCn(m % mod(), n % mod()) * lucas__(m / mod(), n / mod()); }

 public:
  // @param p MUSU be prime
  explicit Lucas() : mCn(mint::mod()) { assert(mint::mod() > 1 && mint::mod() < 10'000'000); }

  constexpr static u64 mod() { return mint::mod(); }
  mint operator()(i64 m, i64 n) const { return m < n || n < 0 ? 0 : lucas__(mCn, (u64)m, (u64)n); }
};

}  // namespace tifa_libs::math

#endif