// competitive-verifier: STANDALONE

#include "../../../src/edh/hamming/lib.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
rand_gen<dbitset::word_t> g;

void test(u64 n) {
  dbitset s(n, g);

  timer_(auto v = hamming::encode(s));
  auto m = v.size() - n - 1;
  check_bool(v.size() <= (1_u64 << m), check_param(n), check_param(m), check_param(s.to_string()), check_param(v.to_string()));

  timer_(auto t1 = hamming::decode<false>(v));
  check(t1.to_string(), s.to_string(), check_param(v.to_string()));

  if (v.size() > 1) {
    auto v2 = v;
    rand_gen<u64> g2(1, v.size() - 1);
    auto pos = g2();
    v2.flip(pos);

    timer_(auto t2 = hamming::decode<true>(v2));
    check(v2.to_string(), v.to_string(), check_param(pos));
    check_bool(t2.has_value(), check_param(pos), check_param(s.to_string()), check_param(v.to_string()));
    check(t2->to_string(), s.to_string(), check_param(pos), check_param(v.to_string()));
  }
}

int main() {
  flt_ (u32, i, 0, 20) {
    timer_(test(i));
  }
  flt_ (u32, i, 2, 10) {
    timer_(test((1 << i) - (i + 1)));
  }
  timer_(test(1000));
  timer_(test(10000));
  timer_(test(200000));
  timer_(test(500000));
  timer_(test(100000));
  timer_(test(200000));
  timer_(test(500000));
  timer_(test(1000000));
  timer_(test(2000000));
  timer_(test(5000000));
}