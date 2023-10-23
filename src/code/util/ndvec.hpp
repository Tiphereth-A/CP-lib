#ifndef TIFA_LIBS_UTIL_NDVEC
#define TIFA_LIBS_UTIL_NDVEC

#include "util.hpp"

namespace tifa_libs {

template <usz N, class Tp>
struct ndvec : public vec<ndvec<N - 1, Tp>> {
  static_assert(N, "N should be positive");
  using base_tp = ndvec<N - 1, Tp>;
  using base = vec<base_tp>;
  template <class T, typename... Ts>
  ndvec(T &&n, Ts &&...args) : base(n, base_tp(args...)) {}
  constexpr usz dim() const { return N; }
  template <class T>
  void fill(T &&x) {
    for (auto &i : *this) i.fill(x);
  }
};
template <class Tp>
struct ndvec<1, Tp> : public vec<Tp> {
  using base = vec<Tp>;
  template <class T>
  ndvec(T &&n) : base(n) {}
  constexpr usz dim() const { return 1; }
  template <class T>
  void fill(T &&x) { std::fill(this->begin(), this->end(), x); }
};

}  // namespace tifa_libs

#endif