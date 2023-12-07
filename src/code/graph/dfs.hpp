#ifndef TIFALIBS_GRAPH_DFS_ALIST
#define TIFALIBS_GRAPH_DFS_ALIST

#include "alist.hpp"

namespace tifa_libs::graph {

namespace dfs_impl_ {

template <class G, class Fb, class Fp, class Fs, class Fr>
void dfs_(G const& fg, u32 u, u32 fa, Fb&& init, Fp&& pre_dfs, Fs&& post_dfs, Fr&& before_return) {
  init(u, fa);
  for (auto v : fg.g[u])
    if constexpr (std::is_base_of_v<alist, G>) {
      if (v != fa) {
        pre_dfs(v, u);
        dfs_(fg, v, u, std::forward<Fb>(init), std::forward<Fp>(pre_dfs), std::forward<Fs>(post_dfs), std::forward<Fr>(before_return));
        post_dfs(v, u);
      }
    } else {
      if (v.first != fa) {
        pre_dfs(v.first, v.second, u);
        dfs_(fg, v.first, u, std::forward<Fb>(init), std::forward<Fp>(pre_dfs), std::forward<Fs>(post_dfs), std::forward<Fr>(before_return));
        post_dfs(v.first, v.second, u);
      }
    }
  before_return(u, fa);
}

}  // namespace dfs_impl_

template <class G, class Fb, class Fp, class Fs, class Fr>
void dfs(G const& fg, u32 start, Fb&& init, Fp&& pre_dfs, Fs&& post_dfs, Fr&& before_return) { dfs_impl_::dfs_(fg, start, -1_u32, std::forward<Fb>(init), std::forward<Fp>(pre_dfs), std::forward<Fs>(post_dfs), std::forward<Fr>(before_return)); }

}  // namespace tifa_libs::graph

#endif