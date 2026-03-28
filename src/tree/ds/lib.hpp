#pragma once

#include "../../graph/ds/graph_c/lib.hpp"

namespace tifa_libs {

template <graph_c graph_t>
struct tree : graph_t {
  u32 root;
  CEXP tree(graph_t CR g, u32 root = 0) NE : graph_t(g), root(root) {}
  CEXP tree(graph_t&& g, u32 root = 0) NE : graph_t(std::move(g)), root(root) {}
  CEXPE tree(u32 n, u32 root = 0) NE : graph_t(n), root(root) {}
};
CONCEPT_GRAPH(tree, tree);

}  // namespace tifa_libs
