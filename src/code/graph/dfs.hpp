#ifndef TIFALIBS_GRAPH_DFS_ALIST
#define TIFALIBS_GRAPH_DFS_ALIST

#include "../util/traits.hpp"

namespace tifa_libs::graph {
namespace dfs_impl_ {
template <adjlist_c G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs_(G CR g, u32 u, u32 fa, Fb&& init, Fp&& pre_dfs, Fs&& post_dfs, Fr&& before_return) {
  if CEXP (init(u, fa); adjlistw_c<G>) {
    for (auto [v, w] : g[u])
      if (v != fa) pre_dfs(v, u, w), dfs_(g, v, u, std::forward<Fb>(init), std::forward<Fp>(pre_dfs), std::forward<Fs>(post_dfs), std::forward<Fr>(before_return)), post_dfs(v, u, w);
  } else
    for (auto v : g[u])
      if ((u32)v != fa) pre_dfs((u32)v, u), dfs_(g, (u32)v, u, std::forward<Fb>(init), std::forward<Fp>(pre_dfs), std::forward<Fs>(post_dfs), std::forward<Fr>(before_return)), post_dfs((u32)v, u);
  before_return(u, fa);
}
}  // namespace dfs_impl_

template <adjlist_c G, class Fb, class Fp, class Fs, class Fr>
CEXP void dfs(G CR g, u32 start, Fb&& init, Fp&& pre_dfs, Fs&& post_dfs, Fr&& before_return) { dfs_impl_::dfs_(g, start, -1_u32, std::forward<Fb>(init), std::forward<Fp>(pre_dfs), std::forward<Fs>(post_dfs), std::forward<Fr>(before_return)); }

}  // namespace tifa_libs::graph

#endif