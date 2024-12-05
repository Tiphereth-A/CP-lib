#ifndef TIFALIBS_DS_RBTREE
#define TIFALIBS_DS_RBTREE

#include "ostree.hpp"

namespace tifa_libs::ds {

struct rbt_tag : bst_tag {
  template <class pointer>
  static CEXP bool is_red(pointer p) { return p ? p->red : false; }
  template <class pointer>
  static CEXP void insert_leaf(pointer &root, pointer p, pointer n, bool dir) {
    n->red = p, bst_tag::insert_leaf(root, p, n, dir);
    while (is_red(p = n->fa)) {
      bool p_dir = p->child_dir();
      auto g = p->fa, u = g->ch[!p_dir];
      if (is_red(u)) {
        p->red = u->red = false, g->red = true, n = g;
        continue;
      }
      if (n->child_dir() != p_dir) rotate(root, p, p_dir), swap(n, p);
      p->red = false, g->red = true, rotate(root, g, !p_dir);
    }
    root->red = false;
  }
  template <class pointer>
  static CEXP void erase_branch_leaf(pointer &root, pointer n) {
    bool n_dir = n == root ? false : n->child_dir();
    bst_tag::erase_branch_leaf(root, n);
    auto p = n->fa;
    if (!p) {
      if (root) root->red = false;
      return;
    } else if (auto s = p->ch[n_dir]; s) return void(s->red = false);
    while (p && !n->red) {
      auto s = p->ch[!n_dir];
      if (is_red(s)) s->red = false, p->red = true, rotate(root, p, n_dir), s = p->ch[!n_dir];
      auto c = s->ch[n_dir], d = s->ch[!n_dir];
      if (!is_red(c) && !is_red(d)) {
        if (s->red = true, n = p, p = n->fa; !p) break;
        n_dir = n->child_dir();
        continue;
      }
      if (!is_red(d)) c->red = false, s->red = true, rotate(root, s, !n_dir), s = p->ch[!n_dir], c = s->ch[n_dir], d = s->ch[!n_dir];
      s->red = p->red, p->red = d->red = false, rotate(root, p, n_dir), n = root;
      break;
    }
    n->red = false;
  }
};

template <class K>
struct ostree_node_t<rbt_tag, K> {
  ostree_node_t *fa, *ch[2];
  K data;
  u32 sz;
  bool red;
  // @return child direction of this non-root point
  CEXP bool child_dir() const { return this == fa->ch[1]; }
};

template <class K, class Comp = std::less<K>>
using rbtree = ostree<K, rbt_tag, Comp>;

}  // namespace tifa_libs::ds

#endif