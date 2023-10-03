#ifndef TIFA_LIBS_DS_FENWICK
#define TIFA_LIBS_DS_FENWICK

#include "../bit/cntr0.hpp"
#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class fenwick {
  vec<T> a;
  constexpr size_t lowbit(size_t x) { return (size_t)1 << bit::cntr0(x); }

public:
  explicit constexpr fenwick(size_t sz = 0):
    a(sz) {}
  constexpr void add(size_t pos, T x) {
    assert(pos > 1 && pos < a.size());
    for (; pos < a.size(); pos += lowbit(pos)) a[pos] += x;
  }
  constexpr T sum(size_t pos) {
    assert(pos > 1 && pos < a.size());
    T ret = 0;
    for (; pos; pos -= lowbit(pos)) ret += a[pos];
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif