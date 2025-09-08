#ifndef TIFALIBS_MATH_DU_SIEVE
#define TIFALIBS_MATH_DU_SIEVE

#include "../math/do_quot.hpp"
#include "../util/alias_others.hpp"

namespace tifa_libs::math {

template <class T, class SF, class SG, class SH>
requires requires(u64 x, SF f, SG g, SH h) {
  { f(x) } -> std::same_as<T>;
  { g(x) } -> std::same_as<T>;
  { h(x) } -> std::same_as<T>;
}
class du_sieve {
  const u64 sf_max;
  SF sf;
  SG sg;
  SH sh;
  hmap<u64, T> mem;

  CEXP T calc(u64 x) NE {
    if (x <= sf_max) return sf(x);
    if (auto d = mem.find(x); d != end(mem)) return d->second;
    T ans = 0;
    do_quot(x, [&](u64 l, u64 r, u64 q) NE { ans += (sg(r) - sg(l - 1)) * calc(q); }, 2);
    return mem[x] = (ans = sh(x) - ans) /= sg(1);
  }

 public:
  CEXP du_sieve(u64 sf_max, SF sf, SG sg, SH sh) NE : sf_max(sf_max), sf(sf), sg(sg), sh(sh) {}

  CEXP T operator()(u64 n) NE { retif_((!n) [[unlikely]], 0, calc(n)); }
};

}  // namespace tifa_libs::math

#endif