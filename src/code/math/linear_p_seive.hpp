#ifndef TIFA_LIBS_MATH_LINEAR_P_SEIVE
#define TIFA_LIBS_MATH_LINEAR_P_SEIVE

#include "linear_seive.hpp"

namespace tifa_libs::math {

inline vec<u32> linear_p_seive(u32 n) {
  return linear_seive(
      n, []([[maybe_unused]] u32 p) {}, []([[maybe_unused]] u32 i, [[maybe_unused]] u32 j) {}, []([[maybe_unused]] u32 i, [[maybe_unused]] u32 j) {});
}

}  // namespace tifa_libs::math

#endif