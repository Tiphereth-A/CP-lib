#ifndef TIFALIBS_GRAPH_DINIC
#define TIFALIBS_GRAPH_DINIC

#include "../util/alias_others.hpp"

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

  CEXPE dinic(u32 n) NE : n{n}, e(n) {}

  CEXP pttu add(u32 u, u32 v, T w, T rw = 0) NE {
    u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
    return {u, e[u].size() - 1};
  }
  template <class EW = u64>
  EW get(u32 s, u32 t) NE {
    EW ret = 0, flow;
    while (bfs(s, t))
      while ((flow = dfs<EW>(s, t))) ret += flow;
    return ret;
  }

 private:
  bool bfs(u32 s, u32 t) NE {
    dep = vecu(n, 0), dep[s] = 1;
    std::queue<u32> q({s});
    while (!q.empty()) {
      const u32 u = q.front();
      for (q.pop(); auto v : e[u])
        if (!dep[v.to] && v.w) dep[v.to] = dep[u] + 1, q.push(v.to);
    }
    cur = vecu(n, 0);
    return dep[t];
  }
  template <class EW>
  CEXP EW dfs(u32 u, u32 t, T lim = std::numeric_limits<T>::max()) NE {
    if (u == t || lim == 0) return (EW)lim;
    EW ret = 0;
    for (u32& i = cur[u]; i < e[u].size(); ++i)
      if (auto v = e[u][i]; dep[v.to] == dep[u] + 1 && v.w) {
        if (EW flow = dfs<EW>(v.to, t, min(v.w, lim)); flow) {
          if (e[u][i].w -= (T)flow, e[v.to][e[u][i].inv].w += (T)flow, ret += flow, lim -= (T)flow; !lim) break;
        } else dep[v.to] = 0;
      }
    return ret;
  }
};

}  // namespace tifa_libs::graph

#endif