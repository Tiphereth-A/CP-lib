#ifndef TIFALIBS_UTIL_NDVEC
#define TIFALIBS_UTIL_NDVEC

#include "alias_others.hpp"

namespace tifa_libs {

template <u32 N, class T>
struct ndvec : vec<T> {
  static_assert(N, "N should be positive");
  arr<u32, N + 1> idxs;

  template <class... Ts>
  CEXPE ndvec(Ts &&...args) NE { resize(args...); }
  template <class... Ts>
  CEXP void resize(Ts &&...args) NE {
    static_assert(sizeof...(args) == N);
    u32 n = 0;
    ((idxs[n++] = (u32)args), ...);
    idxs[N] = 1;
    inclusive_scan(idxs.rbegin(), idxs.rend(), idxs.rbegin(), std::multiplies<>{}), vec<T>::resize(idxs[0]);
  }
  template <class... Ts>
  CEXP T &operator()(Ts &&...args) NE {
    static_assert(sizeof...(args) == N);
    u32 n = 0, idx = 0;
    ((idx += (u32)args * idxs[++n]), ...);
    return this->operator[](idx);
  }
  template <class... Ts>
  CEXP T CR operator()(Ts &&...args) CNE {
    static_assert(sizeof...(args) == N);
    u32 n = 0, idx = 0;
    ((idx += (u32)args * idxs[++n]), ...);
    return this->operator[](idx);
  }
};

}  // namespace tifa_libs

#endif