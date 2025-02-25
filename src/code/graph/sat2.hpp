#ifndef TIFALIBS_GRAPH_SAT2
#define TIFALIBS_GRAPH_SAT2

#include "../util/util.hpp"

namespace tifa_libs::graph {

class sat2 {
  const u32 n;
  vecu st;
  vecptu e;

 public:
  CEXPE sat2(u32 n) NE : n(n), st(2 * n + 1) {}

  // $(c_x = v_x) \lor (c_y = v_y)$
  CEXP void add(u32 x, bool vx, u32 y, bool vy) NE {
    x = x * 2 + vx, y = y * 2 + vy;
    e.emplace_back(x ^ 1, y), e.emplace_back(y ^ 1, x);
    ++st[x ^ 1], ++st[y ^ 1];
  }
  // @return a, a_i == 1 if c_i is true else a_i == 0
  CEXP std::optional<vecu> solve() NE {
    std::inclusive_scan(st.begin(), st.end(), st.begin()), *move_backward(st.begin(), st.end() - 1, st.end()).out = 0;
    vecu to(e.size());
    for (auto CR[u, v] : e) to[st[u]++] = v;
    *move_backward(st.begin(), st.end() - 1, st.end()).out = 0;
    vecu ans(n, -1_u32), lst;
    auto f = [&](auto &&f, u32 v) NE -> bool {
      lst.push_back(v / 2), ans[v / 2] = v & 1;
      flt_ (u32, i, st[v], st[v + 1])
        if (const u32 _ = to[i]; (~ans[_ / 2] && ans[_ / 2] != (_ & 1)) || (!~ans[_ / 2] && !f(f, _))) return false;
      return true;
    };
    flt_ (u32, i, 0, n)
      if (!~ans[i])
        if (lst.clear(); !f(f, 2 * i)) {
          for (u32 v : lst) ans[v] = -1_u32;
          if (!f(f, 2 * i + 1)) return {};
        }
    return ans;
  }
};

}  // namespace tifa_libs::graph

#endif