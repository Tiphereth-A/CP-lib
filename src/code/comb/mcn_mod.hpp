#ifndef TIFA_LIBS_MATH_MCN_MOD
#define TIFA_LIBS_MATH_MCN_MOD

#include "../math/mul_mod_u.hpp"
#include "fact_mod_gen.hpp"
#include "ifact_mod_gen.hpp"

namespace tifa_libs::math {

// \binom{m}{n}
class MCN {
  u64 m_;

 public:
  const vec<u64> fact, ifact;

  MCN(u64 mod, size_t max_m) : m_(mod), fact(fact_mod_gen(max_m, mod)), ifact(ifact_mod_gen(max_m, mod)) {}

  constexpr u64 mod() const { return m_; }

  u64 operator()(i64 m, i64 n) const { return m < n || n < 0 ? 0 : mul_mod_u(mul_mod_u(fact[(size_t)m], ifact[(size_t)n], m_), ifact[(size_t)(m - n)], m_); }
};

}  // namespace tifa_libs::math

#endif