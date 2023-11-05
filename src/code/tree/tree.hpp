#ifndef TIFA_LIBS_TREE_TREE
#define TIFA_LIBS_TREE_TREE

#include "../graph/alist.hpp"

namespace tifa_libs::graph {

struct tree : alist {
  u32 root;

  explicit tree(usz n, u32 root = 0) : alist(n), root(root) {}
};

}  // namespace tifa_libs::graph

#endif