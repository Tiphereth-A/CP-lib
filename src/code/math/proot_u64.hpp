#ifndef TIFA_LIBS_MATH_PROOT_U64
#define TIFA_LIBS_MATH_PROOT_U64

#include "../bit/cntr0.hpp"
#include "../util/util.hpp"

#include "pfactors.hpp"
#include "proot_u32.hpp"
#include "qpow_mod.hpp"

namespace tifa_libs::math {

inline u64 proot_u64(u64 m) {
  if (m <= (u32)(-1)) return proot_u32((u32)m);
  u64 r = 1;
  auto pf = pfactors(m - 1);
  while (true) {
    bool ok = 1;
    for (auto [q, k] : pf)
      if (qpow_mod(r, (m - 1) / q, m) == 1) {
        ok = 0;
        break;
      }
    if (ok) break;
    ++r;
  }
  return r;
}

}  // namespace tifa_libs::math

#endif