#ifndef TIFALIBS_UTIL_FP_CONST
#define TIFALIBS_UTIL_FP_CONST

namespace tifa_libs {

// std::sqrt(std::numeric_limits<FP>::epsilon())
template <class FP>
constexpr inline FP EPS = FP(1e-8L);

// e
template <class FP>
constexpr inline FP E = FP(2.718281828459045235360287471352662498L);

// pi, std::acos((FP)-1)
template <class FP>
constexpr inline FP PI = FP(3.141592653589793238462643383279502884L);

// 1 / pi
template <class FP>
constexpr inline FP INV_PI = FP(0.318309886183790671537767526745028724L);

// 1 / std::sqrt(pi)
template <class FP>
constexpr inline FP INV_SQRT_PI = FP(0.564189583547756286948079451560772586L);

// std::sqrt(2)
template <class FP>
constexpr inline FP SQRT2 = FP(1.414213562373095048801688724209698079L);

// std::sqrt(3)
template <class FP>
constexpr inline FP SQRT3 = FP(1.732050807568877293527446341505872367L);

// 1 / std::sqrt(3)
template <class FP>
constexpr inline FP INV_SQRT3 = FP(0.577350269189625764509148780501957456L);

// Euler-Mascheroni constant
template <class FP>
constexpr inline FP EGAMMA = FP(0.577215664901532860606512090082402431L);

// Golden ratio, (1 + std::sqrt((FP)5)) / 2
template <class FP>
constexpr inline FP PHI = FP(1.618033988749894848204586834365638118L);

}  // namespace tifa_libs

#endif