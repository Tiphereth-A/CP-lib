#ifndef TIFA_LIBS_FAST_STR2UINT_MOD
#define TIFA_LIBS_FAST_STR2UINT_MOD

#include "../math/mul_mod_u.hpp"
#include "str2uint_si64.hpp"

namespace tifa_libs {

constexpr u64 str2uint_mod(std::string_view s, u64 mod) {
  size_t n = s.size();
  if (!n) return 0;
  u64 ans = 0;
  for (size_t i = 0; i + 8 <= n; i += 8) ans = (math::mul_mod_u(ans, 100000000, mod) + str2uint_si64(s.data() + i)) % mod;
  for (auto _ = s.data() + (n & size_t(-8)); _ < s.data() + n; ++_) ans = (math::mul_mod_u(ans, 10, mod) + (*_ & 15)) % mod;
  return ans;
}

}  // namespace tifa_libs

#endif