#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/nt/lsieve_func.hpp"

#include "../../../include/math/qpow.hpp"
#include "../../../include/nt/gcd.hpp"
#include "../../../include/nt/lsieve.hpp"
#include "../../../include/nt/lsieve2.hpp"
#include "../base.hpp"

using namespace tifa_libs;
struct lsieve_bf {
  vecu prime, mpf, phi, tau;
  veci mu;
  vecuu sigma;

  constexpr lsieve_bf& reset_lsieve_bf(u32 n) {
    flt_ (u32, i, 2, n) {
      bool f = 1;
      flt_ (u32, j, 2, i - 1) {
        if (i % j == 0) {
          f = 0;
          break;
        }
        if (j > (i + j - 1) / j) break;
      }
      if (f) prime.push_back(i);
    }
    mpf = vecu(n), (n > 1) && (mpf[1] = 1);
    flt_ (u32, i, 2, n) {
      for (auto j : prime) {
        if (i < j) break;
        if (i % j == 0) {
          mpf[i] = j;
          break;
        }
      }
    }
    phi = vecu(n), (n > 1) && (phi[1] = 1);
    flt_ (u32, i, 2, n)
      flt_ (u32, j, 1, i + 1) phi[i] += (math::gcd(i, j) == 1);
    tau = vecu(n), (n > 1) && (tau[1] = 1);
    flt_ (u32, i, 2, n)
      flt_ (u32, j, 1, i + 1) tau[i] += (i % j == 0);
    mu = veci(n), (n > 1) && (mu[1] = 1);
    flt_ (u32, i, 2, n) {
      mu[i] = 1;
      for (auto j : prime) {
        if (i < j) break;
        if (i % j == 0) {
          if ((i / j) % j == 0) {
            mu[i] = 0;
            break;
          }
          mu[i] *= -1;
        }
      }
    }
    sigma = vecuu(n), (n > 1) && (sigma[1] = 1);
    flt_ (u32, i, 2, n)
      flt_ (u32, j, 1, i + 1) sigma[i] += (i % j == 0) * j;

    return *this;
  }
};

struct lsieve_func2 {
  vecu phi, tau;
  veci mu;
  vecuu sigma;

  constexpr lsieve_func2& reset_lsieve_func2(u32 n) {
    auto ls = math::lsieve2(n);
    phi = ls.run<u32>([](u32 p, u32 i) -> u32 { retif_((i == 0), 1, u32(math::qpow((u64)p, i) - math::qpow((u64)p, i - 1))); });
    tau = ls.run<u32>([](u32, u32 i) -> u32 { return i + 1; });
    mu = ls.run<i32>([](u32, u32 i) -> i32 {
      if (i == 0) return 1;
      else retif_((i == 1), -1, 0);
    });
    sigma = ls.run<u64>([](u32 p, u32 i) -> u64 { retif_((i == 0), 1, (math::qpow((u64)p, i + 1) - 1) / (p - 1)); });
    return *this;
  }
};

void test(u32 n) {
  lsieve_bf lsb;
  lsb.reset_lsieve_bf(n);

  math::lsieve<math::ls_mpf, math::ls_mu, math::ls_phi, math::ls_sigma, math::ls_tau> lsf(n);

  check(lsf.primes, lsb.prime);
  flt_ (u32, i, 0, n) check(lsf.mpf[i], lsb.mpf[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf.phi[i], lsb.phi[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf.tau[i], lsb.tau[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf.mu[i], lsb.mu[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf.sigma[i], lsb.sigma[i], check_param(i));

  lsieve_func2 lsf2;
  lsf2.reset_lsieve_func2(n);

  flt_ (u32, i, 0, n) check(lsf2.phi[i], lsb.phi[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf2.tau[i], lsb.tau[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf2.mu[i], lsb.mu[i], check_param(i));
  flt_ (u32, i, 0, n) check(lsf2.sigma[i], lsb.sigma[i], check_param(i));
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test(0); break;
    case unittest::TC::random_00: test(1); break;
    case unittest::TC::random_01: test(10); break;
    case unittest::TC::random_02: test(100); break;
    case unittest::TC::random_03: test(1000); break;
    case unittest::TC::random_04: test(2000); break;
    case unittest::TC::random_05: test(3000); break;
    case unittest::TC::random_06: test(4000); break;
    case unittest::TC::random_07: test(5000); break;
    case unittest::TC::random_08: test(6000); break;
    case unittest::TC::random_09: test(7000); break;
    default: break;
  }

  unittest::post_test();
}