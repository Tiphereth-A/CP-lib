#ifndef TIFA_LIBS_TREE_TREE
#define TIFA_LIBS_TREE_TREE

#include "../graph/adjlist.hpp"

namespace tifa_libs::graph {

template <class T = void>
class tree : public adjlist<T> {
  u32 rt;

 public:
  explicit tree(u32 n, u32 root = 0) : adjlist<T>(n), rt(root) {}

  u32& root() { return rt; }
  u32 root() const { return rt; }
};

}  // namespace tifa_libs::graph

#endif