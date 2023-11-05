#ifndef TIFA_LIBS_GRAPH_DINIC
#define TIFA_LIBS_GRAPH_DINIC

#include "../../code/util/util.hpp"

namespace tifa_libs::graph {

template <typename EW = u32>
class dinic {
  struct YYZ {
    u32 to;
    EW w;
    u32 inv;
  };
  const u32 N, S, T;
  vec<u32> dep, cur;
  bool bfs() {
    dep = vec<u32>(N, 0);
    std::queue<u32> q;
    dep[S] = 1, q.push(S);
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (auto v : e[u])
        if (!dep[v.to] && v.w) dep[v.to] = dep[u] + 1, q.push(v.to);
    }
    cur = vec<u32>(N, 0);
    return dep[T];
  }
  u64 dfs(u32 u, EW limit = std::numeric_limits<EW>::max()) {
    if (u == T || limit == 0) return limit;
    u64 ret = 0;
    for (u32& i = cur[u]; i < e[u].size(); ++i) {
      auto v = e[u][i];
      if (dep[v.to] == dep[u] + 1 && v.w) {
        u64 flow = dfs(v.to, std::min(v.w, limit));
        if (flow) {
          e[u][i].w -= flow;
          e[v.to][e[u][i].inv].w += flow;
          ret += flow, limit -= flow;
          if(!limit) break;
        }
        else dep[v.to] = 0;
      }
    }
    return ret;
  }

 public:
  vvec<YYZ> e;
  dinic(const u32& n, const u32& s, const u32& t) : N(n), S(s), T(t), e(n) {}
  void add(u32 u, u32 v, EW w) {
    u32 temu = u32(e[u].size()), temv = u32(e[v].size());
    e[u].push_back({v, w, temv}), e[v].push_back({u, 0, temu});
  }
  u64 operator()() {
    u64 ret = 0, flow;
    while (bfs())
      while ((flow = dfs(S))) ret += flow;
    return ret;
  }
};

}  // namespace tifa_libs::graph

#endif