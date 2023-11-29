#ifndef TIFA_LIBS_MATH_LSEIVE_FUNC
#define TIFA_LIBS_MATH_LSEIVE_FUNC

#include "lseive.hpp"

namespace tifa_libs::math {

enum lseive_state {
  ls_mpf = 1,
  ls_phi = 2,
  ls_mu = 4,
  ls_sigma = 8,
  ls_tau = 16
};

struct lseive_func {
  vec<u32> prime, mpf, phi;
  vec<i32> mu;
  vec<u64> sigma, tau;

  template <int state>
  lseive_func& reset_lseive_func(u32 n) {
    if constexpr (state | ls_mpf) mpf = vec<u32>(n), mpf[1] = 1;
    if constexpr (state | ls_phi) phi = vec<u32>(n), phi[1] = 1;
    if constexpr (state | ls_mu) mu = vec<i32>(n), mu[1] = 1;
    if constexpr (state | ls_sigma) pw = vec<u64>(n), sigma = vec<u64>(n), sigma[1] = 1;
    if constexpr (state | ls_tau) pc = vec<u32>(n, 1), tau = vec<u64>(n), tau[1] = 1;

    prime = lseive(
        n,
        [&](u32 p) {
          if constexpr (state | ls_mpf) mpf[p] = p;
          if constexpr (state | ls_phi) phi[p] = p - 1;
          if constexpr (state | ls_mu) mu[p] = -1;
          if constexpr (state | ls_sigma) pw[p] = (u64)p * p, sigma[p] = p + 1;
          if constexpr (state | ls_tau) tau[p] = 2;
        },
        [&](u32 i, u32 j) {
          if constexpr (state | ls_mpf) mpf[i * j] = j;
          if constexpr (state | ls_phi) phi[i * j] = phi[i] * (j - 1);
          if constexpr (state | ls_mu) mu[i * j] = -mu[i];
          if constexpr (state | ls_sigma) pw[i * j] = (u64)j * j, sigma[i * j] = sigma[i] * (j + 1);
          if constexpr (state | ls_tau) tau[i * j] = tau[i] * 2;
        },
        [&](u32 i, u32 j) {
          if constexpr (state | ls_mpf) mpf[i * j] = j;
          if constexpr (state | ls_phi) phi[i * j] = phi[i] * j;
          if constexpr (state | ls_sigma) sigma[i * j] = sigma[i] * ((pw[i * j] = pw[i] * j) - 1) / (pw[i] - 1);
          if constexpr (state | ls_tau) tau[i * j] = tau[i] + tau[i] / (pc[i * j] = pc[i] + 1);
        });
    return *this;
  }

 private:
  vec<u64> pw;
  vec<u32> pc;
};

}  // namespace tifa_libs::math

#endif