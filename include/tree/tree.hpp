#ifndef TIFALIBS_TREE_TREE
#define TIFALIBS_TREE_TREE

#include "../graph/alist.hpp"

namespace tifa_libs::graph {

struct tree : alist<> {
  u32 root;
  CEXPE tree(u32 n, u32 root = 0) NE : alist(n), root(root) {}
};
template <class T>
struct treew : alistw<T> {
  u32 root;
  CEXPE treew(u32 n, u32 root = 0) NE : alistw<T>(n), root(root) {}
};

}  // namespace tifa_libs::graph

#endif