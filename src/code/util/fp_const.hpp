#ifndef TIFA_LIBS_UTIL_FP_CONST
#define TIFA_LIBS_UTIL_FP_CONST

namespace tifa_libs {

// std::sqrt(std::numeric_limits<FP>::epsilon())
template <class FP>
inline constexpr FP EPS = FP(1e-8L);

// std::acos((FP)-1)
template <class FP>
inline constexpr FP PI = FP(3.141592653589793238462643383279502884L);

// (std::sqrt((FP)5) + 1) / 2
template <class FP>
inline constexpr FP PHI = FP(1.618033988749894848204586834365638118L);

}  // namespace tifa_libs

#endif