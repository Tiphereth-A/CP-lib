#ifndef TIFA_LIBS_UTIL_ABS_CONSTEXPR
#define TIFA_LIBS_UTIL_ABS_CONSTEXPR

namespace tifa_libs {

template <class T>
constexpr T abs(T x) { return x < 0 ? -x : x; }

}  // namespace tifa_libs

#endif