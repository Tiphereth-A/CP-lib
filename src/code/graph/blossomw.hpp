#ifndef TIFALIBS_GRAPH_BLOSSOMW
#define TIFALIBS_GRAPH_BLOSSOMW

#include "../util/util.hpp"

namespace tifa_libs::graph {

//! 1-indexed, [1, n]
template <class T>
struct blossomw {
  struct TIFA {
    u32 u, v;
    T w;
  };
  vvec<TIFA> g;

  u32 n, nx;
  vec<T> lab;
  vecu match, slack, st, par, s, aux;
  vvecu flo_from, flo;
  std::queue<u32> q;

  blossomw(u32 n) { init(n); }
  void init(u32 n_) {
    n = n_, g = vvec<TIFA>(n * 2 + 1, vec<TIFA>(n * 2 + 1));
    lab = vec<T>(n * 2 + 1), match = vecu(n * 2 + 1), slack = vecu(n * 2 + 1), st = vecu(n * 2 + 1);
    par = vecu(n * 2 + 1), s = vecu(n * 2 + 1), aux = vecu(n * 2 + 1);
    flo_from = vvecu(n * 2 + 1, vecu(n + 1)), flo = vvecu(n * 2 + 1);
    fle_ (u32, u, 1, n)
      fle_ (u32, v, 1, n) g[u][v] = {u, v, 0};
  }

  CEXP void add_edge(u32 u, u32 v, T w) { g[u][v].w = g[v][u].w = w; }
  // {u, v, w}
  auto operator()(T inf = std::numeric_limits<T>::max()) {
    nx = n, st[0] = 0;
    fle_ (u32, i, 1, 2 * n) aux[i] = 0;
    fle_ (u32, i, 1, n) match[i] = 0, st[i] = i, flo[i].clear();
    T wmax = 0;
    fle_ (u32, u, 1, n)
      fle_ (u32, v, 1, n)
        flo_from[u][v] = (u == v ? u : 0), wmax = max(wmax, g[u][v].w);
    fle_ (u32, u, 1, n) lab[u] = wmax;
    while (matching(inf));
    vec<std::tuple<u32, u32, T>> ans;
    fle_ (u32, u, 1, n)
      if (match[u] && match[u] < u) ans.emplace_back(u, match[u], g[u][match[u]].w);
    return ans;
  }

