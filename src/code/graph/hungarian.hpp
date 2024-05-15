#ifndef TIFALIBS_GRAPH_HUNGARIAN
#define TIFALIBS_GRAPH_HUNGARIAN

#include "../util/util.hpp"

namespace tifa_libs::graph {

// Given J jobs and W workers ($J\leq W$), computes the minimum cost to assign each prefix of jobs to distinct workers.
// @tparam T a type large enough to represent integers on the order of $J\max(|g|)$
// @param g a matrix of dimensions JxW such that g[j][w] = cost to assign j-th job to w-th worker (possibly negative)
// @return a vector of length J, with the j-th entry equaling the minimum cost to assign the first (j+1) jobs to distinct workers
// Time: $O(J^2W)$
template <class T>
CEXP vec<T> hungarian(vvec<T> CR g, T INF = std::numeric_limits<T>::max()) {
  u32 J = (u32)g.size(), W = (u32)g[0].size();
  assert(J <= W);
  vecu job(W + 1, -1_u32);
  vec<T> ys(J), yt(W + 1), ret;
  flt_ (u32, j_now, 0, J) {
    u32 w_now = W;
    job[w_now] = j_now;
    vec<T> min_to(W + 1, INF);
    vecu prv(W + 1, -1_u32);
    vecb vis(W + 1);
    while (~job[w_now]) {
      vis[w_now] = true;
      u32 j = job[w_now], w_nxt = -1_u32;
      T _ = INF;
      flt_ (u32, w, 0, W) {
        if (!vis[w]) {
          if (min_to[w] > g[j][w] - ys[j] - yt[w]) min_to[w] = g[j][w] - ys[j] - yt[w], prv[w] = w_now;
          if (_ > min_to[w]) _ = min_to[w_nxt = w];
        }
      }
      fle_ (u32, w, 0, W) {
        if (vis[w]) ys[job[w]] += _, yt[w] -= _;
        else min_to[w] -= _;
      }
      w_now = w_nxt;
    }
    for (u32 w; ~w_now && ~prv[w_now]; w_now = w) job[w_now] = job[w = prv[w_now]];
    ret.push_back(-yt[W]);
  }
  return ret;
}

}  // namespace tifa_libs::graph

#endif