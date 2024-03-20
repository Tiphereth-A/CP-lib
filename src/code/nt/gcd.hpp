#ifndef TIFALIBS_MATH_GCD
#define TIFALIBS_MATH_GCD

#include "../util/traits.hpp"

namespace tifa_libs::math {

// From GCC lib
template <int_c T, int_c U>
constexpr std::common_type_t<T, U> gcd(T a, U b) {
  using W = to_uint_t<std::common_type_t<T, U>>;
  if constexpr (std::is_integral_v<W>) return std::gcd(a, b);
  else {
    W a_ = abs(a), b_ = abs(b);
    if (a_ == 0) return b_;
    if (b_ == 0) return a_;
    const int i = std::countr_zero(a_), j = std::countr_zero(b_), k = std::min(i, j);
    a_ >>= i, b_ >>= j;
    while (true) {
      if (a_ > b_) std::swap(a_, b_);
      if ((b_ -= a_) == 0) return a_ << k;
      b_ >>= std::countr_zero(b_);
    }
  }
}

}  // namespace tifa_libs::math

#endif