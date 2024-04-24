#ifndef TIFALIBS_MATH_ATKIN
#define TIFALIBS_MATH_ATKIN

#include "../math/isqrt.hpp"

namespace tifa_libs::math {

// @return primes in [1, %lim]
constexpr vecu atkin(u32 lim) {
  if (lim < 2) return {};
  if (lim < 3) return {2};
  if (lim < 5) return {2, 3};

  u32 slim = isqrt(lim);
  if (slim * slim < lim) ++slim;
  vecb vis(lim + 1);

  for (u32 i = 0; i < slim; ++i)
    for (u32 j = 0; j < slim; ++j) {
      if (u64 n = 4_u64 * i * i + (u64)j * j; n > lim) break;
      else if (u32(n) % 12 == 1 || u32(n) % 12 == 5) vis[n].flip();
    }
  for (u32 i = 0; i < slim; ++i)
    for (u32 j = 0; j < slim; ++j) {
      if (u64 n = 3_u64 * i * i + (u64)j * j; n > lim) break;
      else if (u32(n) % 12 == 7) vis[n].flip();
    }
  for (u32 i = 0; i < slim; ++i)
    for (u32 j = i - 1; ~j; --j) {
      if (u64 n = 3_u64 * i * i - (u64)j * j; n > lim) break;
      else if (u32(n) % 12 == 11) vis[n].flip();
    }
  for (u32 i = 5; i <= slim; ++i)
    if (vis[i])
      for (u32 k = i * i, j = k; j <= lim; j += k) vis[j] = false;
  vecu ret{2, 3};
  for (u32 x = 5; x <= lim; ++x)
    if (vis[x]) ret.push_back(x);
  return ret;
}

}  // namespace tifa_libs::math

#endif