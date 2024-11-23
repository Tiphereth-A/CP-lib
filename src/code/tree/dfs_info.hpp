#ifndef TIFALIBS_TREE_DFS_INFO
#define TIFALIBS_TREE_DFS_INFO

#include "../util/traits.hpp"

namespace tifa_libs::graph {

struct tdi_dfn {
  vecu dfn;

 protected:
  u32 cnt;
  CEXPE tdi_dfn(u32 n) : dfn(n), cnt{0} {}
  void init(u32 u, u32) { dfn[u] = cnt++; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct tdi_sz {
  vecu sz;

 protected:
  CEXPE tdi_sz(u32 n) : sz(n) {}
  void init(u32 u, u32) { sz[u] = 1; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32 to, u32 u, auto) { sz[u] += sz[to]; }
  void before_return(u32, u32) {}
};
struct tdi_fa {
  vecu fa;

 protected:
  CEXPE tdi_fa(u32 n) : fa(n) {}
  void init(u32 u, u32 f) { fa[u] = f; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct tdi_dep {
  vecu dep;

 protected:
  CEXPE tdi_dep(u32 n) : dep(n) {}
  void init(u32, u32) {}
  void pre_dfs(u32 to, u32 u, auto) { dep[to] = dep[u] + 1; }
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct tdi_maxson : tdi_sz {
  vecu maxson;

 protected:
  CEXPE tdi_maxson(u32 n) : tdi_sz(n), maxson(n, n) {}
  void init(u32 u, u32 f) { tdi_sz::init(u, f); }
  void pre_dfs(u32 to, u32 u, auto w) { tdi_sz::pre_dfs(to, u, w); }
  void post_dfs(u32 to, u32 u, auto w) {
    if (tdi_sz::post_dfs(to, u, w); maxson[u] == (u32)maxson.size() || sz[to] > sz[maxson[u]]) maxson[u] = to;
  }
  void before_return(u32 u, u32 f) { tdi_sz::before_return(u, f); }
};
struct tdi_maxdfn {
  vecu maxdfn;

 protected:
  u32 cnt;
  CEXPE tdi_maxdfn(u32 n) : maxdfn(n), cnt{0} {}
  void init(u32, u32) { ++cnt; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32 u, u32) { maxdfn[u] = cnt - 1; }
};
struct tdi_euler {
  vecu euler;

 protected:
  u32 cnt;
  CEXPE tdi_euler(u32 n) : euler(n), cnt{0} {}
  void init(u32 u, u32) { euler[cnt++] = u; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct tdi_go {
  vvecu go;

 protected:
  CEXP static u32 N = 21;
  CEXPE tdi_go(u32 n) : go(n, vecu(N, n)) { assert(n < 1u << N); }
  void init(u32 u, u32 f) {
    go[u][0] = f;
    for (u32 i = 1; i < N && go[u][i - 1] < go.size(); ++i) go[u][i] = go[go[u][i - 1]][i - 1];
  }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
template <tree_c G>
struct tdi_dis {
  using w_t = std::conditional_t<std::is_void_v<TPN G::w_t>, u32, TPN G::w_t>;
  vec<w_t> dis;

 protected:
  CEXPE tdi_dis(u32 n) : dis(n) {}
  void init(u32, u32) {}
  void pre_dfs(u32 to, u32 u, auto w) { dis[to] = dis[u] + w; }
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};

template <tree_c G, class... Ts>
struct tree_dfs_info : Ts... {
  using w_t = std::conditional_t<std::is_void_v<TPN G::w_t>, u32, TPN G::w_t>;
  CEXPE tree_dfs_info(G CR tree) : Ts(tree.size())... { dfs(tree, tree.root); }

 private:
  void dfs(G CR g, u32 u, u32 fa = -1_u32) {
    if CEXP ((..., Ts::init(u, fa)); adjlistw_c<G>) {
      for (auto [v, w] : g[u])
        if (v != fa) (..., Ts::pre_dfs(v, u, w)), dfs(g, v, u), (..., Ts::post_dfs(v, u, w));
    } else
      for (auto v : g[u])
        if ((u32)v != fa) (..., Ts::pre_dfs((u32)v, u, 1)), dfs(g, (u32)v, u), (..., Ts::post_dfs((u32)v, u, 1));
    (..., Ts::before_return(u, fa));
  }
};

}  // namespace tifa_libs::graph

#endif