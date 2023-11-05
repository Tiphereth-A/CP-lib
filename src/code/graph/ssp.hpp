#ifndef TIFA_LIBS_GRAPH_DINIC
#define TIFA_LIBS_GRAPH_DINIC

#include "../../code/util/util.hpp"

namespace tifa_libs::graph {

template <typename EW = u32, typename EC = i32>
class ssp {
  struct YYZ {
    u32 to;
    EW w;
    EC c;
    u32 inv;
  };
  const u32 N, S, T;
  vec<i64> dis;
  vec<EW> flow;
  vec<std::pair<u32, u32>> pre;
  bool spfa(u64 inflow) {
    dis = vec<i64>(N, std::numeric_limits<i64>::max() / 2 - 1);
    vec<bool> inq(N);
    std::queue<u32> q;
    dis[S] = 0, flow[S] = EW(inflow), flow[T] = 0, q.push(S), inq[S] = 1;
    while (!q.empty()) {
      u32 u = q.front();
      q.pop(), inq[u] = 0;
      for (u32 i = 0; i < e[u].size(); ++i) {
        auto v = e[u][i];
        if (dis[u] + v.c < dis[v.to] && v.w) {
          dis[v.to] = dis[u] + v.c;
          if (!inq[v.to]) q.push(v.to), inq[v.to] = 1;
          flow[v.to] = std::min(flow[u], v.w);
          pre[v.to] = {u, i};
        }
      }
    }
    return flow[T];
  }
  void update(u64& retflow, i64& retcost) {
    retflow += flow[T];
    for (u32 u = T; u != S; u = pre[u].first) {
      e[pre[u].first][pre[u].second].w -= flow[T];
      e[u][e[pre[u].first][pre[u].second].inv].w += flow[T];
      retcost += i64(flow[T]) * e[pre[u].first][pre[u].second].c;
    }
  }

 public:
  vvec<YYZ> e;
  ssp(const u32& n, const u32& s, const u32& t) : N(n), S(s), T(t), dis(), flow(n), pre(n), e(n) {}
  void add(u32 u, u32 v, EW w, EC c) {
    u32 temu = u32(e[u].size()), temv = u32(e[v].size());
    e[u].push_back({v, w, c, temv}), e[v].push_back({u, 0, -c, temu});
  }
  std::pair<u64, i64> operator()(u64 inflow = std::numeric_limits<u64>::max()) {
    u64 retflow = 0;
    i64 retcost = 0;
    bool flag = inflow == std::numeric_limits<EW>::max();
    while (spfa(flag ? inflow : inflow - retflow)) update(retflow, retcost);
    return {retflow, retcost};
  }
};

}  // namespace tifa_libs::graph

#endif