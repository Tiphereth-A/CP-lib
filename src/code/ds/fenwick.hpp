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
  //! [1, sz)
  explicit constexpr fenwick(size_t sz):
    a(sz) { assert(sz > 1); }
  //! [1, pos)
  constexpr void add(size_t pos, T const &x) {
    if (!pos) return;
    for (pos = std::clamp(pos, size_t(1), a.size() - 1); pos < a.size(); pos += lowbit(pos)) a[pos] += x;
  }
  //! [1, pos)
  constexpr T sum(size_t pos) {
    T ret = 0;
    for (pos = std::clamp(pos, size_t(0), a.size() - 1); pos; pos -= lowbit(pos)) ret += a[pos];
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif