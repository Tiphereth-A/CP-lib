#ifndef TIFALIBS_UTIL_CONSTS
#define TIFALIBS_UTIL_CONSTS

#include "alias_num.hpp"
// clang-format off
namespace tifa_libs {
using std::numbers::pi_v;
template <std::floating_point FP>
inline FP eps_v = std::sqrt(std::numeric_limits<FP>::epsilon());
template <std::floating_point FP>
CEXP void set_eps(FP v) NE { eps_v<FP> = v; }
CEXP u32 TIME = ((__TIME__[0] & 15) << 20) | ((__TIME__[1] & 15) << 16) | ((__TIME__[3] & 15) << 12) | ((__TIME__[4] & 15) << 8) | ((__TIME__[6] & 15) << 4) | (__TIME__[7] & 15);
CEXP auto STR2U16 = [] { std::array<u32, 65536> table{}; table.fill(-1_u32); flt_ (u32, i, 48, 58) flt_ (u32, j, 48, 58) table[i << 8 | j] = (j & 15) * 10 + (i & 15); return table; }();

inline const auto fn_0 = [](auto&&...) NE {};
inline const auto fn_is0 = [](auto x) NE { return x == 0; };
}  // namespace tifa_libs
// clang-format on
#endif