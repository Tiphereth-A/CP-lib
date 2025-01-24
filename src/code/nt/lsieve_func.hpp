#ifndef TIFALIBS_MATH_LSIEVE_FUNC
#define TIFALIBS_MATH_LSIEVE_FUNC

#include "../util/util.hpp"

namespace tifa_libs::math {

struct ls_mpf {
  vecu mpf;

 protected:
  CEXPE ls_mpf(u32 n) NE : mpf(n) {
    if (n > 1) mpf[1] = 1;
  }
  CEXP void prime(u32 p) NE { mpf[p] = p; }
  CEXP void coprime(u32 i, u32 j) NE { mpf[i * j] = j; }
  CEXP void not_coprime(u32 i, u32 j) NE { mpf[i * j] = j; }
};
struct ls_phi {
  vecu phi;

 protected:
  CEXPE ls_phi(u32 n) NE : phi(n) {
    if (n > 1) phi[1] = 1;
  }
  CEXP void prime(u32 p) NE { phi[p] = p - 1; }
  CEXP void coprime(u32 i, u32 j) NE { phi[i * j] = phi[i] * (j - 1); }
  CEXP void not_coprime(u32 i, u32 j) NE { phi[i * j] = phi[i] * j; }
};
struct ls_tau {
  vecu tau;

 protected:
  vecu pc;
  CEXPE ls_tau(u32 n) NE : tau(n), pc(n, 1) {
    if (n > 1) tau[1] = 1;
  }
  CEXP void prime(u32 p) NE { tau[p] = 2; }
  CEXP void coprime(u32 i, u32 j) NE { tau[i * j] = tau[i] * 2; }
  CEXP void not_coprime(u32 i, u32 j) NE { tau[i * j] = tau[i] + tau[i] / (pc[i * j] = pc[i] + 1); }
};
struct ls_mu {
  veci mu;

 protected:
  CEXPE ls_mu(u32 n) NE : mu(n) {
    if (n > 1) mu[1] = 1;
  }
  CEXP void prime(u32 p) NE { mu[p] = -1; }
  CEXP void coprime(u32 i, u32 j) NE { mu[i * j] = -mu[i]; }
  CEXP void not_coprime(u32, u32) NE {}
};
struct ls_sigma {
  vecuu sigma;

 protected:
  vecuu pw;
  CEXPE ls_sigma(u32 n) NE : sigma(n), pw(n) {
    if (n > 1) sigma[1] = 1;
  }
  CEXP void prime(u32 p) NE { pw[p] = (u64)p * p, sigma[p] = p + 1; }
  CEXP void coprime(u32 i, u32 j) NE { pw[i * j] = (u64)j * j, sigma[i * j] = sigma[i] * (j + 1); }
  CEXP void not_coprime(u32 i, u32 j) NE { sigma[i * j] = sigma[i] * ((pw[i * j] = pw[i] * j) - 1) / (pw[i] - 1); }
};

}  // namespace tifa_libs::math

#endif