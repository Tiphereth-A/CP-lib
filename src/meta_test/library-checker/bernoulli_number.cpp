#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../code/comb/gen_bernoulli.hpp"
#include "../../code/io/fastio.hpp"

constexpr u32 MOD = 998244353;

#define GENTCs_p3ntts
#define GENTCs_p3nttd0
#define GENTCs_pcntts
#define GENTCs_pmtts
#define GENTCs_pmttd0
#define GENTCs_pntt

int main() {
#define GENTCs_p3nttd1
#define GENTCs_pmttd1
  u32 n;
  tifa_libs::fin >> n;
  tifa_libs::fout << tifa_libs::math::gen_bernoulli<poly>(n).data();
  return 0;
}
