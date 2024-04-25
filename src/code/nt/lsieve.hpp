#ifndef TIFALIBS_MATH_LSIEVE
#define TIFALIBS_MATH_LSIEVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class F1, class F2, class F3>
requires requires(F1 cb_prime, F2 cb_coprime, F3 cb_not_coprime, u32 p, u32 q) {
  cb_prime(p);
  cb_coprime(p, q);
  cb_not_coprime(p, q);
}
CEXP vecu lsieve(u32 n, F1 cb_prime, F2 cb_coprime, F3 cb_not_coprime) {
  vecb vis(n);
  vecu p;
  p.reserve(n <= 170 ? 16 : n / 10);
  flt_ (u32, i, 2, n) {
    if (!vis[i]) {
      p.push_back(i);
      cb_prime(i);
    }
    for (u32 j : p) {
      if (i * j >= n) break;
      vis[i * j] = true;
      if (i % j) cb_coprime(i, j);
      else {
        cb_not_coprime(i, j);
        break;
      }
    }
  }
  return p;
}

}  // namespace tifa_libs::math

#endif