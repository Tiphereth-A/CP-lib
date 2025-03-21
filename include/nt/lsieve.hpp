#ifndef TIFALIBS_MATH_LSIEVE
#define TIFALIBS_MATH_LSIEVE

#include "../util/alias_others.hpp"

namespace tifa_libs::math {

template <class... Ts>
struct lsieve : Ts... {
  vecb not_prime;
  vecu primes;

  CEXPE lsieve(u32 n) NE : Ts(n)..., not_prime(n) {
    if (n < 2) return;
    // clang-format off
    primes.reserve((usz)max(127, int(n * (n >= 2e5 ? 1.6 : 1.7) / std::bit_width(n) + 1)));
    // clang-format on
    flt_ (u32, i, 2, n) {
      if (!not_prime[i]) primes.push_back(i), (..., Ts::prime(i));
      for (auto j : primes) {
        if (i * j >= n) break;
        not_prime[i * j] = true;
        if (i % j) (..., Ts::coprime(i, j));
        else {
          (..., Ts::not_coprime(i, j));
          break;
        }
      }
    }
    primes.shrink_to_fit();
  }
};

}  // namespace tifa_libs::math

#endif