#ifndef TIFALIBS_DS_LEFTIST_TREE
#define TIFALIBS_DS_LEFTIST_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class leftist_tree {
  u32 cnt;
  struct YYZ {
    u32 l, r;
    arr<u32, 2> son{};
    u32 dist, rt;
    T w;
    bool del;
    constexpr YYZ() {}
    constexpr YYZ(u32 l, u32 r, u32 dist_, u32 rt_, T w_, bool del_ = false) : l(l), r(r), dist(dist_), rt(rt_), w(w_), del(del_) {}
  };

  constexpr u32 merge_(u32 x, u32 y) {
    if (x == -1u) return y;
    if (y == -1u) return x;
    if (t[y].w < t[x].w || (t[y].w == t[x].w && x > y)) std::swap(x, y);
    t[x].r = merge_(t[x].r, y);
    if (t[x].l == -1_u32 || t[t[x].r].dist > t[t[x].l].dist) std::swap(t[x].l, t[x].r);
    t[x].dist = (t[x].r == -1u ? 0 : t[t[x].r].dist + 1);
    return x;
  }
  void del(u32 x) {
    t[x].del = true;
    t[x].rt = merge_(t[x].l, t[x].r);
    if (t[x].l != -1u) t[t[x].l].rt = t[x].rt;
    if (t[x].r != -1u) t[t[x].r].rt = t[x].rt;
  }

 public:
  vec<YYZ> t;

  constexpr explicit leftist_tree(vec<T> const& a) : t() {
    for (auto x : a) newheap(x);
  }
  constexpr explicit leftist_tree() : t() {}

  void newheap(T w) {
    t.emplace_back(-1u, -1u, 0, t.size(), w, false);
  }
  u32 gf(u32 x) { return t[x].rt == x ? x : t[x].rt = gf(t[x].rt); }
  bool same(u32 x, u32 y) {
    if (t[x].del || t[y].del) return false;
    if ((x = gf(x)) == (y = gf(y))) return false;
    return true;
  }
  void merge(u32 x, u32 y) {
    if (t[x].del || t[y].del) return;
    if ((x = gf(x)) == (y = gf(y))) return;
    t[x].rt = t[y].rt = merge_(x, y);
  }
  T pop(u32 x) {
    if (t[x].del) return std::numeric_limits<T>::max();
    T ret = t[x = gf(x)].w;
    del(x);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif