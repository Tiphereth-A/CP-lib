#ifndef TIFALIBS_GRAPH_DINIC
#define TIFALIBS_GRAPH_DINIC

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class EW = u32>
class dinic {
  struct TIFA {
    u32 to;
    EW w, inv;
  };
  const u32 N;

 public:
  vvec<TIFA> e;
  vecu dep, cur;

  CEXP dinic(u32 n) : N(n), e(n) {}

  CEXP ptt<u32> add(u32 u, u32 v, EW w, EW rw = 0) {
    u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
    return {u, e[u].size() - 1};
  }
  u64 operator()(u32 s, u32 t) {
    u64 ret = 0, flow;
    while (bfs(s, t))
      while ((flow = dfs(s, t))) ret += flow;
    return ret;
  }

 private:
  bool bfs(u32 s, u32 t) {
    dep = vecu(N, 0);
    std::queue<u32> q({s});
    dep[s] = 1;
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (auto v : e[u])
        if (!dep[v.to] && v.w) dep[v.to] = dep[u] + 1, q.push(v.to);
    }
    cur = vecu(N, 0);
    return dep[t];
  }
  CEXP u64 dfs(u32 u, u32 t, EW lim = std::numeric_limits<EW>::max()) {
    if (u == t || lim == 0) return lim;
    u64 ret = 0;
    for (u32& i = cur[u]; i < e[u].size(); ++i) {
      auto v = e[u][i];
      if (dep[v.to] == dep[u] + 1 && v.w) {
        u64 flow = dfs(v.to, t, min(v.w, lim));
        if (flow) {
          e[u][i].w -= flow;
          e[v.to][e[u][i].inv].w += flow;
          ret += flow, lim -= flow;
          if (!lim) break;
        } else dep[v.to] = 0;
      }
    }
    return ret;
  }
};

}  // namespace tifa_libs::graph

#endif