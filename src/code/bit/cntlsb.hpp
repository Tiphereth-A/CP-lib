#ifndef TIFALIBS_BIT_CNTLSB
#define TIFALIBS_BIT_CNTLSB

namespace tifa_libs::bit {

template <class T>
constexpr int cntlsb(T x) {
  constexpr int nd = sizeof(T) * 8;
  static_assert(nd <= 64);
  if constexpr (nd <= sizeof(unsigned) * 8) return __builtin_clrsb(x);
  else if constexpr (nd <= sizeof(unsigned long) * 8) return __builtin_clrsbl(x);
  else return __builtin_clrsbll(x);
}

}  // namespace tifa_libs::bit

#endif