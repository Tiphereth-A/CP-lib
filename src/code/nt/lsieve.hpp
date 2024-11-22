#ifndef TIFALIBS_MATH_LSIEVE
#define TIFALIBS_MATH_LSIEVE

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class... Ts>
struct lsieve : Ts... {
  vecb not_prime;
  vecu primes;

  CEXPE lsieve(u32 n) : Ts(n)..., not_prime(n) {
    if (n < 2) return;
    // clang-format off
    primes.reserve(n / (n >= 5e5 ? 12 : n >= 1e4 ? 8 : n >= 1150 ? 6 : n >= 120 ? 4 : n >= 8 ? 2 : 1));
    // clang-format on
    flt_ (u32, i, 2, n) {
      if (!not_prime[i]) primes.push_back(i), (..., Ts::prime(i));
      for (auto j : primes) {
        if (i * j >= n) break;
        if (not_prime[i * j] = true; i % j) (..., Ts::coprime(i, j));
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