#ifndef TIFALIBS_GRAPH_BLOSSOM
#define TIFALIBS_GRAPH_BLOSSOM

#include "../util/alias_others.hpp"

namespace tifa_libs::graph {

//! 1-indexed, [1, n]
class blossom {
  u32 n;
  vvecu g;
  vecu mate, first;
  vecb white;
  vecptu label;

 public:
  CEXPE blossom(u32 n) NE { init(n); }

  CEXP void init(u32 n_) NE {
    n = n_;
    g = vvecu(n + 1);
    mate = first = vecu(n + 1);
    label = vecptu(n + 1);
    white = vecb(n + 1);
  }
  CEXP void add_edge(u32 u, u32 v) NE { g[u].push_back(v), g[v].push_back(u); }
  vecptu operator()() NE {
    flt_ (u32, s, 1, n + 1)
      if (!mate[s]) augment(s);
    flt_ (u32, s, 1, n + 1)
      if (!mate[s] && !white[s]) assert(!augment(s));
    vecptu ans;
    flt_ (u32, s, 1, n + 1)
      if (s < mate[s]) ans.emplace_back(s, mate[s]);
    return ans;
  }

 private:
  CEXP u32 gf(u32 x) NE { return !white[first[x]] ? first[x] : first[x] = gf(first[x]); }
  CEXP void match(u32 p, u32 b) NE {
    if (swap(b, mate[p]); mate[b] != p) return;
    if (auto [k, v] = label[p]; !v) mate[b] = k, match(k, b);
    else match(k, v), match(v, k);
  }
  bool augment(u32 s) NE {
    assert(s), white[s] = 1, first[s] = 0, label[s] = {0, 0};
    std::queue<u32> q({s});
    while (!q.empty()) {
      const u32 a = q.front();
      for (q.pop(); auto b : g[a])
        if (assert(b); white[b]) {
          u32 x = gf(a), y = gf(b), lca = 0;
          while (x || y) {
            if (y) swap(x, y);
            if (label[x] == pttu{a, b}) {
              lca = x;
              break;
            }
            label[x] = {a, b}, x = gf(label[mate[x]].first);
          }
          for (u32 v : {gf(a), gf(b)})
            while (v != lca) {
              assert(!white[v]);
              q.push(v);
              white[v] = true, first[v] = lca;
              v = gf(label[mate[v]].first);
            }
        } else if (!mate[b]) {
          match(mate[b] = a, b), white = vecb(n + 1);
          return true;
        } else if (!white[mate[b]]) {
          white[mate[b]] = true;
          label[first[mate[b]] = b] = {0, 0}, label[mate[b]] = {a, 0};
          q.push(mate[b]);
        }
    }
    return false;
  }
};

}  // namespace tifa_libs::graph

#endif