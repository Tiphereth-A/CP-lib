#ifndef TIFALIBS_MATH_BSGS_NIMBER
#define TIFALIBS_MATH_BSGS_NIMBER

#include "../math/nimber.hpp"
#include "../math/qpow.hpp"
#include "../util/hash_splitmix64.hpp"

namespace tifa_libs::math {

// solve a^x=b
template <std::unsigned_integral T, T (*prod)(T, T)>
constexpr T bsgs_nimber(nimber<T, prod> const& a, nimber<T, prod> const& b) {
  assert(a != 0 && b != 0);
  vec<T> rem, mod;
  for (T p : {3, 5, 17, 257, 641, 65537, 6700417}) {
    if (T(-1) % p) continue;
    T q = T(-1) / p;
    T STEP = 1;
    while (4 * STEP * STEP < p) STEP *= 2;
    auto inside = [&](nimber<T, prod> a, nimber<T, prod> z) -> T {
      hmap<T, i32> mp;
      nimber<T, prod> big = 1, now = 1;
      for (u32 i = 0; i < u32(STEP); ++i) mp[z.x] = i, z *= a, big *= a;
      for (i32 step = 0; step < i32(p + 10); step += STEP) {
        now *= big;
        if (mp.find(now.x) != mp.end()) return (step + STEP) - mp[now.x];
      }
      return T(-1);
    };
    auto xq = qpow(a, q), yq = qpow(b, q);
    if (xq == 1 && yq == 1) continue;
    if (xq == 1 && yq != 1) return T(-1);
    T res = inside(xq, yq);
    if (res == T(-1)) return T(-1);
    rem.push_back(res % p);
    mod.push_back(p);
  }
  return crt_mod(rem, mod).first;
}

}  // namespace tifa_libs::math

#endif