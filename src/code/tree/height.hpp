#ifndef TIFALIBS_TREE_HEIGHT
#define TIFALIBS_TREE_HEIGHT

#include "../graph/alist.hpp"

namespace tifa_libs::graph {

template <class G>
constexpr auto tree_height(G const &tr) {
  u32 n = (u32)tr.g.size();
  using T = typename G::weight_type;
  vec<T> h(n);
  vvec<T> _(n);
  for (u32 i = 0; i < n; ++i) _[i].resize(tr.g[i].size(), T(-1));
  auto f = [&](auto &&f, u32 u, u32 fa) -> T {
    T ans = 0;
    auto &&es = tr.g[u];
    for (u32 i = 0; i < es.size(); ++i)
      if constexpr (std::is_base_of_v<alist, G>) {
        if (auto &&v = es[i]; v != fa) ans = std::max(ans, (_[u][i] = _[u][i] == T(-1) ? f(f, v, u) : _[u][i]) + 1);
      } else {
        if (auto &&[v, w] = es[i]; v != fa) ans = std::max(ans, (_[u][i] = _[u][i] == T(-1) ? f(f, v, u) : _[u][i]) + w);
      }
    return ans;
  };
  for (u32 i = 0; i < n; ++i) h[i] = f(f, i, 0);
  return h;
}

}  // namespace tifa_libs::graph

#endif