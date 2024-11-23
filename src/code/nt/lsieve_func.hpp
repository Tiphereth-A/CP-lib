#ifndef TIFALIBS_MATH_LSIEVE_FUNC
#define TIFALIBS_MATH_LSIEVE_FUNC

#include "../util/util.hpp"

namespace tifa_libs::math {

struct ls_mpf {
  vecu mpf;

 protected:
  CEXPE ls_mpf(u32 n) : mpf(n) { (n > 1) && (mpf[1] = 1); }
  CEXP void prime(u32 p) { mpf[p] = p; }
  CEXP void coprime(u32 i, u32 j) { mpf[i * j] = j; }
  CEXP void not_coprime(u32 i, u32 j) { mpf[i * j] = j; }
};
struct ls_phi {
  vecu phi;

 protected:
  CEXPE ls_phi(u32 n) : phi(n) { (n > 1) && (phi[1] = 1); }
  CEXP void prime(u32 p) { phi[p] = p - 1; }
  CEXP void coprime(u32 i, u32 j) { phi[i * j] = phi[i] * (j - 1); }
  CEXP void not_coprime(u32 i, u32 j) { phi[i * j] = phi[i] * j; }
};
struct ls_tau {
  vecu tau;

 protected:
  vecu pc;
  CEXPE ls_tau(u32 n) : tau(n), pc(n, 1) { (n > 1) && (tau[1] = 1); }
  CEXP void prime(u32 p) { tau[p] = 2; }
  CEXP void coprime(u32 i, u32 j) { tau[i * j] = tau[i] * 2; }
  CEXP void not_coprime(u32 i, u32 j) { tau[i * j] = tau[i] + tau[i] / (pc[i * j] = pc[i] + 1); }
};
struct ls_mu {
  veci mu;

 protected:
  CEXPE ls_mu(u32 n) : mu(n) { (n > 1) && (mu[1] = 1); }
  CEXP void prime(u32 p) { mu[p] = -1; }
  CEXP void coprime(u32 i, u32 j) { mu[i * j] = -mu[i]; }
  CEXP void not_coprime(u32, u32) {}
};
struct ls_sigma {
  vecuu sigma;

 protected:
  vecuu pw;
  CEXPE ls_sigma(u32 n) : sigma(n), pw(n) { (n > 1) && (sigma[1] = 1); }
  CEXP void prime(u32 p) { pw[p] = (u64)p * p, sigma[p] = p + 1; }
  CEXP void coprime(u32 i, u32 j) { pw[i * j] = (u64)j * j, sigma[i * j] = sigma[i] * (j + 1); }
  CEXP void not_coprime(u32 i, u32 j) { sigma[i * j] = sigma[i] * ((pw[i * j] = pw[i] * j) - 1) / (pw[i] - 1); }
};

}  // namespace tifa_libs::math

#endif