#ifndef TIFALIBS_CONV_SUBSET
#define TIFALIBS_CONV_SUBSET

#include "../bit/cntr0.hpp"
#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T, u32 N>
struct conv_subset {
  using arr = std::array<T, N + 1>;
  vec<u32> pc;

  void add(arr& l, arr const& r, u32 d) const {
    for (u32 i = 0; i < d; ++i) l[i] += r[i];
  }

  void sub(arr& l, arr const& r, u32 d) const {
    for (u32 i = d; i <= N; ++i) l[i] -= r[i];
  }

 public:
  conv_subset() : pc(1u << N) {
    for (u32 i = 1; i < (1u << N); ++i) pc[i] = pc[i - (i & -i)] + 1;
  }

  void zeta(vec<arr>& a) const {
    u32 n = a.size();
    for (u32 w = 1; w < n; w *= 2)
      for (u32 k = 0; k < n; k += w * 2)
        for (u32 i = 0; i < w; ++i) add(a[k + w + i], a[k + i], pc[k + w + i]);
  }

  void mobius(vec<arr>& a) const {
    u32 n = a.size();
    for (u32 w = n >> 1; w; w /= 2)
      for (u32 k = 0; k < n; k += w * 2)
        for (u32 i = 0; i < w; ++i) sub(a[k + w + i], a[k + i], pc[k + w + i]);
  }

  vec<arr> lift(vec<T> const& a) const {
    vec<arr> A(a.size());
    for (u32 i = 0; i < a.size(); ++i) {
      std::fill(A[i].begin(), A[i].end(), T());
      A[i][pc[i]] = a[i];
    }
    return A;
  }

  vec<T> unlift(vec<arr> const& A) const {
    vec<T> a(A.size());
    for (u32 i = 0; i < A.size(); ++i) a[i] = A[i][pc[i]];
    return a;
  }

  void prod(vec<arr>& A, vec<arr> const& B) const {
    u32 n = A.size(), d = (u32)bit::cntr0(n);
    for (u32 i = 0; i < n; ++i) {
      arr c;
      for (u32 j = 0; j <= d; ++j)
        for (u32 k = 0; k <= d - j; ++k) c[j + k] += A[i][j] * B[i][k];
      A[i].swap(c);
    }
  }

  vec<T> conv(vec<T> const& a, vec<T> const& b) const {
    vec<arr> A = lift(a), B = lift(b);
    zeta(A), zeta(B);
    prod(A, B);
    mobius(A);
    return unlift(A);
  }
};

}  // namespace tifa_libs::math

#endif