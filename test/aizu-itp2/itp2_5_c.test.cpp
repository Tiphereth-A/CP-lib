#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_5_C"

#include "../../include/edh/cantor.hpp"
#include "../../include/edh/cantor_inv.hpp"
#include "../../include/edh/cantor_seq2val.hpp"
#include "../../include/edh/cantor_val2seq.hpp"
#include "../../include/io/ios_container.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu p(n);
  std::cin >> p;
  auto s = cantor_seq(p);
  auto fact = math::gen_fact((u32)s.size(), -1_u64);
  u64 v = cantor_seq2val(s, fact);
  if (v > 1) std::cout << cantor_inv_seq(cantor_val2seq(v - 1, fact)) << '\n';
  std::cout << p << '\n';
  if (v < fact.back() * n) std::cout << cantor_inv_seq(cantor_val2seq(v + 1, fact)) << '\n';
  return 0;
}
