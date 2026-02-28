// competitive-verifier: STANDALONE

#include "../../../src/nt/carmichael/lib.hpp"
#include "../../../src/nt/euler_phi/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
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
  for (int i = 1; i <= 10; ++i) {
    timer_(test());
  }
}