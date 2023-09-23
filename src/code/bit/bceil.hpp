#ifndef TIFA_LIBS_BIT_BCEIL
#define TIFA_LIBS_BIT_BCEIL

#include "../util/util.hpp"

#include "cntl0.hpp"

namespace tifa_libs::bit {

// From GCC lib
template <typename T>
constexpr T bceil(T x) {
  if (x == 0 || x == 1) return 1;
  constexpr int nd = sizeof(T) * 8;
  int sh = nd - cntl0((T)(x - 1u));
  using U = decltype(x << 1);
  if constexpr (!std::is_same_v<U, T>) sh |= (sh & nd) << (sizeof(U) / sizeof(T) / 2);
  return (T)1u << sh;
}

}  // namespace tifa_libs::bit

#endif