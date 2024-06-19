#ifndef TIFALIBS_DS_LEFTIST_TREE
#define TIFALIBS_DS_LEFTIST_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, bool persistent = false>
class leftist_tree {
  u32 cnt;
  struct TIFA {
    u32 l, r, dist, rt;
    T w;
    bool del;
    CEXP TIFA() {}
    CEXP TIFA(u32 l, u32 r, u32 dist_, u32 rt_, T w_, bool del_ = false) : l(l), r(r), dist(dist_), rt(rt_), w(w_), del(del_) {}
  };

  CEXP u32 merge_(u32 x, u32 y) {
    if (!~x || !~y) return x & y;
    if (t[y].w < t[x].w || (t[y].w == t[x].w && x > y)) swap(x, y);
    if CEXP (persistent) t.push_back(t[x]), t.back().rt = x = (u32)t.size() - 1;
    if (t[x].r = merge_(t[x].r, y); !~t[x].l || t[t[x].r].dist > t[t[x].l].dist) swap(t[x].l, t[x].r);
    return t[x].dist = (!~t[x].r ? 0 : t[t[x].r].dist + 1), x;
  }
  CEXP void del(u32 x) {
    if (t[x].del = true, t[x].rt = merge_(t[x].l, t[x].r); ~t[x].l) t[t[x].l].rt = t[x].rt;
    if (~t[x].r) t[t[x].r].rt = t[x].rt;
  }

 public:
  vec<TIFA> t;

  CEXPE leftist_tree(vec<T> CR a) : t() {
    for (auto x : a) newheap(x);
  }
  CEXPE leftist_tree(u32 n = 0) : t() {
    t.reserve(n);
    flt_ (u32, i, 0, n) newheap();
  }

  CEXP u32 newheap(T w = T{}) { return t.emplace_back(-1_u32, -1_u32, 0, t.size(), w, false), (u32)t.size() - 1; }
  CEXP u32 gf(u32 x) { return t[x].rt == x ? x : t[x].rt = gf(t[x].rt); }
  CEXP bool same(u32 x, u32 y) {
    if (t[x].del || t[y].del) return false;
    if ((x = gf(x)) == (y = gf(y))) return false;
    return true;
  }
  CEXP void merge(u32 x, u32 y) {
    if (t[x].del || t[y].del) return;
    if ((x = gf(x)) == (y = gf(y))) return;
    t[x].rt = t[y].rt = merge_(x, y);
  }
  CEXP std::optional<T> pop(u32 x) {
    if (t[x].del) return {};
    T ret = t[x = gf(x)].w;
    return del(x), ret;
  }
};

}  // namespace tifa_libs::ds

#endif