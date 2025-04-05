#ifndef TIFALIBS_LALG_BASIS_R
#define TIFALIBS_LALG_BASIS_R

#include "../util/alias_others.hpp"
#include "../util/func_fp.hpp"

namespace tifa_libs::math {

template <class T>
struct basisR {
  const u32 vec_len;
  vvec<T> basis;

  CEXPE basisR(u32 vec_len) NE : vec_len{vec_len}, basis(vec_len, vec<T>(vec_len)) {}

  // maybe need setting a larger eps (such as 1e-4) first
  CEXP bool insert(vec<T> x) NE {
    x.resize(vec_len);
    bool status = 0;
    for (u32 i = (u32)basis.size() - 1; ~i; --i) {
      if (is_zero(x[i])) continue;
      if (!is_zero(basis[i][i])) {
        const T _ = x[i] / basis[i][i];
        x[i] = 0;
        flt_ (u32, j, 0, i) x[j] -= basis[i][j] * _;
      } else {
        flt_ (u32, j, 0, i)
          if (!is_zero(x[j]) && !is_zero(basis[j][j])) {
            const T _ = x[j] / basis[j][j];
            x[j] = 0;
            flt_ (u32, k, 0, j) x[k] -= basis[j][k] * _;
          }
        flt_ (u32, j, i + 1, (u32)basis.size())
          if (!is_zero(basis[j][i]) && !is_zero(x[i])) {
            const T _ = basis[j][i] / x[i];
            basis[j][i] = 0;
            flt_ (u32, k, 0, i) basis[j][k] -= x[k] * _;
          }
        basis[i] = x, status = 1;
        break;
      }
    }
    return status;
  }
  CEXP bool test(vec<T> x) CNE {
    for (u32 i = (u32)basis.size() - 1; ~i; --i) {
      if (is_zero(x[i])) continue;
      if (!is_zero(basis[i][i])) {
        const T _ = x[i] / basis[i][i];
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
  CEXP std::optional<vec<T>> coord(vec<T> x) {
    vec<T> res(vec_len);
    for (u32 i = basis.size() - 1; ~i; --i)
      if (!is_zero(x[i])) {
        if (is_zero(basis[i][i])) return {};
        const T _ = x[i] / basis[i][i];
        res[i] = _, x[i] = 0;
        flt_ (u32, j, 0, i + 1) x[j] -= basis[i][j] * _;
      }
    return res;
  }
};

}  // namespace tifa_libs::math

#endif