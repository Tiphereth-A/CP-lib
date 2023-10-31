#ifndef TIFA_LIBS_MATH_CANTOR_VAL2SEQ
#define TIFA_LIBS_MATH_CANTOR_VAL2SEQ

#include "../comb/gen_fact.hpp"

namespace tifa_libs::math {

inline vec<u32> cantor_val2seq(u64 cv, vec<u64> const &fact) {
  usz n = fact.size();
  --cv;
  vec<u32> s;
  s.reserve(n);
  for (u64 i = 0; i < n; cv %= fact[n - i - 1], ++i) s.push_back(u32(cv / fact[n - i - 1]));
  return s;
}
inline vec<u32> cantor_val2seq(u64 cv, usz n) { return cantor_val2seq(cv, gen_fact((u32)n, (u64)-1)); }

}  // namespace tifa_libs::math

#endif