 private:
  CEXP T e_delta(TIFA CR e) { return lab[e.u] + lab[e.v] - g[e.u][e.v].w * 2; }
  CEXP void upd_slack(u32 u, u32 x) {
    if (!slack[x] || e_delta(g[u][x]) < e_delta(g[slack[x]][x])) slack[x] = u;
  }
  CEXP void set_slack(u32 x) {
    slack[x] = 0;
    fle_ (u32, u, 1, n)
      if (g[u][x].w > 0 && st[u] != x && s[st[u]] == 0) upd_slack(u, x);
  }
  void q_push(u32 x) {
    if (x <= n) q.push(x);
    else
      for (auto t : flo[x]) q_push(t);
  }
  CEXP void set_st(u32 x, u32 b) {
    st[x] = b;
    if (x > n)
      for (auto t : flo[x]) set_st(t, b);
  }
  CEXP u32 get_pr(u32 b, u32 xr) {
    if (u32 pr = u32(std::ranges::find(flo[b], xr) - flo[b].begin()); pr & 1) {
      std::reverse(flo[b].begin() + 1, flo[b].end());
      return u32(flo[b].size() - pr);
    } else return pr;
  }
  CEXP void set_match(u32 u, u32 v) {
    auto [eu, ev, _] = g[u][v];
    match[u] = ev;
    if (u <= n) return;
    u32 xr = flo_from[u][eu], pr = get_pr(u, xr);
    flt_ (u32, i, 0, pr) set_match(flo[u][i], flo[u][i ^ 1]);
    set_match(xr, v), std::rotate(flo[u].begin(), flo[u].begin() + pr, flo[u].end());
  }
  CEXP void augment(u32 u, u32 v) {
    while (1) {
      u32 xnv = st[match[u]];
      set_match(u, v);
      if (!xnv) return;
      set_match(xnv, st[par[xnv]]);
      u = st[par[xnv]], v = xnv;
    }
  }
  u32 lca(u32 u, u32 v) {
    static u32 t = 0;
    for (++t; u || v; swap(u, v)) {
      if (!u) continue;
      if (aux[u] == t) return u;
      aux[u] = t;
      if ((u = st[match[u]])) u = st[par[u]];
    }
    return 0;
  }
  CEXP void add_blossom(u32 u, u32 anc, u32 v) {
    u32 b = n + 1;
    while (b <= nx && st[b]) ++b;
    if (b > nx) ++nx;
    lab[b] = s[b] = 0, match[b] = match[anc], flo[b] = {anc};
    auto blossom = [&](u32 x) {
      for (u32 y; x != anc; x = st[par[y]]) flo[b].push_back(x), flo[b].push_back(y = st[match[x]]), q_push(y);
    };
    blossom(u), std::reverse(flo[b].begin() + 1, flo[b].end()), blossom(v), set_st(b, b);
    fle_ (u32, x, 1, nx) g[b][x].w = g[x][b].w = 0;
    fle_ (u32, x, 1, n) flo_from[b][x] = 0;
    for (auto xs : flo[b]) {
      fle_ (u32, x, 1, nx)
        if (g[b][x].w == 0 || e_delta(g[xs][x]) < e_delta(g[b][x])) g[b][x] = g[xs][x], g[x][b] = g[x][xs];
      fle_ (u32, x, 1, n)
        if (flo_from[xs][x]) flo_from[b][x] = xs;
    }
    set_slack(b);
  }
  CEXP void expand_blossom(u32 b) {
    for (auto t : flo[b]) set_st(t, t);
    const u32 xr = flo_from[b][g[b][par[b]].u], pr = get_pr(b, xr);
    for (u32 i = 0; i < pr; i += 2) {
      u32 xs = flo[b][i], xns = flo[b][i + 1];
      par[xs] = g[xns][xs].u, s[xs] = 1, s[xns] = slack[xs] = slack[xns] = 0, q_push(xns);
    }
    s[xr] = 1, par[xr] = par[b];
    flt_ (u32, i, pr + 1, (u32)flo[b].size()) {
      u32 xs = flo[b][i];
      s[xs] = -1_u32, set_slack(xs);
    }
    st[b] = 0;
  }
  bool on_found_edge(TIFA CR e) {
    const u32 u = st[e.u], v = st[e.v];
    if (!~s[v]) {
      par[v] = e.u, s[v] = 1, slack[v] = 0;
      u32 nu = st[match[v]];
      s[nu] = slack[nu] = 0, q_push(nu);
    } else if (!s[v]) {
      if (u32 anc = lca(u, v); !anc) return augment(u, v), augment(v, u), 1;
      else add_blossom(u, anc, v);
    }
    return 0;
  }
  bool matching(T inf) {
    q = std::queue<u32>();
    fle_ (u32, x, 1, nx) {
      s[x] = -1_u32, slack[x] = 0;
      if (st[x] == x && !match[x]) par[x] = s[x] = 0, q_push(x);
    }
    if (q.empty()) return 0;
    while (1) {
      while (!q.empty()) {
        const u32 u = q.front();
        q.pop();
        if (s[st[u]] == 1) continue;
        fle_ (u32, v, 1, n)
          if (g[u][v].w > 0 && st[u] != st[v]) {
            if (!e_delta(g[u][v])) {
              if (on_found_edge(g[u][v])) return 1;
            } else upd_slack(u, st[v]);
          }
      }
      T d = inf;
      fle_ (u32, b, n + 1, nx)
        if (st[b] == b && s[b] == 1) d = min(d, lab[b] / 2);
      fle_ (u32, x, 1, nx)
        if (st[x] == x && slack[x]) {
          if (!~s[x]) d = min(d, e_delta(g[slack[x]][x]));
          else if (!s[x]) d = min(d, e_delta(g[slack[x]][x]) / 2);
        }
      fle_ (u32, u, 1, n) {
        if (!s[st[u]]) {
          if (lab[u] <= d) return 0;
          lab[u] -= d;
        } else if (s[st[u]] == 1) lab[u] += d;
      }
      fle_ (u32, b, n + 1, nx)
        if (st[b] == b && ~s[b]) lab[b] += (!s[b] ? 1 : -1) * d * 2;
      q = std::queue<u32>();
      fle_ (u32, x, 1, nx)
        if (st[x] == x && slack[x] && st[slack[x]] != x && !e_delta(g[slack[x]][x]))
          if (on_found_edge(g[slack[x]][x])) return 1;
      fle_ (u32, b, n + 1, nx)
        if (st[b] == b && s[b] == 1 && !lab[b]) expand_blossom(b);
    }
    return 0;
  }
};

}  // namespace tifa_libs::graph

#endif