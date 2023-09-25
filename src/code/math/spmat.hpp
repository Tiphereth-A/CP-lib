#ifndef TIFA_LIBS_SPARSE_MAT
#define TIFA_LIBS_SPARSE_MAT

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class T>
struct spmat_node {
  size_t r, c;
  T val;

  explicit spmat_node(size_t r = 0, size_t c = 0, T const &val = T{}):
    r(r), c(c), val(val) {}
};

template <class T>
class spmat {
  vec<spmat_node<T>> d;

public:
  using node = spmat_node<T>;

  explicit spmat() {}
  explicit spmat(vec<node> const &d):
    d(d) {}

  constexpr vec<node> data() const { return d; }
  constexpr vec<node> &data() { return d; }
  void insert(size_t r, size_t c, T const &val) { d.emplace_back(r, c, val); }
};

}  // namespace tifa_libs::math

#endif