#ifndef TIFA_LIBS_DS_LINK_CUT_TREE
#define TIFA_LIBS_DS_LINK_CUT_TREE

#include "../util/util.hpp"

namespace tifa_libs::ds {

template <class T, auto op>
class link_cut_tree {
  // function in private: index of node should start from 1
  // waite for updating
  struct YYZ {
    T w;
    u32 fa, rev;
    std::array<u32, 2> son;
  };
  vec<YYZ> tr;
  vec<T> a;
  void update_(u32 x) { tr[x].w = op(op(tr[tr[x].son[0]].w, a[x]), tr[tr[x].son[1]].w); }
  bool which_(u32 x) { return tr[tr[x].fa].son[1] == x; }
  bool noroot_(u32 x) { return tr[tr[x].fa].son[0] == x || tr[tr[x].fa].son[1] == x; }
  void all_update_(u32 x) {
    if (x) std::swap(tr[x].son[0], tr[x].son[1]), tr[x].rev ^= 1;
  }
  void pushdown_(u32 x) {
    if (tr[x].rev) all_update_(tr[x].son[0]), all_update_(tr[x].son[1]), tr[x].rev ^= 1;
  }
  void ppushdown_(u32 x) {
    if (noroot_(x)) ppushdown_(tr[x].fa);
    pushdown_(x);
  }
  void rotate(u32 x) {
    u32 y = tr[x].fa, z = tr[y].fa, ySon = which_(x), zSon = which_(y), B = tr[x].son[ySon ^ 1];
    if (noroot_(y)) tr[z].son[zSon] = x;
    tr[x].fa = z;
    tr[y].fa = x, tr[x].son[ySon ^ 1] = y;
    if (B) tr[B].fa = y;
    tr[y].son[ySon] = B;
    update_(y);
  }
  void splay_(u32 x) {
    ppushdown_(x);
    while (noroot_(x)) {
      u32 fa = tr[x].fa;
      if (noroot_(fa)) {
        if (which_(fa) ^ which_(x)) rotate(x);
        else rotate(fa);
      }
      rotate(x);
    }
    update_(x);
  }
  void access_(u32 x) {
    for (u32 y = 0; x; x = tr[y = x].fa) splay_(x), tr[x].son[1] = y, update_(x);
  }
  void makeroot_(u32 x) { access_(x), splay_(x), all_update_(x); }
  u32 findroot_(u32 x) {
    access_(x), splay_(x);
    while (tr[x].son[0]) x = tr[x].son[0];
    return x;
  }
  void split_(u32 x, u32 y) { makeroot_(x), access_(y), splay_(y); }
  bool con_(u32 x, u32 y) {
    makeroot_(x);
    if (findroot_(y) != x) return true;
    return false;
  }
  bool link_(u32 x, u32 y) {
    makeroot_(x);
    if (findroot_(y) != x) return tr[x].fa = y, true;
    return false;
  }
  bool cut_(u32 x, u32 y) {
    makeroot_(x), access_(y);
    if (findroot_(y) == x && tr[x].fa == y && tr[y].son[0] == x) {
      tr[y].son[0] = tr[x].fa = 0, update_(y);
      return true;
    }
    return false;
  }

 public:
  link_cut_tree(u32 n, vec<T> A) : tr(n + 1) {
    a.push_back(0);
    for (auto x : A) a.push_back(x);
  }
  void access(u32 x) { access_(x + 1); }
  void makeroot(u32 x) { makeroot_(x + 1); }
  u32 findroot(u32 x) { return findroot_(x + 1) - 1; }
  void split(u32 x, u32 y) { split(x + 1, y + 1); }
  bool con(u32 x, u32 y) { return con_(x + 1, y + 1); }
  bool link(u32 x, u32 y) { return link_(x + 1, y + 1); }
  bool cut(u32 x, u32 y) { return cut_(x + 1, y + 1); }
  void node_update(u32 x, T k) { x += 1, splay_(x), a[x] = k, update_(x); }
  void node_add(u32 x, T k) { x += 1, splay_(x), a[x] = op(a[x], k), update_(x); }
  T query(u32 x, u32 y) {
    x += 1, y += 1;
    split_(x, y);
    return tr[y].w;
  }
};

}  // namespace tifa_libs::ds

#endif