#ifndef TIFALIBS_TREE_DFS_INFO
#define TIFALIBS_TREE_DFS_INFO

#include "../util/traits.hpp"

namespace tifa_libs::graph {

struct td_dfn_tag {
  vecu dfn;

 protected:
  u32 cnt;
  CEXPE td_dfn_tag(u32 n) : dfn(n), cnt{0} {}
  void init(u32 u, u32) { dfn[u] = cnt++; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_sz_tag {
  vecu sz;

 protected:
  CEXPE td_sz_tag(u32 n) : sz(n) {}
  void init(u32 u, u32) { sz[u] = 1; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32 to, u32 u, auto) { sz[u] += sz[to]; }
  void before_return(u32, u32) {}
};
struct td_fa_tag {
  vecu fa;

 protected:
  CEXPE td_fa_tag(u32 n) : fa(n) {}
  void init(u32 u, u32 f) { fa[u] = f; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_dep_tag {
  vecu dep;

 protected:
  CEXPE td_dep_tag(u32 n) : dep(n) {}
  void init(u32, u32) {}
  void pre_dfs(u32 to, u32 u, auto) { dep[to] = dep[u] + 1; }
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_maxson_tag : td_sz_tag {
  vecu maxson;

 protected:
  CEXPE td_maxson_tag(u32 n) : td_sz_tag(n), maxson(n, n) {}
  void init(u32 u, u32 f) { td_sz_tag::init(u, f); }
  void pre_dfs(u32 to, u32 u, auto w) { td_sz_tag::pre_dfs(to, u, w); }
  void post_dfs(u32 to, u32 u, auto w) {
    if (td_sz_tag::post_dfs(to, u, w); maxson[u] == (u32)maxson.size() || sz[to] > sz[maxson[u]]) maxson[u] = to;
  }
  void before_return(u32 u, u32 f) { td_sz_tag::before_return(u, f); }
};
struct td_maxdfn_tag {
  vecu maxdfn;

 protected:
  u32 cnt;
  CEXPE td_maxdfn_tag(u32 n) : maxdfn(n), cnt{0} {}
  void init(u32, u32) { ++cnt; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32 u, u32) { maxdfn[u] = cnt - 1; }
};
struct td_euler_tag {
  vecu euler;

 protected:
  u32 cnt;
  CEXPE td_euler_tag(u32 n) : euler(n), cnt{0} {}
  void init(u32 u, u32) { euler[cnt++] = u; }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
struct td_go_tag {
  vvecu go;

 protected:
  CEXP static u32 N = 21;
  CEXPE td_go_tag(u32 n) : go(n, vecu(N, n)) { assert(n < 1u << N); }
  void init(u32 u, u32 f) {
    go[u][0] = f;
    for (u32 i = 1; i < N && go[u][i - 1] < go.size(); ++i) go[u][i] = go[go[u][i - 1]][i - 1];
  }
  void pre_dfs(u32, u32, auto) {}
  void post_dfs(u32, u32, auto) {}
  void before_return(u32, u32) {}
};
template <tree_c G>
struct td_dis_tag {
  using w_t = std::conditional_t<std::is_void_v<TPN G::w_t>, u32, TPN G::w_t>;
  vec<w_t> dis;

 protected:
  CEXPE td_dis_tag(u32 n) : dis(n) {}
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