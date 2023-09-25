#ifndef TIFA_LIBS_MATH_EXLUCAS
#define TIFA_LIBS_MATH_EXLUCAS

#include "../util/util.hpp"

#include "crt.hpp"
#include "isqrt.hpp"
#include "lucas_pp.hpp"

namespace tifa_libs::math {

// Calculate binom(m, n) mod p, p can be ANY INTEGER
class ExLucas {
  u32 m_;
  vec<u64> ms;
  vec<LucasPP> cs;

public:
  explicit ExLucas(u32 md):
    m_(md) {
    assert(md < 100'000'000);
    for (u32 i = 2, ed_ = isqrt(md); i <= ed_; ++i)
      if (md % i == 0) {
        u32 j = 0, k = 1;
        while (md % i == 0) {
          md /= i;
          ++j;
          k *= i;
        }
        ms.push_back(k);
        cs.emplace_back(i, j);
      }
    if (md > 1) {
      ms.push_back(md);
      cs.emplace_back(md, 1);
    }
  }

  u64 operator()(i64 m, i64 n) const {
    if (m_ == 1 || m < n || n < 0) return 0;
    vec<i64> b;
    b.reserve(cs.size());
    for (const auto &i : cs) b.push_back((i64)i(m, n));
    return crt(b, ms)->first;
  }
};

}  // namespace tifa_libs::math

#endif