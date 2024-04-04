#ifndef TIFALIBS_DS_LEFTIST_TREE
#define TIFALIBS_DS_LEFTIST_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T>
class leftist_tree {
  u32 cnt;
  struct YYZ {
    std::array<u32, 2> son{};
    u32 dist, rt;
    T w;
    bool del;
    constexpr YYZ() {}
    constexpr YYZ(std::array<u32, 2> SON, u32 DIST, u32 RT, T W, bool DEL = false) : son(SON), dist(DIST), rt(RT), w(W), del(DEL) {}
  };

  constexpr u32 merge_(u32 x, u32 y) {
    if (x == -1u) return y;
    if (y == -1u) return x;
    if (t[y].w < t[x].w || (t[y].w == t[x].w && x > y)) std::swap(x, y);
    t[x].son[1] = merge_(t[x].son[1], y);
    if (t[x].son[0] == -1u || t[t[x].son[1]].dist > t[t[x].son[0]].dist) std::swap(t[x].son[0], t[x].son[1]);
    t[x].dist = (t[x].son[1] == -1u ? 0 : t[t[x].son[1]].dist + 1);
    return x;
  }
  void del(u32 x) {
    t[x].del = true;
    t[x].rt = merge_(t[x].son[0], t[x].son[1]);
    if (t[x].son[0] != -1u) t[t[x].son[0]].rt = t[x].rt;
    if (t[x].son[1] != -1u) t[t[x].son[1]].rt = t[x].rt;
  }

 public:
  vec<YYZ> t;

  leftist_tree(vec<T> const& a) : t() {
    for (auto x : a) newheap(x);
  }
  leftist_tree() : t() {}

  void newheap(T w) {
    t.emplace_back(std::array<u32, 2>{-1u, -1u}, 0, t.size(), w, false);
  }
  u32 gf(u32 x) { return t[x].rt == x ? x : t[x].rt = gf(t[x].rt); }
  bool same(u32 x, u32 y) {
    if (t[x].del || t[y].del) return false;
    x = gf(x), y = gf(y);
    if (x == y) return false;
    return true;
  }
  void merge(u32 x, u32 y) {
    if (t[x].del || t[y].del) return;
    x = gf(x), y = gf(y);
    if (x == y) return;
    t[x].rt = t[y].rt = merge_(x, y);
  }
  T pop(u32 x) {
    if (t[x].del) return std::numeric_limits<T>::max();
    x = gf(x);
    T ret = t[x].w;
    del(x);
    return ret;
  }
};

}  // namespace tifa_libs::ds

#endif