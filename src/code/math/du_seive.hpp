#ifndef TIFA_LIBS_MATH_DU_SEIVE
#define TIFA_LIBS_MATH_DU_SEIVE

#include "../util/hash_splitmix64.hpp"
#include "do_quot.hpp"

namespace tifa_libs::math {

template <class T, class SF, class SG, class SH>
class du_sieve {
  const u64 sf_max;
  SF sf;
  SG sg;
  SH sh;
  hmap<u64, T> mem;

  T calc(u64 x) {
    if (x <= sf_max) return sf(x);
    if (auto d = mem.find(x); d != mem.end()) return d->second;
    T ans = 0;
    do_quot(
        x,
        [&](u64 l, u64 r, u64 q) { ans += (sg(r) - sg(l - 1)) * calc(q); },
        2);
    return mem[x] = (ans = sh(x) - ans) /= sg(1);
  }

 public:
  du_sieve(u64 sf_max, SF sf, SG sg, SH sh) : sf_max(sf_max), sf(sf), sg(sg), sh(sh) {}

  T operator()(u64 n) { return !n ? 0 : calc(n); }
};

}  // namespace tifa_libs::math

#endif