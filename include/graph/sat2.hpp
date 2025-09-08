#ifndef TIFALIBS_GRAPH_SAT2
#define TIFALIBS_GRAPH_SAT2

#include "tarjan.hpp"

namespace tifa_libs::graph {

class sat2 {
  const u32 n;
  // vecptu e;
  tarjan tj;
  vvecu g;

 public:
  CEXPE sat2(u32 n) NE : n{n}, g(n * 2 + 1) {}

  // $(c_x = v_x) \lor (c_y = v_y)$
  CEXP void add(u32 x, bool vx, u32 y, bool vy) NE {
    x = x * 2 + vx, y = y * 2 + vy;
    // e.emplace_back(x ^ 1, y), e.emplace_back(y ^ 1, x);
    g[x ^ 1].push_back(y), g[y ^ 1].push_back(x);
  }
  // @return a, a_i == 1 if c_i is true else a_i == 0
  CEXP auto solve() NE {
    tj.build(g);
    std::optional ans{vecb(n)};
    flt_ (u32, i, 0, n)
      if (tj.scc_id[i * 2] == tj.scc_id[i * 2 + 1]) {
        ans = std::nullopt;
        return ans;
      } else ans.value()[i] = tj.scc_id[i * 2] > tj.scc_id[i * 2 + 1];
    return ans;
  }
};

}  // namespace tifa_libs::graph

#endif