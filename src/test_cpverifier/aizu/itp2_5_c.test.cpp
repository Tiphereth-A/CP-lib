#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_5_C"

#include "../../code/comb/cantor.hpp"
#include "../../code/comb/cantor_inv.hpp"
#include "../../code/comb/cantor_seq2val.hpp"
#include "../../code/comb/cantor_val2seq.hpp"
#include "../../code/util/ios_container.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<u32> p(n);
  std::cin >> p;
  auto s = tifa_libs::math::cantor_seq(p);
  auto fact = tifa_libs::math::gen_fact((u32)s.size(), -1_u64);
  u64 v = tifa_libs::math::cantor_seq2val(s, fact);
  if (v > 1) std::cout << tifa_libs::math::cantor_inv_seq(tifa_libs::math::cantor_val2seq(v - 1, fact)) << '\n';
  std::cout << p << '\n';
  if (v < fact.back() * n) std::cout << tifa_libs::math::cantor_inv_seq(tifa_libs::math::cantor_val2seq(v + 1, fact)) << '\n';
  return 0;
}
