#ifndef TIFA_LIBS_MATH_LINEAR_SEIVE
#define TIFA_LIBS_MATH_LINEAR_SEIVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class F1, class F2, class F3>
inline vec<u32> linear_seive(u32 n, F1 cb_prime, F2 cb_coprime, F3 cb_not_coprime) {
  vec<bool> vis(n);
  vec<u32> p;
  p.reserve(n <= 55 ? 16 : n / 10);
  for (u32 i = 2; i < n; ++i) {
    if (!vis[i]) {
      p.push_back(i);
      cb_prime(i);
    }
    for (u32 j : p) {
      if ((u64)i * j >= n) break;
      vis[i * j] = true;
      if (i % j)
        cb_coprime(i, j);
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