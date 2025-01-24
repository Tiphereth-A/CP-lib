#ifndef TIFALIBS_TREE_HEIGHT
#define TIFALIBS_TREE_HEIGHT

#include "../util/traits.hpp"

namespace tifa_libs::graph {

template <tree_c G>
CEXP auto tree_height(G CR tr) NE {
  using T = TPN G::w_t;
  const u32 n = (u32)tr.size();
  vvec<T> _(n);
  flt_ (u32, i, 0, n) _[i].resize(tr[i].size(), T(-1));
  auto f = [&](auto &&f, u32 u, u32 fa) NE -> T {
    T ans = 0;
    auto &&es = tr[u];
    flt_ (u32, i, 0, (u32)es.size())
      if CEXP (treew_c<G>) {
        if (auto &&[v, w] = es[i]; v != fa) ans = max(ans, (_[u][i] = (_[u][i] == T(-1) ? f(f, v, u) : _[u][i])) + w);
      } else if (auto v = es[i]; v != fa) ans = max(ans, (_[u][i] = (_[u][i] == T(-1) ? f(f, v, u) : _[u][i])) + 1);
    return ans;
  };
  vec<T> h(n);
  flt_ (u32, i, 0, n) h[i] = f(f, i, i);
  return h;
}

}  // namespace tifa_libs::graph

#endif