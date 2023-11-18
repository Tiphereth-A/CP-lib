#ifndef TIFA_LIBS_MATH_BSGS_NIMBER
#define TIFA_LIBS_MATH_BSGS_NIMBER

#include "../util/hash_splitmix64.hpp"
#include "nimber.hpp"
#include "qpow.hpp"

namespace tifa_libs::math {

// solve a^x=b
template <class uint, uint (*prod)(uint, uint)>
uint bsgs_nimber(nimber<uint, prod> const& a, nimber<uint, prod> const& b) {
  assert(a != 0 && b != 0);
  vec<uint> rem, mod;
  for (uint p : {3, 5, 17, 257, 641, 65537, 6700417}) {
    if (uint(-1) % p) continue;
    uint q = uint(-1) / p;
    uint STEP = 1;
    while (4 * STEP * STEP < p) STEP *= 2;
    auto inside = [&](nimber<uint, prod> a, nimber<uint, prod> z) -> uint {
      hmap<uint, i32> mp;
      nimber<uint, prod> big = 1, now = 1;
      for (u32 i = 0; i < u32(STEP); ++i) mp[z.x] = i, z *= a, big *= a;
      for (i32 step = 0; step < i32(p + 10); step += STEP) {
        now *= big;
        if (mp.find(now.x) != mp.end()) return (step + STEP) - mp[now.x];
      }
      return uint(-1);
    };
    auto xq = qpow(a, q), yq = qpow(b, q);
    if (xq == 1 && yq == 1) continue;
    if (xq == 1 && yq != 1) return uint(-1);
    uint res = inside(xq, yq);
    if (res == uint(-1)) return uint(-1);
    rem.push_back(res % p);
    mod.push_back(p);
  }
  return crt_mod(rem, mod).first;
}

}  // namespace tifa_libs::math

#endif