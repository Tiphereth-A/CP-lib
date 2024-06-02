#ifndef TIFALIBS_MATH_BSGS_NIMBER
#define TIFALIBS_MATH_BSGS_NIMBER

#include "../edh/hash_splitmix64.hpp"
#include "../math/nimber.hpp"
#include "../math/qpow.hpp"

namespace tifa_libs::math {

// solve a^x=b
template <std::unsigned_integral T, T (*prod)(T, T)>
CEXP T bsgs_nimber(nimber<T, prod> CR a, nimber<T, prod> CR b) {
  assert(a != 0 && b != 0);
  vec<T> rem, mod;
  for (T p : {3, 5, 17, 257, 641, 65537, 6700417}) {
    if (T(-1) % p) continue;
    const T q = T(-1) / p;
    T step = 1;
    while (4 * step * step < p) step *= 2;
    auto f = [&](nimber<T, prod> a, nimber<T, prod> z) -> T {
      hmap<T, i32> mp;
      nimber<T, prod> big = 1, now = 1;
      flt_ (u32, i, 0, step) mp[z.x] = i, z *= a, big *= a;
      for (i32 step = 0; step < i32(p + 10); step += step)
        if (now *= big; mp.find(now.x) != mp.end()) return (step + step) - mp[now.x];
      return T(-1);
    };
    const auto xq = qpow(a, q), yq = qpow(b, q);
    if (xq == 1 && yq == 1) continue;
    if (xq == 1 && yq != 1) return T(-1);
    if (T _ = f(xq, yq); _ == T(-1)) return T(-1);
    else rem.push_back(_ % p), mod.push_back(p);
  }
  return crt_mod(rem, mod).first;
}

}  // namespace tifa_libs::math

#endif