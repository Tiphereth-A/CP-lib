#ifndef TIFALIBS_GRAPH_SAT2
#define TIFALIBS_GRAPH_SAT2

#include "../util/util.hpp"

namespace tifa_libs::graph {

class sat2 {
  const u32 n;
  vecu st;
  vecpt<u32> e;

 public:
  constexpr sat2(u32 n) : n(n), st(2 * n + 1) {}

  // $(c_x = v_x) \lor (c_y = v_y)$
  constexpr void add(u32 x, bool vx, u32 y, bool vy) {
    x = x * 2 + vx, y = y * 2 + vy;
    e.emplace_back(x ^ 1, y), e.emplace_back(y ^ 1, x);
    ++st[x ^ 1], ++st[y ^ 1];
  }

  // @return a, a_i == 1 if c_i is true else a_i == 0
  constexpr std::optional<vecu> solve() {
    std::partial_sum(st.begin(), st.end(), st.begin());
    *std::move_backward(st.begin(), st.end() - 1, st.end()) = 0;
    vecu tos(e.size());
    for (auto const &[u, v] : e) tos[st[u]++] = v;
    *std::move_backward(st.begin(), st.end() - 1, st.end()) = 0;
    vecu ans(n, -1_u32), lst;
    auto f = [&](auto &&f, u32 v) -> bool {
      lst.push_back(v / 2);
      ans[v / 2] = v & 1;
      for (u32 i = st[v]; i < st[v + 1]; ++i)
        if (u32 to = tos[i]; (~ans[to / 2] && ans[to / 2] != (to & 1)) || (!~ans[to / 2] && !f(f, to))) return false;
      return true;
    };
    for (u32 i = 0; i < n; ++i)
      if (!~ans[i]) {
        lst.clear();
        if (!f(f, 2 * i)) {
          for (u32 v : lst) ans[v] = -1_u32;
          if (!f(f, 2 * i + 1)) return {};
        }
      }
    return ans;
  }
};

}  // namespace tifa_libs::graph

#endif