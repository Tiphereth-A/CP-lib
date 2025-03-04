#ifndef TIFALIBS_GRAPH_DINIC
#define TIFALIBS_GRAPH_DINIC

#include "../util/alias_others.hpp"
#include "../util/traits_math.hpp"

namespace tifa_libs::graph {

template <class W = u32, class C = i32>
class ssp {
  struct TIFA {
    u32 to, inv;
    W w;
    C c;
  };
  const u32 N, S, T;
  vec<W> flow;
  vecptu pre;

  template <class EW>
  bool sssp(EW inflow) NE {
    using SW = std::make_signed_t<EW>;
    vec<SW> dis(N, inf_v<SW>);
    vecb inq(N);
    std::queue<u32> q({S});
    dis[S] = 0, flow[S] = W(inflow), flow[T] = 0, inq[S] = 1;
    while (!q.empty()) {
      const u32 u = q.front();
      q.pop(), inq[u] = 0;
      flt_ (u32, i, 0, (u32)e[u].size())
        if (auto v = e[u][i]; dis[u] + v.c < dis[v.to] && v.w) {
          if (dis[v.to] = dis[u] + v.c; !inq[v.to]) q.push(v.to), inq[v.to] = 1;
          flow[v.to] = min(flow[u], v.w), pre[v.to] = {u, i};
        }
    }
    return flow[T];
  }
  template <class EW, class EC>
  CEXP void update(EW& retflow, EC& retcost) NE {
    retflow += flow[T];
    for (u32 u = T; u != S; u = pre[u].first) {
      e[pre[u].first][pre[u].second].w -= flow[T];
      e[u][e[pre[u].first][pre[u].second].inv].w += flow[T];
      retcost += EC(flow[T]) * e[pre[u].first][pre[u].second].c;
    }
  }

 public:
  vvec<TIFA> e;

  CEXP ssp(u32 n, u32 s, u32 t) NE : N(n), S(s), T(t), flow(n), pre(n), e(n) {}

  CEXP void add(u32 u, u32 v, cT_(W) w, cT_(C) c) NE {
    const u32 lu = u32(e[u].size()), lv = u32(e[v].size());
    e[u].push_back({v, lv, w, c}), e[v].push_back({u, lu, 0, -c});
  }
  template <class EW = u64, class EC = i64>
  CEXP std::pair<EW, EC> get(EW inflow = std::numeric_limits<EW>::max()) NE {
    EW retflow = 0;
    EC retcost = 0;
    const bool flag = inflow == std::numeric_limits<W>::max();
    while (sssp(flag ? inflow : inflow - retflow)) update(retflow, retcost);
    return {retflow, retcost};
  }
};

}  // namespace tifa_libs::graph

#endif