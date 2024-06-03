#ifndef TIFALIBS_COMB_EXLUCAS
#define TIFALIBS_COMB_EXLUCAS

#include "../math/isqrt.hpp"
#include "../nt/crt.hpp"
#include "lucas_pp.hpp"

namespace tifa_libs::math {

// Calculate binom(m, n) mod p, p can be ANY INTEGER
class ExLucas {
  const u32 m_;
  vecuu ms;
  vec<LucasPP> cs;

 public:
  explicit CEXP ExLucas(u32 md) : m_(md) {
    assert(md < 100'000'000);
    fle_ (u32, i, 2, isqrt(md))
      if (md % i == 0) {
        u32 j = 0, k = 1;
        while (md % i == 0) md /= i, ++j, k *= i;
        ms.push_back(k), cs.emplace_back(i, j);
      }
    if (md > 1) ms.push_back(md), cs.emplace_back(md, 1);
  }

  CEXP u64 operator()(i64 m, i64 n) const {
    if (m_ == 1 || m < n || n < 0) return 0;
    vecii b;
    for (b.reserve(cs.size()); auto CR i : cs) b.push_back((i64)i(m, n));
    return crt(b, ms)->first;
  }
};

}  // namespace tifa_libs::math

#endif