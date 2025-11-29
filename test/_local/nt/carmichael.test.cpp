#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/nt/carmichael.hpp"

#include "../../../include/nt/euler_phi.hpp"
#include "../base.hpp"

using namespace tifa_libs;

rand::gen<u64> g;
void test() {
  flt_ (u64, i, 0, 32) {
    u64 n = 1_u64 << i;
    auto pfe = math::pf_exp(n);
    auto lambda = math::carmichael(pfe);
    auto phi = math::euler_phi(n, pfe);
    if (i > 2) check(lambda * 2, phi, check_param(i));
    else check(lambda, phi, check_param(i));
  }
  g.seed((u64)std::chrono::steady_clock::now().time_since_epoch().count());
  flt_ (u32, i, 0, 4) {
    u64 n = g();
    auto pfe = math::pf_exp(n);
    if (pfe.size() > 2 || (pfe.size() == 2 && (pfe[0].first > 2 || pfe[0].second > 1)) || (pfe.size() == 1 && pfe[0].first == 2 && pfe[0].second > 2)) {
      --i;
      continue;
    }
    auto lambda = math::carmichael(pfe);
    auto phi = math::euler_phi(n, pfe);
    check(lambda, phi, check_param(n));
  }
}

int main() {
  auto tcase = unittest::pre_test();
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
  switch (tcase) {
    case unittest::TC::example_00: test(); break;
    case unittest::TC::example_01: test(); break;
    case unittest::TC::random_00: test(); break;
    case unittest::TC::random_01: test(); break;
    case unittest::TC::random_02: test(); break;
    case unittest::TC::random_03: test(); break;
    case unittest::TC::random_04: test(); break;
    case unittest::TC::random_05: test(); break;
    case unittest::TC::random_06: test(); break;
    case unittest::TC::random_07: test(); break;
    case unittest::TC::random_08: test(); break;
    case unittest::TC::random_09: test(); break;
    default: break;
  }
#pragma GCC diagnostic warning "-Wimplicit-fallthrough"

  unittest::post_test();
}