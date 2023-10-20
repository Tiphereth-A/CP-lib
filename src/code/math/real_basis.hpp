#ifndef TIFA_LIBS_MATH_REAL_BASIS
#define TIFA_LIBS_MATH_REAL_BASIS

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class FP>
class basis_R {
  static_assert(std::is_floating_point_v<FP>);

  vvec<FP> base;
  bool is_zero(FP x) const { return std::abs(x) < EPS; }

 public:
  const usz vec_len;
  const FP EPS;

  constexpr explicit basis_R(usz vec_len, FP EPS = 1e-4) : vec_len(vec_len), EPS(EPS) {}

  constexpr vec<FP> &operator[](usz i) { return base[i]; }
  constexpr vec<FP> operator[](usz i) const { return base[i]; }
  constexpr vvec<FP> &data() { return base; }
  constexpr vvec<FP> data() const { return base; }

  constexpr usz rank() const {
    usz res = 0;
    for (usz i = 0; i < base.size(); ++i) res += !is_zero(base[i][i]);
    return res;
  }

  constexpr bool insert(vec<FP> x) {
    x.resize(vec_len);
    bool status = false;
    for (usz i = base.size() - 1; ~i; --i) {
      if (is_zero(x[i])) continue;
      if (!is_zero(base[i][i])) {
        FP __ = x[i] / base[i][i];
        x[i] = 0;
        for (usz j = 0; j < i; ++j) x[j] -= base[i][j] * __;
      } else {
        for (usz j = 0; j < i; ++j)
          if (!is_zero(x[j]) && !is_zero(base[j][j])) {
            FP __ = x[j] / base[j][j];
            x[j] = 0;
            for (usz k = 0; k < j; ++k) x[k] -= base[j][k] * __;
          }
        for (usz j = i + 1; j < base.size(); ++j)
          if (!is_zero(base[j][i]) && !is_zero(x[i])) {
            FP __ = base[j][i] / x[i];
            base[j][i] = 0;
            for (usz k = 0; k < i; ++k) base[j][k] -= x[k] * __;
          }
        base[i] = x;
        status = true;
        break;
      }
    }
    return status;
  }

  // @return std::nullopt if x is linear independent with current basis, else return the solution
  constexpr std::optional<vec<FP>> coord(vec<FP> x) {
    vec<FP> res(vec_len);
    for (usz i = base.size() - 1; ~i; --i)
      if (!is_zero(x[i])) {
        if (is_zero(base[i][i])) return {};
        FP __ = x[i] / base[i][i];
        res[i] = __;
        x[i] = 0;
        for (usz j = 0; j <= i; ++j) x[j] -= base[i][j] * __;
      }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif