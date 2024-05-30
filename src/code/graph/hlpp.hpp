#ifndef TIFALIBS_GRAPH_HLPP
#define TIFALIBS_GRAPH_HLPP

#include "../util/util.hpp"

namespace tifa_libs::graph {

template <class T = u32>
class hlpp {
  static constexpr u32 inf = 0x3f3f3f3f;
  struct TIFA {
    u32 to;
    T w, inv;
  };
  vecu h, gap;

  const u32 n, s, t;
  u32 level;
  vvecu B;

  CEXP u32 select() {
    while (~level && B[level].empty()) --level;
    return ~level ? B[level].back() : 0;
  }

 public:
  vvec<TIFA> e;
  vec<T> exf;

  CEXP hlpp(u32 n, u32 s, u32 t) : n(n), s(s), t(t), level(0), B(n), e(n), exf(n + 1) {}

  CEXP ptt<u32> add(u32 u, u32 v, T w, T rw = 0) {
    const u32 lstu = (u32)e[u].size(), lstv = (u32)e[v].size();
    e[u].push_back({v, w, lstv}), e[v].push_back({u, rw, lstu});
    return {u, e[u].size() - 1};
  }
  T get() {
    if (!bfs_init()) return 0;
    gap = vecu(n, 0);
    flt_ (u32, i, 0, n)
      if (h[i] != inf) ++gap[h[i]];
    h[s] = n;
    push(s);
    u32 u;
    while ((u = select())) {
      B[level].pop_back();
      if (push(u)) {
        if (!--gap[h[u]])
          flt_ (u32, i, 0, n)
            if (i != s && h[i] > h[u] && h[i] < n + 1) h[i] = n + 1;
        relabel(u);
      }
    }
    return exf[t];
  }

 private:
  bool bfs_init() {
    h = vecu(n, inf);
    std::queue<u32> q({t});
    h[t] = 0;
    while (!q.empty()) {
      u32 u = q.front();
      q.pop();
      for (auto [to, w, lstv] : e[u])
        if (e[to][lstv].w && h[to] > h[u] + 1) h[to] = h[u] + 1, q.push(to);
    }
    return h[s] != inf;
  }
  CEXP bool push(u32 u) {
    bool init = u == s;
    for (auto &[to, w, lstv] : e[u]) {
      if (!w || (init == false && h[u] != h[to] + 1) || h[to] == inf) continue;
      T k = init ? w : min(w, exf[u]);
      if (to != s && to != t && !exf[to]) B[h[to]].push_back(to), level = max(level, h[to]);
      exf[u] -= k, exf[to] += k, w -= k, e[to][lstv].w += k;
      if (!exf[u]) return 0;
    }
    return 1;
  }
  CEXP void relabel(u32 u) {
    h[u] = inf;
    for (auto [to, w, _] : e[u])
      if (w) h[u] = min(h[u], h[to]);
    if (++h[u] < n) {
      B[h[u]].push_back(u);
      level = max(level, h[u]);
      ++gap[h[u]];
    }
  }
};

}  // namespace tifa_libs::graph

#endif