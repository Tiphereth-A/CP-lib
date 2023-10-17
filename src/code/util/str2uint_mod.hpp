#ifndef TIFA_LIBS_UTIL_STR2UINT_MOD
#define TIFA_LIBS_UTIL_STR2UINT_MOD

#include "../math/mul_mod_u.hpp"
#include "str2uint_1e8.hpp"

namespace tifa_libs {

constexpr u64 str2uint_mod(const char* const s, size_t n, u64 mod) {
  if (!n) return 0;
  u64 ans = 0;
  for (size_t i = 0; i + 8 <= n; i += 8) ans = (math::mul_mod_u(ans, 100000000, mod) + str2uint_1e8(s + i)) % mod;
  for (auto _ = s + (n & size_t(-8)); _ < s + n; ++_) ans = (math::mul_mod_u(ans, 10, mod) + (*_ & 15)) % mod;
  return ans;
}

}  // namespace tifa_libs

#endif