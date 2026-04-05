// competitive-verifier: STANDALONE

#include "../../../src/edh/bwt/inv.hpp"
#include "../../../src/edh/bwt/seq.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
rand_gen<char> g('\x21', '\x7f');

void test(u32 n) {
  strn s(n + 1, '\x20');
  flt_ (u32, i, 1, n + 1) s[i] = g();
  timer_(strn bwt_s = bwt(s));
  timer_(strn bwt_inv_s = bwt_inv(bwt_s));
  check(bwt_inv_s, s, check_param(bwt_s));
}

int main() {
  timer_(test(10));
  timer_(test(20));
  timer_(test(50));
  timer_(test(100));
  timer_(test(2000));
  timer_(test(5000));
  timer_(test(1000));
  timer_(test(2000));
  timer_(test(5000));
  timer_(test(10000));
  timer_(test(20000));
  timer_(test(50000));
}