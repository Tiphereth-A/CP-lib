#ifndef TIFALIBS_MATH_LSIEVE_FUNC
#define TIFALIBS_MATH_LSIEVE_FUNC

#include "lsieve.hpp"

namespace tifa_libs::math {

enum lsieve_state { ls_mpf = 1,
                    ls_phi = 2,
                    ls_tau = 4,
                    ls_mu = 8,
                    ls_sigma = 16 };

struct lsieve_func {
  vecu prime, mpf, phi, tau;
  veci mu;
  vecuu sigma;

  template <int state>
  CEXP lsieve_func& reset_lsieve_func(u32 n) {
    if CEXP (state | ls_mpf) mpf = vecu(n), (n > 1) && (mpf[1] = 1);
    if CEXP (state | ls_phi) phi = vecu(n), (n > 1) && (phi[1] = 1);
    if CEXP (state | ls_tau) pc = vecu(n, 1), tau = vecu(n), (n > 1) && (tau[1] = 1);
    if CEXP (state | ls_mu) mu = veci(n), (n > 1) && (mu[1] = 1);
    if CEXP (state | ls_sigma) pw = vecuu(n), sigma = vecuu(n), (n > 1) && (sigma[1] = 1);

    prime = lsieve(
        n,
        [&](u32 p) {
          if CEXP (state | ls_mpf) mpf[p] = p;
          if CEXP (state | ls_phi) phi[p] = p - 1;
          if CEXP (state | ls_tau) tau[p] = 2;
          if CEXP (state | ls_mu) mu[p] = -1;
          if CEXP (state | ls_sigma) pw[p] = (u64)p * p, sigma[p] = p + 1; },
        [&](u32 i, u32 j) {
          if CEXP (state | ls_mpf) mpf[i * j] = j;
          if CEXP (state | ls_phi) phi[i * j] = phi[i] * (j - 1);
          if CEXP (state | ls_tau) tau[i * j] = tau[i] * 2;
          if CEXP (state | ls_mu) mu[i * j] = -mu[i];
          if CEXP (state | ls_sigma) pw[i * j] = (u64)j * j, sigma[i * j] = sigma[i] * (j + 1); },
        [&](u32 i, u32 j) {
          if CEXP (state | ls_mpf) mpf[i * j] = j;
          if CEXP (state | ls_phi) phi[i * j] = phi[i] * j;
          if CEXP (state | ls_tau) tau[i * j] = tau[i] + tau[i] / (pc[i * j] = pc[i] + 1);    
          if CEXP (state | ls_sigma) sigma[i * j] = sigma[i] * ((pw[i * j] = pw[i] * j) - 1) / (pw[i] - 1); });
    return *this;
  }

 private:
  vecuu pw;
  vecu pc;
};

}  // namespace tifa_libs::math

#endif