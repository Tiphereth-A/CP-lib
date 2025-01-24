#ifndef TIFALIBS_BIT_PARITY
#define TIFALIBS_BIT_PARITY

#include "../util/util.hpp"

namespace tifa_libs::bit {

template <class T>
CEXP int parity(T x) NE {
  CEXP int nd = sizeof(T) * 8;
  static_assert(nd <= 128);
  CEXP int nd_ull = sizeof(unsigned long long) * 8;
  if CEXP (nd <= sizeof(unsigned) * 8) return __builtin_parity(x);
  else if CEXP (nd <= sizeof(unsigned long) * 8) return __builtin_parityl(x);
  else if CEXP (nd <= nd_ull) return __builtin_parityll(x);
  else return __builtin_parityll(x >> nd_ull) ^ __builtin_parityll(x & (unsigned long long)(-1));
}

}  // namespace tifa_libs::bit

#endif