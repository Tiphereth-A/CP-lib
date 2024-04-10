#ifndef TIFALIBS_CONV_SUBSET
#define TIFALIBS_CONV_SUBSET

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, u32 N>
struct conv_subset {
  using arr_t = arr<T, N + 1>;
  vecu pc;

  constexpr void add(arr_t& l, arr_t const& r, u32 d) const {
    for (u32 i = 0; i < d; ++i) l[i] += r[i];
  }
  constexpr void sub(arr_t& l, arr_t const& r, u32 d) const {
    for (u32 i = d; i <= N; ++i) l[i] -= r[i];
  }

 public:
  explicit constexpr conv_subset() : pc(1u << N) {
    for (u32 i = 1; i < (1u << N); ++i) pc[i] = pc[i - (i & -i)] + 1;
  }

  constexpr void zeta(vec<arr_t>& a) const {
    for (u32 w = 1; w < (u32)a.size(); w *= 2)
      for (u32 k = 0; k < (u32)a.size(); k += w * 2)
        for (u32 i = 0; i < w; ++i) add(a[k + w + i], a[k + i], pc[k + w + i]);
  }

  constexpr void mobius(vec<arr_t>& a) const {
    u32 n = (u32)a.size();
    for (u32 w = n >> 1; w; w /= 2)
      for (u32 k = 0; k < n; k += w * 2)
        for (u32 i = 0; i < w; ++i) sub(a[k + w + i], a[k + i], pc[k + w + i]);
  }

  constexpr vec<arr_t> lift(vec<T> const& a) const {
    vec<arr_t> A(a.size());
    for (u32 i = 0; i < a.size(); ++i) {
      std::ranges::fill(A[i], T());
      A[i][pc[i]] = a[i];
    }
    return A;
  }

  constexpr vec<T> unlift(vec<arr_t> const& A) const {
    vec<T> a(A.size());
    for (u32 i = 0; i < A.size(); ++i) a[i] = A[i][pc[i]];
    return a;
  }

  constexpr void prod(vec<arr_t>& A, vec<arr_t> const& B) const {
    u32 n = (u32)A.size(), d = (u32)std::countr_zero(n);
    for (u32 i = 0; i < n; ++i) {
      arr_t c;
      for (u32 j = 0; j <= d; ++j)
        for (u32 k = 0; k <= d - j; ++k) c[j + k] += A[i][j] * B[i][k];
      A[i].swap(c);
    }
  }

  constexpr vec<T> conv(vec<T> const& a, vec<T> const& b) const {
    vec<arr_t> A = lift(a), B = lift(b);
    zeta(A), zeta(B);
    prod(A, B);
    mobius(A);
    return unlift(A);
  }
};

}  // namespace tifa_libs::math

#endif