#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/nt/lsieve_func.hpp"

#include "../../../code/math/qpow.hpp"
#include "../../../code/nt/gcd.hpp"
#include "../../../code/nt/lsieve2.hpp"
#include "../base.hpp"

constexpr u32 N = 5000;

struct lsieve_bf {
  vecu prime, mpf, phi, tau;
  veci mu;
  vecuu sigma;

  template <int state>
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
    if constexpr (state | tifa_libs::math::ls_mpf) {
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
    }
    if constexpr (state | tifa_libs::math::ls_phi) {
      phi = vecu(n), (n > 1) && (phi[1] = 1);
      flt_ (u32, i, 2, n)
        fle_ (u32, j, 1, i) phi[i] += (tifa_libs::math::gcd(i, j) == 1);
    }
    if constexpr (state | tifa_libs::math::ls_tau) {
      tau = vecu(n), (n > 1) && (tau[1] = 1);
      flt_ (u32, i, 2, n)
        fle_ (u32, j, 1, i) tau[i] += (i % j == 0);
    }
    if constexpr (state | tifa_libs::math::ls_mu) {
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
    }
    if constexpr (state | tifa_libs::math::ls_sigma) {
      sigma = vecuu(n), (n > 1) && (sigma[1] = 1);
      flt_ (u32, i, 2, n)
        fle_ (u32, j, 1, i) sigma[i] += (i % j == 0) * j;
    }

    return *this;
  }
};

struct lsieve_func2 {
  vecu phi, tau;
  veci mu;
  vecuu sigma;

  template <int state>
  constexpr lsieve_func2& reset_lsieve_func2(u32 n) {
    auto ls = tifa_libs::math::lsieve2(n);
    if constexpr (state | tifa_libs::math::ls_phi) phi = ls.run<u32>([](u32 p, u32 i) -> u32 { return i == 0 ? 1 : u32(tifa_libs::math::qpow((u64)p, i) - tifa_libs::math::qpow((u64)p, i - 1)); });
    if constexpr (state | tifa_libs::math::ls_tau) tau = ls.run<u32>([](u32, u32 i) -> u32 { return i + 1; });
    if constexpr (state | tifa_libs::math::ls_mu) mu = ls.run<i32>([](u32, u32 i) -> i32 { return i == 0 ? 1 : i == 1 ? -1
                                                                                                                      : 0; });
    if constexpr (state | tifa_libs::math::ls_sigma) sigma = ls.run<u64>([](u32 p, u32 i) -> u64 { return i == 0 ? 1 : (tifa_libs::math::qpow((u64)p, i + 1) - 1) / (p - 1); });
    return *this;
  }
};

template <int state>
void test(u32 n) {
  lsieve_bf lsb;
  lsb.reset_lsieve_bf<state>(n);

  tifa_libs::math::lsieve_func lsf;
  lsf.reset_lsieve_func<state>(n);

  check(lsf.prime, lsb.prime);
  flt_ (u32, i, 0, N) check(lsf.mpf[i], lsb.mpf[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf.phi[i], lsb.phi[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf.tau[i], lsb.tau[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf.mu[i], lsb.mu[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf.sigma[i], lsb.sigma[i], check_param(i));

  lsieve_func2 lsf2;
  lsf2.reset_lsieve_func2<state>(n);

  flt_ (u32, i, 0, N) check(lsf2.phi[i], lsb.phi[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf2.tau[i], lsb.tau[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf2.mu[i], lsb.mu[i], check_param(i));
  flt_ (u32, i, 0, N) check(lsf2.sigma[i], lsb.sigma[i], check_param(i));
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test<0>(N), test<11>(N), test<22>(N); break;
    case tifa_libs::unittest::ts_random_00: test<1>(N), test<12>(N), test<23>(N); break;
    case tifa_libs::unittest::ts_random_01: test<2>(N), test<13>(N), test<24>(N); break;
    case tifa_libs::unittest::ts_random_02: test<3>(N), test<14>(N), test<25>(N); break;
    case tifa_libs::unittest::ts_random_03: test<4>(N), test<15>(N), test<26>(N); break;
    case tifa_libs::unittest::ts_random_04: test<5>(N), test<16>(N), test<27>(N); break;
    case tifa_libs::unittest::ts_random_05: test<6>(N), test<17>(N), test<28>(N); break;
    case tifa_libs::unittest::ts_random_06: test<7>(N), test<18>(N), test<29>(N); break;
    case tifa_libs::unittest::ts_random_07: test<8>(N), test<19>(N), test<30>(N); break;
    case tifa_libs::unittest::ts_random_08: test<9>(N), test<20>(N), test<31>(N); break;
    case tifa_libs::unittest::ts_random_09: test<10>(N), test<21>(N); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}