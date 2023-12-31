#ifndef TIFALIBS_MATH_BASIS_R
#define TIFALIBS_MATH_BASIS_R

#include "../util/util.hpp"

namespace tifa_libs::math {

template <std::floating_point FP>
class basisR {
  vvec<FP> base;
  constexpr bool is_zero(FP x) const { return std::abs(x) < eps_v; }

 public:
  const u32 vec_len;
  const FP eps_v;

  explicit constexpr basisR(u32 vec_len, FP eps_v = 1e-4) : vec_len(vec_len), eps_v(eps_v) {}

  constexpr vec<FP> &operator[](u32 i) { return base[i]; }
  constexpr vec<FP> const &operator[](u32 i) const { return base[i]; }
  constexpr vvec<FP> &data() { return base; }
  constexpr vvec<FP> const &data() const { return base; }

  constexpr u32 rank() const {
    u32 res = 0;
    for (u32 i = 0; i < base.size(); ++i)
      res += !is_zero(base[i][i]);
    return res;
  }

  constexpr bool insert(vec<FP> x) {
    x.resize(vec_len);
    bool status = false;
    for (u32 i = base.size() - 1; ~i; --i) {
      if (is_zero(x[i]))
        continue;
      if (!is_zero(base[i][i])) {
        FP __ = x[i] / base[i][i];
        x[i] = 0;
        for (u32 j = 0; j < i; ++j)
          x[j] -= base[i][j] * __;
      } else {
        for (u32 j = 0; j < i; ++j)
          if (!is_zero(x[j]) && !is_zero(base[j][j])) {
            FP __ = x[j] / base[j][j];
            x[j] = 0;
            for (u32 k = 0; k < j; ++k)
              x[k] -= base[j][k] * __;
          }
        for (u32 j = i + 1; j < base.size(); ++j)
          if (!is_zero(base[j][i]) && !is_zero(x[i])) {
            FP __ = base[j][i] / x[i];
            base[j][i] = 0;
            for (u32 k = 0; k < i; ++k)
              base[j][k] -= x[k] * __;
          }
        base[i] = x;
        status = true;
        break;
      }
    }
    return status;
  }

  // @return std::nullopt if x is linear independent with current basis, else
  // return the solution
  constexpr std::optional<vec<FP>> coord(vec<FP> x) {
    vec<FP> res(vec_len);
    for (u32 i = base.size() - 1; ~i; --i)
      if (!is_zero(x[i])) {
        if (is_zero(base[i][i]))
          return {};
        FP __ = x[i] / base[i][i];
        res[i] = __;
        x[i] = 0;
        for (u32 j = 0; j <= i; ++j)
          x[j] -= base[i][j] * __;
      }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif