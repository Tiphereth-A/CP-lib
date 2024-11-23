#ifndef TIFALIBS_MATH_rgcd
#define TIFALIBS_MATH_rgcd

#include "../math/isqrt.hpp"
#include "lsieve.hpp"

namespace tifa_libs::math {

class rgcd {
  struct ls_rgcd {
    struct F3 {
      u32 a, b, c;
      CEXP F3(u32 _a = 0, u32 _b = 0, u32 _c = 0) : a(_a), b(_b), c(_c) {}
    };
    vec<F3> fs;

   protected:
    CEXPE ls_rgcd(u32 n) : fs(n) { (n > 1) && ((fs[1] = {1, 1, 1}), 0); }

    CEXP void prime(u32 p) { fs[p] = {1, 1, p}; }
    CEXP void coprime(u32 i, u32 j) {
      F3 &now = fs[i * j];
      now = fs[i];
      if ((now.a *= j) > now.b) swap(now.a, now.b);
      if (now.b > now.c) swap(now.b, now.c);
    }
    CEXP void not_coprime(u32 i, u32 j) {
      F3 &now = fs[i * j];
      now = fs[i];
      if ((now.a *= j) > now.b) swap(now.a, now.b);
      if (now.b > now.c) swap(now.b, now.c);
    }
  };

  lsieve<ls_rgcd> s;
  vvecu g_;

 public:
  CEXPE rgcd(u32 n) : s(n), g_(isqrt(n) + 1, vvecu::value_type(isqrt(n) + 1)) {
    flt_ (u32, i, 1, (u32)g_.size()) {
      g_[i][0] = g_[0][i] = g_[i][i] = (u32)i;
      flt_ (u32, j, 1, i) g_[i][j] = g_[j][i] = g_[j][i % j];
    }
  }

  CEXP u32 operator()(u32 x, u32 y) const {
    if (assert(x < s.fs.size() && y < s.fs.size()); x < g_.size() && y < g_.size()) return g_[x][y];
    u32 ans = 1, _;
    for (u32 i : {s.fs[x].a, s.fs[x].b, s.fs[x].c}) y /= (_ = i < g_.size() ? g_[i][y % i] : (y % i == 0) * (i - 1) + 1), ans *= _;
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif