#ifndef TIFALIBS_GRAPH_DINIC
#define TIFALIBS_GRAPH_DINIC

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T = u32>
class dinic {
  struct TIFA {
    u32 to;
    T w;
    u32 inv;
  };
  const u32 n;

 public:
  vvec<TIFA> e;
  vecu dep, cur;

  CEXP dinic(u32 n) : n(n), e(n) {}

  CEXP ptt<u32> add(u32 u, u32 v, T w, T rw = 0) {
    u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
    return {u, e[u].size() - 1};
  }
  template <class EW = u64>
  EW get(u32 s, u32 t) {
    EW ret = 0, flow;
    while (bfs(s, t))
      while ((flow = dfs<EW>(s, t))) ret += flow;
    return ret;
  }

 private:
  bool bfs(u32 s, u32 t) {
    dep = vecu(n, 0);
    std::queue<u32> q({s});
    dep[s] = 1;
    while (!q.empty()) {
      const u32 u = q.front();
      q.pop();
      for (auto v : e[u])
        if (!dep[v.to] && v.w) dep[v.to] = dep[u] + 1, q.push(v.to);
    }
    cur = vecu(n, 0);
    return dep[t];
  }
  template <class EW>
  CEXP EW dfs(u32 u, u32 t, T lim = std::numeric_limits<T>::max()) {
    if (u == t || lim == 0) return lim;
    EW ret = 0;
    for (u32& i = cur[u]; i < e[u].size(); ++i) {
      auto v = e[u][i];
      if (dep[v.to] == dep[u] + 1 && v.w) {
        EW flow = dfs<EW>(v.to, t, min(v.w, lim));
        if (flow) {
          e[u][i].w -= flow, e[v.to][e[u][i].inv].w += flow;
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