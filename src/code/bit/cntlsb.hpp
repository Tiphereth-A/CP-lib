#ifndef TIFALIBS_BIT_CNTLSB
#define TIFALIBS_BIT_CNTLSB

#include "../util/util.hpp"

namespace tifa_libs::bit {

template <class T>
CEXP int cntlsb(T x) NE {
  CEXP int nd = sizeof(T) * 8;
  static_assert(nd <= 64);
  if CEXP (nd <= sizeof(unsigned) * 8) return __builtin_clrsb(x);
  else if CEXP (nd <= sizeof(unsigned long) * 8) return __builtin_clrsbl(x);
  return __builtin_clrsbll(x);
}

}  // namespace tifa_libs::bit

#endif