#ifndef TIFALIBS_MATH_BASIS_R
#define TIFALIBS_MATH_BASIS_R

#include "../util/fp_func.hpp"

namespace tifa_libs::math {

template <std::floating_point FP>
struct basisR {
  vvec<FP> basis;
  const u32 vec_len;

  CEXPE basisR(u32 vec_len) NE : vec_len(vec_len) {}

  CEXP bool insert(vec<FP> x) NE {
    x.resize(vec_len);
    bool status = 0;
    for (u32 i = (u32)basis.size() - 1; ~i; --i) {
      if (is_zero(x[i])) continue;
      if (!is_zero(basis[i][i])) {
        const FP _ = x[i] / basis[i][i];
        x[i] = 0;
        flt_ (u32, j, 0, i) x[j] -= basis[i][j] * _;
      } else {
        flt_ (u32, j, 0, i)
          if (!is_zero(x[j]) && !is_zero(basis[j][j])) {
            const FP _ = x[j] / basis[j][j];
            x[j] = 0;
            flt_ (u32, k, 0, j) x[k] -= basis[j][k] * _;
          }
        flt_ (u32, j, i + 1, (u32)basis.size())
          if (!is_zero(basis[j][i]) && !is_zero(x[i])) {
            const FP _ = basis[j][i] / x[i];
            basis[j][i] = 0;
            flt_ (u32, k, 0, i) basis[j][k] -= x[k] * _;
          }
        basis[i] = x, status = 1;
        break;
      }
    }
    return status;
  }
  CEXP bool test(vec<FP> x) CNE {
    for (u32 i = (u32)basis.size() - 1; ~i; --i) {
      if (is_zero(x[i])) continue;
      if (!is_zero(basis[i][i])) {
        const FP _ = x[i] / basis[i][i];
        x[i] = 0;
        flt_ (u32, j, 0, i) x[j] -= basis[i][j] * _;
      } else return 0;
    }
    return 1;
  }
  CEXP u32 rank() CNE {
    u32 res = 0;
    flt_ (u32, i, 0, (u32)basis.size()) res += !is_zero(basis[i][i]);
    return res;
  }
  // @return std::nullopt if x is linear independent with current basis, else
  // return the solution
  CEXP std::optional<vec<FP>> coord(vec<FP> x) {
    vec<FP> res(vec_len);
    for (u32 i = basis.size() - 1; ~i; --i)
      if (!is_zero(x[i])) {
        if (is_zero(basis[i][i])) return {};
        const FP _ = x[i] / basis[i][i];
        res[i] = _, x[i] = 0;
        flt_ (u32, j, 0, i + 1) x[j] -= basis[i][j] * _;
      }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif