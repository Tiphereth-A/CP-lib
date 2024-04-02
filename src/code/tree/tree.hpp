#ifndef TIFALIBS_TREE_TREE
#define TIFALIBS_TREE_TREE

#include "../graph/alist.hpp"

namespace tifa_libs::graph {

struct tree : alist<false> {
  u32 root;

  explicit constexpr tree(u32 n, u32 root = 0) : alist(n), root(root) {}
};

}  // namespace tifa_libs::graph

#endif