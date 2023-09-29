#ifndef TIFA_LIBS_MATH_RGCD
#define TIFA_LIBS_MATH_RGCD

#include "isqrt.hpp"
#include "linear_seive.hpp"

namespace tifa_libs::math {

class RGCD {
  struct F3 {
    u32 a, b, c;
    F3(u32 _a = 0, u32 _b = 0, u32 _c = 0):
      a(_a), b(_b), c(_c) {}
  };

  vec<F3> fs;
  vec<vec<u32>> g_;

public:
  explicit RGCD(u32 n):
    fs(n), g_(isqrt(n) + 1, decltype(g_)::value_type(isqrt(n) + 1)) {
    fs[1] = {1, 1, 1};
    linear_seive(
      n,
      [this](u32 p) { fs[p] = {1, 1, p}; },
      [this](u32 i, u32 j) {
        F3 &now = fs[i * j];
        now = fs[i];
        if ((now.a *= j) > now.b) std::swap(now.a, now.b);
        if (now.b > now.c) std::swap(now.b, now.c);
      },
      [this]([[maybe_unused]] u32 i, [[maybe_unused]] u32 j) {
        F3 &now = fs[i * j];
        now = fs[i];
        if ((now.a *= j) > now.b) std::swap(now.a, now.b);
        if (now.b > now.c) std::swap(now.b, now.c);
      });
    for (size_t i = 1; i < g_.size(); ++i) {
      g_[i][0] = g_[0][i] = g_[i][i] = (u32)i;
      for (size_t j = 1; j < i; ++j) g_[i][j] = g_[j][i] = g_[j][i % j];
    }
  }

  u32 operator()(u32 x, u32 y) const {
    assert(x < fs.size() && y < fs.size());
    if (x < g_.size() && y < g_.size()) return g_[x][y];
    u32 ans = 1, _;
    for (u32 i : {fs[x].a, fs[x].b, fs[x].c}) {
      y /= (_ = i < g_.size() ? g_[i][y % i] : (y % i == 0) * (i - 1) + 1);
      ans *= _;
    }
    return ans;
  }
};

}  // namespace tifa_libs::math

#endif