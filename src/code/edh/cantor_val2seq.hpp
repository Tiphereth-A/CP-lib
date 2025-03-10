#ifndef TIFALIBS_EDH_CANTOR_VAL2SEQ
#define TIFALIBS_EDH_CANTOR_VAL2SEQ

#include "../comb/gen_fact.hpp"

namespace tifa_libs {

CEXP vecu cantor_val2seq(u64 cv, spnuu fact) NE {
  const u32 n = (u32)fact.size();
  vecu s;
  s.reserve(n), --cv;
  for (u32 i = 0; i < n; cv %= fact[n - i - 1], ++i) s.push_back(u32(cv / fact[n - i - 1]));
  return s;
}
CEXP vecu cantor_val2seq(u64 cv, u32 n) NE { return cantor_val2seq(cv, math::gen_fact(n, -1_u64)); }

}  // namespace tifa_libs

#endif