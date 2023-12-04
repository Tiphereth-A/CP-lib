#ifndef TIFALIBS_MATH_CANTOR_VAL2SEQ
#define TIFALIBS_MATH_CANTOR_VAL2SEQ

#include "../comb/gen_fact.hpp"

namespace tifa_libs::math {

inline vec<u32> cantor_val2seq(u64 cv, vec<u64> const &fact) {
  u32 n = (u32)fact.size();
  --cv;
  vec<u32> s;
  s.reserve(n);
  for (u32 i = 0; i < n; cv %= fact[n - i - 1], ++i) s.push_back(u32(cv / fact[n - i - 1]));
  return s;
}
inline vec<u32> cantor_val2seq(u64 cv, u32 n) { return cantor_val2seq(cv, gen_fact(n, -1_u64)); }

}  // namespace tifa_libs::math

#endif