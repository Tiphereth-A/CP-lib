#ifndef TIFALIBS_CONV_SUBSET
#define TIFALIBS_CONV_SUBSET

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, u32 N>
struct conv_subset {
  using arr_t = arr<T, N + 1>;
  vecu pc;

  CEXP void add(arr_t& l, cT_(arr_t) r, u32 d) const {
    flt_ (u32, i, 0, d) l[i] += r[i];
  }
  CEXP void sub(arr_t& l, cT_(arr_t) r, u32 d) const {
    flt_ (u32, i, d, N + 1) l[i] -= r[i];
  }

 public:
  CEXPE conv_subset() : pc(1u << N) {
    for (u32 i = 1; i < (1u << N); ++i) pc[i] = pc[i - (i & -i)] + 1;
  }

  CEXP void zeta(vec<arr_t>& a) const {
    for (u32 w = 1; w < (u32)a.size(); w *= 2)
      for (u32 k = 0; k < (u32)a.size(); k += w * 2)
        flt_ (u32, i, 0, w) add(a[k + w + i], a[k + i], pc[k + w + i]);
  }
  CEXP void mobius(vec<arr_t>& a) const {
    const u32 n = (u32)a.size();
    for (u32 w = n >> 1; w; w /= 2)
      for (u32 k = 0; k < n; k += w * 2)
        flt_ (u32, i, 0, w) sub(a[k + w + i], a[k + i], pc[k + w + i]);
  }
  CEXP vec<arr_t> lift(spn<T> a) const {
    vec<arr_t> A(a.size());
    flt_ (u32, i, 0, (u32)a.size()) std::ranges::fill(A[i], T()), A[i][pc[i]] = a[i];
    return A;
  }
  CEXP vec<T> unlift(spn<arr_t> A) const {
    vec<T> a(A.size());
    flt_ (u32, i, 0, (u32)A.size()) a[i] = A[i][pc[i]];
    return a;
  }
  CEXP void prod(vec<arr_t>& A, spn<arr_t> B) const {
    u32 n = (u32)A.size(), d = (u32)std::countr_zero(n);
    flt_ (u32, i, 0, n) {
      arr_t c;
      flt_ (u32, j, 0, d + 1)
        for (u32 k = 0; k <= d - j; ++k) c[j + k] += A[i][j] * B[i][k];
      A[i].swap(c);
    }
  }
  CEXP vec<T> conv(spn<T> a, spn<T> b) const {
    vec<arr_t> A = lift(a), B = lift(b);
    return zeta(A), zeta(B), prod(A, B), mobius(A), unlift(A);
  }
};

}  // namespace tifa_libs::math

#endif