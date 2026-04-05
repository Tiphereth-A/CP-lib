// competitive-verifier: STANDALONE

#include "../../../src/edh/prufer/inv.hpp"
#include "../../../src/edh/prufer/seq.hpp"
#include "../../../src/util/rand/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;

void test(u32 n) {
  rand_gen<u32> g(1, n);
  vecu seq(n - 1);
  flt_ (u32, i, 1, n - 1) seq[i] = g();
  timer_(auto tree_seq = prufer_inv(seq));
  timer_(auto prufer_seq = prufer(tree_seq));
  check(prufer_seq, seq, check_param(tree_seq));
}

int main() {
  timer_(test(10));
  timer_(test(100));
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