#ifndef TIFA_LIBS_TREE_TREEW
#define TIFA_LIBS_TREE_TREEW

#include "../graph/alistw.hpp"

namespace tifa_libs::graph {

template <class T>
struct treew : alistw<T> {
  u32 root;

  explicit treew(usz n, u32 root = 0) : alistw<T>(n), root(root) {}
};

}  // namespace tifa_libs::graph

#endif