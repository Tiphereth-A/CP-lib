#ifndef TIFA_LIBS_DS_FENWICK
#define TIFA_LIBS_DS_FENWICK

#include "../bit/cntr0.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick {
  size_t n;
  vec<T> a;
  constexpr size_t lowbit(size_t x) {
    return (size_t)1 << bit::cntr0(x);
  }

public:
  explicit constexpr fenwick(size_t sz = 0):
    n(sz), a(sz) {}
  constexpr void update(size_t pos, T x) {
    while (pos < n) {
      a[pos] += x;
      pos += lowbit(pos);
    }
  }
  constexpr T sum(size_t pos) {
    T ret = 0;
    while (pos) {
      ret += a[pos];
      pos -= lowbit(pos);
    }
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif